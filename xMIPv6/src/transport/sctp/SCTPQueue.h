////
//// Copyright (C) 2008 Irene Ruengeler
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#ifndef __SCTPQUEUE_H
//#define __SCTPQUEUE_H
//
//#include <omnetpp.h>
//#include "SCTPAssociation.h"
//
//
//class SCTPMessage;
//class SCTPCommand;
//class SCTPDataVariables;
//
///**
// * Abstract base class for SCTP receive queues. This class represents
// * data received by SCTP but not yet passed up to the application.
// * The class also accomodates for selective retransmission, i.e.
// * also acts as a segment buffer.
// *
// * This class goes hand-in-hand with SCTPSendQueue.
// *
// * This class is polymorphic because depending on where and how you
// * use the SCTP model you might have different ideas about "sending data"
// * on a simulated connection: you might want to transmit real bytes,
// * "dummy" (byte count only), inet::cMessage objects, etc; see discussion
// * at SCTPSendQueue. Different subclasses can be written to accomodate
// * different needs.
// *
// * @see SCTPSendQueue
// */
//class SCTPQueue : public inet::cObject
//{
//  protected:
//    SCTPAssociation *assoc; // SCTP connection object
//
//
//  public:
//    typedef std::map<uint32_t, SCTPDataVariables *> PayloadQueue;
//  PayloadQueue payloadQueue;
//    /**
//     * Ctor.
//     */
//    SCTPQueue();
//
//    /**
//     * Virtual dtor.
//     */
//    ~SCTPQueue();
//
////	uint32_t insertMessage(uint32_t key,SCTPDataVariables* datVar);
//
//	bool checkAndInsertVar(uint32_t key,SCTPDataVariables *datVar); /* returns true if new data is inserted and false if data was present*/
//
//    SCTPDataVariables *getAndExtractMessage(uint32_t tsn);
//    SCTPDataVariables *extractMessage();
//
//	void printQueue();
//
//	uint32_t getQueueSize();
//
//	SCTPDataVariables* getFirstVar();
//
//	inet::cMessage* getMsg(uint32_t key);
//
//	SCTPDataVariables* getVar(uint32_t key);
//
//	SCTPDataVariables* getNextVar(uint32_t key, uint32_t toTsn);
//
//	void removeMsg(uint32_t key);
//
//	bool deleteMsg(uint32_t tsn);
//
//	int32_t getNumBytes();
//
//	SCTPDataVariables* dequeueVarBySsn(uint16_t ssn);
//};
//
//#endif
//
//
