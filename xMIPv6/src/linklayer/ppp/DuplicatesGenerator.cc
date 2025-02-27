////
//// Copyright (C) 2009 Thomas Reschka
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#include "DuplicatesGenerator.h"
//
//Define_Module(DuplicatesGenerator);
//
//void DuplicatesGenerator::initialize()
//{
//    numPackets = 0;
//    numDuplicated = 0;
//    generateFurtherDuplicates = false;
//
//    WATCH(numPackets);
//    WATCH(numDuplicated);
//    WATCH(generateFurtherDuplicates);
//
//	const char *vector = par("duplicatesVector");
//    parseVector(vector);
//
//    if (duplicatesVector.size()==0)
//    	{EV << "DuplicatesGenerator: Empty duplicatesVector" << endl;}
//    else
//    {
//    	EV << "DuplicatesGenerator: duplicatesVector=" << vector << endl;
//    	generateFurtherDuplicates = true;
//    }
//}
//
//void DuplicatesGenerator::handleMessage(cMessage *msg)
//{
//	numPackets++;
//
//	if (generateFurtherDuplicates)
//	{
//		if (numPackets==duplicatesVector[0])
//		{
//			EV << "DuplicatesGenerator: Duplicating packet number " << numPackets << " " << msg << endl;
//			cMessage *dupmsg = (cMessage*) msg->dup();
//			send(dupmsg, "out");
//			numDuplicated++;
//			duplicatesVector.erase(duplicatesVector.begin());
//			if (duplicatesVector.size()==0)
//			{
//				EV << "DuplicatesGenerator: End of duplicatesVector reached." << endl;
//				generateFurtherDuplicates = false;
//			}
//		}
//	}
//	send(msg, "out");
//}
//
//void DuplicatesGenerator::parseVector(const char *vector)
//{
//    const char *v = vector;
//    while (*v)
//    {
//        // parse packet numbers
//        while (isspace(*v)) v++;
//		if (!*v || *v==';') break;
//        if (!isdigit(*v))
//            throw cRuntimeError("syntax error in duplicatesVector: packet number expected");
//        if (duplicatesVector.size()>0 && duplicatesVector.back() >= (unsigned int)atoi(v))
//            throw cRuntimeError("syntax error in duplicatesVector: packet numbers in ascending order expected");
//
//        duplicatesVector.push_back(atoi(v));
//        while (isdigit(*v)) v++;
//
//        // skip delimiter
//        while (isspace(*v)) v++;
//        if (!*v) break;
//        if (*v!=';')
//            throw cRuntimeError("syntax error in duplicatesVector: separator ';' missing");
//        v++;
//        while (isspace(*v)) v++;
//    }
//}
//
//void DuplicatesGenerator::finish()
//{
//    recordScalar("total packets", numPackets);
//    recordScalar("total duplicated", numDuplicated);
//}
