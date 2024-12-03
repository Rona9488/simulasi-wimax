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
//
//#ifndef __SCTPSENDSTREAM_H
//#define __SCTPSENDSTREAM_H
//
//#include <omnetpp.h>
//#include <list>
//#include "SCTPAssociation.h"
//#include "SCTPQueue.h"
//
//class SCTPMessage;
//class SCTPCommand;
//class SCTPQueue;
//class SCTPDataVariables;
//
//
//class SCTPSendStream : public inet::cObject
//{
//	protected:
//		uint16_t streamId;
//		uint16_t nextStreamSeqNum;
//		inet::cQueue  *streamQ;
//		inet::cQueue	*uStreamQ;
//		int32_t ssn;
//	public:
//
//		SCTPSendStream(uint16_t id);
//		~SCTPSendStream();
//
//		inet::cQueue* getStreamQ() {return streamQ;};
//		inet::cQueue* getUnorderedStreamQ() {return uStreamQ;};
//		uint32_t getNextStreamSeqNum() {return nextStreamSeqNum;};
//		void setNextStreamSeqNum(uint16_t num) {nextStreamSeqNum = num;};
//		uint16_t getStreamId() {return streamId;};
//		void setStreamId(uint16_t id) {streamId = id;};
//		void deleteQueue();
//};
//
//#endif
//
//
