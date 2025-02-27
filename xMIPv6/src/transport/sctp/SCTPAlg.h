//
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
//#ifndef __PLAINSCTP_H
//#define __PLAINSCTP_H
//
//#include <omnetpp.h>
//#include "SCTPAlgorithm.h"
//
//
///**
// * State variables for SCTPAlg.
// */
//class SCTPAlgStateVariables : public SCTPStateVariables
//{
//  public:
//    //...
//};
//
//
//class SCTPAlg : public SCTPAlgorithm
//{
//  protected:
//    SCTPAlgStateVariables *state;
//
//  public:
//    /**
//     * Ctor.
//     */
//    SCTPAlg();
//
//    /**
//     * Virtual dtor.
//     */
//    virtual ~SCTPAlg();
//
//    /**
//     * Creates and returns a SCTPStateVariables object.
//     */
//    virtual SCTPStateVariables *createStateVariables();
//
//    virtual void established(bool active);
//
//    virtual void connectionClosed();
//
//    virtual void processTimer(inet::cMessage *timer, SCTPEventCode& event);
//
//    virtual void sendCommandInvoked(IPvXAddress addr);
//
//    virtual void receivedDataAck(uint32_t firstSeqAcked);
//
//    virtual void receivedDuplicateAck();
//
//    virtual void receivedAckForDataNotYetSent(uint32_t seq);
//
//    virtual void sackSent();
//
//    virtual void dataSent(uint32_t fromseq);
//
//};
//
//#endif
//
//
