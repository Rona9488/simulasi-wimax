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
//#ifndef __SCTPALGORITHM_H
//#define __SCTPALGORITHM_H
//
//#include <omnetpp.h>
//#include "SCTPAssociation.h"
//#include "SCTPQueue.h"
//
//
//
///**
// * Abstract base class for SCTP algorithms which encapsulate all behaviour
// * during data transfer state: flavour of congestion control, fast
// * retransmit/recovery, selective acknowledgement etc. Subclasses
// * may implement various sets and flavours of the above algorithms.
// */
//class SCTPAlgorithm : public inet::cObject
//{
//  protected:
//    SCTPAssociation *assoc; // we belong to this association
//    SCTPQueue *transmissionQ;
//    SCTPQueue *retransmissionQ;
//
//  public:
//    /**
//     * Ctor.
//     */
//    SCTPAlgorithm() {assoc = NULL; transmissionQ = NULL; retransmissionQ = NULL;}
//
//    /**
//     * Virtual dtor.
//     */
//    virtual ~SCTPAlgorithm() {}
//
//    void setAssociation(SCTPAssociation *_assoc)  {
//        assoc = _assoc;
//        transmissionQ = assoc->getTransmissionQueue();
//        retransmissionQ = assoc->getRetransmissionQueue();
//    }
//
//    virtual void initialize() {}
//
//    virtual SCTPStateVariables *createStateVariables() = 0;
//
//    virtual void established(bool active) = 0;
//
//    virtual void connectionClosed() = 0;
//
//    virtual void processTimer(inet::cMessage *timer, SCTPEventCode& event) = 0;
//
//    virtual void sendCommandInvoked(IPvXAddress addr) = 0;
//
//    virtual void receivedDataAck(uint32_t firstSeqAcked) = 0;
//
//    virtual void receivedDuplicateAck() = 0;
//
//    virtual void receivedAckForDataNotYetSent(uint32_t seq) = 0;
//
//    virtual void sackSent() = 0;
//
//    virtual void dataSent(uint32_t fromseq) = 0;
//
//};
//
//#endif
//
//
