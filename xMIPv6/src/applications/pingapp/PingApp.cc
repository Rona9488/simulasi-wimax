////
//// Copyright (C) 2001, 2003, 2004 Johnny Lai, Monash University, Melbourne, Australia
//// Copyright (C) 2005 Andras Varga
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
//#include <limits.h>
//#include <stdlib.h>
//#include <iostream>
//
//#include "IPAddressResolver.h"
//#include "PingApp.h"
//#include "PingPayload_m.h"
//#include "IPControlInfo.h"
//#include "IPv6ControlInfo.h"
//
//Define_Module(PingApp);
//
//void PingApp::initialize()
//{
//    // read params
//    // (defer reading srcAddr/destAddr to when ping starts, maybe
//    // addresses will be assigned later by some protocol)
//    packetSize = par("packetSize");
//    intervalp = & par("interval");
//    hopLimit = par("hopLimit");
//    count = par("count");
//    startTime = par("startTime");
//    stopTime = par("stopTime");
//    printPing = (bool)par("printPing");
//
//    // state
//    sendSeqNo = expectedReplySeqNo = 0;
//    WATCH(sendSeqNo);
//    WATCH(expectedReplySeqNo);
//
//    // statistics
//    delayStat.setName("pingRTT");
//    delayVector.setName("pingRTT");
//    dropVector.setName("pingDrop");
//
//    dropCount = outOfOrderArrivalCount = 0;
//    WATCH(dropCount);
//    WATCH(outOfOrderArrivalCount);
//
//    //Additonal statistics parameters intialised (Zarrar Yousaf 15.11.07)
//    sentVector.setName("PING: Ping Request");
//    receivedVector.setName("PING: Ping Reply");
//    pingTx = 0;
//    pingRx = 0;
//
//    EV << "PING app: " << getFullName() << " start=" << startTime << endl;
//
//    // schedule first ping (use empty destAddr or stopTime<=startTime to disable)
//    if (par("destAddr").stringValue()[0] && (stopTime==0 || stopTime>=startTime))
//    {
//        cMessage *msg = new cMessage("sendPing");
//        scheduleAt(startTime, msg);
//    }
//}
//
//void PingApp::handleMessage(cMessage *msg)
//{
//    if (msg->isSelfMessage())
//    {
//        // on first call we need to initialize
//
//        if (destAddr.isUnspecified())
//        {
//            std::string myname = getFullPath();
//
//            // check if destination has address assigned at all
//            IPvXAddress result;
//            bool resolvedok = IPAddressResolver().tryResolve(par("destAddr"), result);
//            if (!resolvedok) {
//                EV << "PingApp(" << myname << ") failed: Unable to resolve " << par("destAddr").stringValue() << ", retrying in 1 second." << endl;
//                // It is possible that destination is now during handover and its address is tentative
//                // now, so we can't get its name resolved
//                // let's try resolving it again in 1 second
//                scheduleAt(simTime()+1.0f, msg);
//                return;
//            }
//
//            destAddr = IPAddressResolver().resolve(par("destAddr"));
//            ASSERT(!destAddr.isUnspecified());
//            srcAddr = IPAddressResolver().resolve(par("srcAddr"));
//            EV << "Starting up: dest=" << destAddr << "  src=" << srcAddr << "\n";
//        }
//
//        // send a ping request
//        sendPing();
//
//        // then schedule next one if needed
//        scheduleNextPing(msg);
//    }
//    else
//    {
//        // process ping response
//        processPingResponse(check_and_cast<PingPayload *>(msg));
//    }
//}
//
//void PingApp::sendPing()
//{
//    EV << "Sending ping #" << sendSeqNo << "\n";
//
//    char name[32];
//    sprintf(name,"ping%ld", sendSeqNo);
//
//    PingPayload *msg = new PingPayload(name);
//    msg->setOriginatorId(getId());
//    msg->setSeqNo(sendSeqNo);
//    msg->setByteLength(packetSize);
//
//    pingTx = sendSeqNo; //Statistics: Zarrar Yousaf
//    sentVector.record(pingTx); //Statistics: Zarrar Yousaf
//
//    EV << endl << endl << "send ping" << endl << "destAddr = " << destAddr << endl << "srcAddr = " << srcAddr << endl<<endl;
//    sendToICMP(msg, destAddr, srcAddr, hopLimit);
//}
//
//void PingApp::scheduleNextPing(cMessage *timer)
//{
//    simtime_t nextPing = simTime() + intervalp->doubleValue();
//    sendSeqNo++;
//    if ((count==0 || sendSeqNo<count) && (stopTime==0 || nextPing<stopTime))
//        scheduleAt(nextPing, timer);
//    else
//        delete timer;
//}
//
//void PingApp::sendToICMP(cMessage *msg, const IPvXAddress& destAddr, const IPvXAddress& srcAddr, int hopLimit)
//{
//    if (!destAddr.isIPv6())
//    {
//        // send to IPv4
//        IPControlInfo *ctrl = new IPControlInfo();
//        ctrl->setSrcAddr(srcAddr.get4());
//        ctrl->setDestAddr(destAddr.get4());
//        ctrl->setTimeToLive(hopLimit);
//        msg->setControlInfo(ctrl);
//        send(msg, "pingOut");
//    }
//    else
//    {
//        // send to IPv6
//        IPv6ControlInfo *ctrl = new IPv6ControlInfo();
//        ctrl->setSrcAddr(srcAddr.get6());
//        ctrl->setDestAddr(destAddr.get6());
//        ctrl->setHopLimit(hopLimit);
//        msg->setControlInfo(ctrl);
//        send(msg, "pingv6Out");
//    }
//}
//
//void PingApp::processPingResponse(PingPayload *msg)
//{
//    // get src, hopCount etc from packet, and print them
//    EV << "PingApp::processPingResponse_start" << endl;
//    IPvXAddress src, dest;
//    int msgHopCount = -1;
//    if (dynamic_cast<IPControlInfo *>(msg->getControlInfo())!=NULL)
//    {
//        IPControlInfo *ctrl = (IPControlInfo *)msg->getControlInfo();
//        src = ctrl->getSrcAddr();
//        dest = ctrl->getDestAddr();
//        msgHopCount = ctrl->getTimeToLive();
//    }
//    else if (dynamic_cast<IPv6ControlInfo *>(msg->getControlInfo())!=NULL)
//    {
//        IPv6ControlInfo *ctrl = (IPv6ControlInfo *)msg->getControlInfo();
//        src = ctrl->getSrcAddr();
//        dest = ctrl->getDestAddr();
//        msgHopCount = ctrl->getHopLimit();
//    }
//
//    simtime_t rtt = simTime() - msg->getCreationTime();
//   //Statistics: Zarrar Yousaf 15.11.07
//    pingRx = msg->getSeqNo(); //ZY
//    receivedVector.record(pingRx); //ZY
//
//
//
//    if (printPing){
//        EV << getFullPath() << ": reply of " << std::dec << msg->getByteLength()
//             << " bytes from " << src
//             << " icmp_seq=" << msg->getSeqNo() << " ttl=" << msgHopCount
//             << " time=" << (rtt * 1000) << " msec"
//             << " (" << msg->getName() << ")" << endl;
//    }
//
//    // update statistics
//    countPingResponse(msg->getByteLength(), msg->getSeqNo(), rtt);
//    delete msg;
//}
//
//void PingApp::countPingResponse(int bytes, long seqNo, simtime_t rtt)
//{
//    EV << "Ping reply #" << seqNo << " arrived, rtt=" << rtt << "\n";
//
//    delayStat.collect(rtt);
//    delayVector.record(rtt);
//
//    if (seqNo == expectedReplySeqNo)
//    {
//        // expected ping reply arrived; expect next sequence number
//        expectedReplySeqNo++;
//    }
//    else if (seqNo > expectedReplySeqNo)
//    {
//        EV << "Jump in seq numbers, assuming pings since #" << expectedReplySeqNo << " got lost\n";
//
//        // jump in the sequence: count pings in gap as lost
//        long jump = seqNo - expectedReplySeqNo;
//        dropCount += jump;
//        dropVector.record(dropCount);
//
//        // expect sequence numbers to continue from here
//        expectedReplySeqNo = seqNo+1;
//    }
//    else // seqNo < expectedReplySeqNo
//    {
//        // ping arrived too late: count as out of order arrival
//        EV << "Arrived out of order (too late)\n";
//        outOfOrderArrivalCount++;
//    }
//}
//
//void PingApp::finish()
//{
//    if (sendSeqNo==0)
//    {
//        EV << getFullPath() << ": No pings sent, skipping recording statistics and printing results.\n";
//        recordScalar("Pings sent", sendSeqNo);
//        return;
//    }
//
//    // record statistics
//    recordScalar("Pings sent", sendSeqNo);
//    recordScalar("Pings dropped", dropCount);
//    recordScalar("Out-of-order ping arrivals", outOfOrderArrivalCount);
//    recordScalar("Pings outstanding at end", sendSeqNo-expectedReplySeqNo);
//
//    recordScalar("Ping drop rate (%)", 100 * dropCount / (double)sendSeqNo);
//    recordScalar("Ping out-of-order rate (%)", 100 * outOfOrderArrivalCount / (double)sendSeqNo);
//
//    delayStat.recordAs("Ping roundtrip delays");
//
//    // print it to stdout as well
//    EV << "--------------------------------------------------------" << endl;
//    EV << "\t" << getFullPath() << endl;
//    EV << "--------------------------------------------------------" << endl;
//
//    EV << "sent: " << sendSeqNo
//         << "   drop rate (%): " << (100 * dropCount / (double)sendSeqNo) << endl;
//    EV << "round-trip min/avg/max (ms): "
//         << (delayStat.getMin()*1000.0) << "/"
//         << (delayStat.getMean()*1000.0) << "/"
//         << (delayStat.getMax()*1000.0) << endl;
//    EV << "stddev (ms): "<< (delayStat.getStddev()*1000.0)
//         << "   variance:" << delayStat.getVariance() << endl;
//    EV <<"--------------------------------------------------------" << endl;
//}
//
//
