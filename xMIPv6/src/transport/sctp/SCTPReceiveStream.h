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
//#ifndef __SCTPRECEIVESTREAM_H
//#define __SCTPRECEIVESTREAM_H
//
//#include <omnetpp.h>
//#include "SCTPAssociation.h"
//#include "SCTPQueue.h"
//
//class SCTPMessage;
//class SCTPCommand;
//class SCTPQueue;
//
//
//class SCTPReceiveStream : public inet::cObject
//{
//  protected:
//	uint16_t streamId;
//	int32_t expectedStreamSeqNum;
//	SCTPQueue* deliveryQ;
//	SCTPQueue* orderedQ;
//	SCTPQueue* unorderedQ;
//  public:
//  uint32_t enqueueNewDataChunk(SCTPDataVariables* dchunk);
//    /**
//     * Ctor.
//     */
//    SCTPReceiveStream();
//
//    /**
//     * Virtual dtor.
//     */
//    ~SCTPReceiveStream();
//	//void enqueueNewDataChunk(SCTPDataVariables* dchunk);
//	SCTPQueue* getDeliveryQ() {return deliveryQ;};
//	SCTPQueue* getOrderedQ() {return orderedQ;};
//	SCTPQueue* getUnorderedQ() {return unorderedQ;};
//	int32_t getExpectedStreamSeqNum() { return expectedStreamSeqNum;};
//	int32_t getStreamId() {return streamId;};
//	void setExpectedStreamSeqNum(int32_t num) {expectedStreamSeqNum=num;};
//	void setStreamId(uint16_t id) {streamId = id;};
//};
//
//#endif
//
//
