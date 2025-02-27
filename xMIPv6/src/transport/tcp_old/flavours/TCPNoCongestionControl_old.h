////
//// Copyright (C) 2004 Andras Varga
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
//#ifndef __INET_TCPNOCONGESTIONCONTROL_OLD_H
//#define __INET_TCPNOCONGESTIONCONTROL_OLD_H
//
//#include <omnetpp.h>
//#include "TCPBaseAlg_old.h"
//
//namespace tcp_old {
//
///**
// * State variables for TCPNoCongestionControl.
// */
//typedef TCPBaseAlgStateVariables TCPNoCongestionControlStateVariables;
//
//
///**
// * TCP with no congestion control (i.e. congestion window kept very large).
// * Can be used to demonstrate effect of lack of congestion control.
// */
//class INET_API TCPNoCongestionControl : public TCPBaseAlg
//{
//  protected:
//    TCPNoCongestionControlStateVariables *&state; // alias to TCLAlgorithm's 'state'
//
//    /** Create and return a TCPNoCongestionControlStateVariables object. */
//    virtual TCPStateVariables *createStateVariables() {
//        return new TCPNoCongestionControlStateVariables();
//    }
//
//    /** Redefine what should happen on retransmission */
//    virtual void processRexmitTimer(TCPEventCode& event);
//
//  public:
//    /** Ctor */
//    TCPNoCongestionControl();
//
//    /** Initialize state vars */
//    virtual void initialize();
//
//    /** Redefine what should happen when data got acked, to add congestion window management */
//    virtual void receivedDataAck(uint32 firstSeqAcked);
//};
//
//}
//#endif
//
//
