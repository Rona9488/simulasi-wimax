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
//#include <stdio.h>
//#include <string.h>
//#include <omnetpp.h>
//#include "IInterfaceTable.h"
//#include "InterfaceTableAccess.h"
//#include "PPP.h"
//#include "IPassiveQueue.h"
//#include "NotificationBoard.h"
//#include "NotifierConsts.h"
//
//
//
//Define_Module(PPP);
//
//PPP::PPP()
//{
//    endTransmissionEvent = NULL;
//    nb = NULL;
//}
//
//PPP::~PPP()
//{
//    // kludgy way to check that nb is not deleted yet
//    if (nb && nb == findModuleWhereverInNode("notificationBoard", this))
//        nb->unsubscribe(this, NF_SUBSCRIBERLIST_CHANGED);
//    cancelAndDelete(endTransmissionEvent);
//}
//
//void PPP::initialize(int stage)
//{
//    // all initialization is done in the first stage
//    if (stage==0)
//    {
//        txQueue.setName("txQueue");
//        endTransmissionEvent = new cMessage("pppEndTxEvent");
//
//        txQueueLimit = par("txQueueLimit");
//
//        interfaceEntry = NULL;
//
//        numSent = numRcvdOK = numBitErr = numDroppedIfaceDown = 0;
//        WATCH(numSent);
//        WATCH(numRcvdOK);
//        WATCH(numBitErr);
//        WATCH(numDroppedIfaceDown);
//
//        // find queueModule
//        queueModule = NULL;
//        if (par("queueModule").stringValue()[0])
//        {
//            cModule *mod = getParentModule()->getSubmodule(par("queueModule").stringValue());
//            queueModule = check_and_cast<IPassiveQueue *>(mod);
//        }
//
//        // remember the output gate now, to speed up send()
//        physOutGate = gate("phys$o");
//
//        // we're connected if other end of connection path is an input gate
//        bool connected = physOutGate->getPathEndGate()->getType()==cGate::INPUT;
//
//        // if we're connected, get the gate with transmission rate
//        datarateChannel = connected ? physOutGate->getTransmissionChannel() : NULL;
//        double datarate = connected ? datarateChannel->par("datarate").doubleValue() : 0;
//
//        // register our interface entry in IInterfaceTable
//        interfaceEntry = registerInterface(datarate);
//
//        // prepare to fire notifications
//        nb = NotificationBoardAccess().get();
//        notifDetails.setInterfaceEntry(interfaceEntry);
//        nb->subscribe(this, NF_SUBSCRIBERLIST_CHANGED);
//        updateHasSubcribers();
//
//        // display string stuff
//        if (ev.isGUI())
//        {
//            if (connected) {
//                oldConnColor = datarateChannel->getDisplayString().getTagArg("o",0);
//            }
//            else {
//                // we are not connected: gray out our icon
//                getDisplayString().setTagArg("i",1,"#707070");
//                getDisplayString().setTagArg("i",2,"100");
//            }
//        }
//
//        // request first frame to send
//        if (queueModule)
//        {
//            EV << "Requesting first frame from queue module\n";
//            queueModule->requestPacket();
//        }
//    }
//
//    // update display string when addresses have been autoconfigured etc.
//    if (stage==3)
//    {
//        updateDisplayString();
//    }
//}
//
//InterfaceEntry *PPP::registerInterface(double datarate)
//{
//    InterfaceEntry *e = new InterfaceEntry();
//
//    // interface name: our module name without special characters ([])
//    char *interfaceName = new char[strlen(getParentModule()->getFullName())+1];
//    char *d=interfaceName;
//    for (const char *s=getParentModule()->getFullName(); *s; s++)
//        if (isalnum(*s))
//            *d++ = *s;
//    *d = '\0';
//
//    e->setName(interfaceName);
//    delete [] interfaceName;
//
//    // data rate
//    e->setDatarate(datarate);
//
//    // generate a link-layer address to be used as interface token for IPv6
//    InterfaceToken token(0, simulation.getUniqueNumber(), 64);
//    e->setInterfaceToken(token);
//
//    // MTU: typical values are 576 (Internet de facto), 1500 (Ethernet-friendly),
//    // 4000 (on some point-to-point links), 4470 (Cisco routers default, FDDI compatible)
//    e->setMtu(par("mtu"));
//
//    // capabilities
//    e->setMulticast(true);
//    e->setPointToPoint(true);
//
//    // add
//    IInterfaceTable *ift = InterfaceTableAccess().get();
//    ift->addInterface(e, this);
//
//    return e;
//}
//
//
//void PPP::startTransmitting(cPacket *msg)
//{
//    // if there's any control info, remove it; then encapsulate the packet
//    delete msg->removeControlInfo();
//    PPPFrame *pppFrame = encapsulate(msg);
//    if (ev.isGUI()) displayBusy();
//
//    if (hasSubscribers)
//    {
//        // fire notification
//        notifDetails.setPacket(pppFrame);
//        nb->fireChangeNotification(NF_PP_TX_BEGIN, &notifDetails);
//    }
//
//    // send
//    EV << "Starting transmission of " << pppFrame << endl;
//    send(pppFrame, physOutGate);
//
//    // schedule an event for the time when last bit will leave the gate.
//    simtime_t endTransmissionTime = datarateChannel->getTransmissionFinishTime();
//    scheduleAt(endTransmissionTime, endTransmissionEvent);
//}
//
//void PPP::handleMessage(cMessage *msg)
//{
//    if (datarateChannel==NULL)
//    {
//        EV << "Interface is not connected, dropping packet " << msg << endl;
//        delete msg;
//        numDroppedIfaceDown++;
//    }
//    else if (msg==endTransmissionEvent)
//    {
//        // Transmission finished, we can start next one.
//        EV << "Transmission finished.\n";
//        if (ev.isGUI()) displayIdle();
//
//        if (hasSubscribers)
//        {
//            // fire notification
//            notifDetails.setPacket(NULL);
//            nb->fireChangeNotification(NF_PP_TX_END, &notifDetails);
//        }
//
//        if (!txQueue.empty())
//        {
//            cPacket *pk = (cPacket *) txQueue.pop();
//            startTransmitting(pk);
//            numSent++;
//        }
//        else if (queueModule)
//        {
//            // tell queue module that we've become idle
//            queueModule->requestPacket();
//        }
//    }
//    else if (msg->arrivedOn("phys$i"))
//    {
//        if (hasSubscribers)
//        {
//            // fire notification
//            notifDetails.setPacket(PK(msg));
//            nb->fireChangeNotification(NF_PP_RX_END, &notifDetails);
//        }
//
//        // check for bit errors
//        if (PK(msg)->hasBitError())
//        {
//            EV << "Bit error in " << msg << endl;
//            numBitErr++;
//            delete msg;
//        }
//        else
//        {
//            // pass up payload
//            cPacket *payload = decapsulate(check_and_cast<PPPFrame *>(msg));
//            numRcvdOK++;
//            send(payload,"netwOut");
//        }
//    }
//    else // arrived on gate "netwIn"
//    {
//        if (endTransmissionEvent->isScheduled())
//        {
//            // We are currently busy, so just queue up the packet.
//            EV << "Received " << msg << " for transmission but transmitter busy, queueing.\n";
//            if (ev.isGUI() && txQueue.length()>=3) getDisplayString().setTagArg("i",1,"red");
//
//            if (txQueueLimit && txQueue.length()>txQueueLimit)
//                error("txQueue length exceeds %d -- this is probably due to "
//                      "a bogus app model generating excessive traffic "
//                      "(or if this is normal, increase txQueueLimit!)",
//                      txQueueLimit);
//
//            txQueue.insert(msg);
//        }
//        else
//        {
//            // We are idle, so we can start transmitting right away.
//            EV << "Received " << msg << " for transmission\n";
//            startTransmitting(PK(msg));
//            numSent++;
//        }
//    }
//
//    if (ev.isGUI())
//        updateDisplayString();
//
//}
//
//void PPP::displayBusy()
//{
//    getDisplayString().setTagArg("i",1, txQueue.length()>=3 ? "red" : "yellow");
//    datarateChannel->getDisplayString().setTagArg("o",0,"yellow");
//    datarateChannel->getDisplayString().setTagArg("o",1,"3");
//}
//
//void PPP::displayIdle()
//{
//    getDisplayString().setTagArg("i",1,"");
//    datarateChannel->getDisplayString().setTagArg("o",0,oldConnColor.c_str());
//    datarateChannel->getDisplayString().setTagArg("o",1,"1");
//}
//
//void PPP::updateDisplayString()
//{
//    if (ev.isDisabled())
//    {
//        // speed up things
//        getDisplayString().setTagArg("t",0,"");
//    }
//    else if (datarateChannel!=NULL)
//    {
//        double datarate = datarateChannel->par("datarate").doubleValue();
//        char datarateText[40];
//        if (datarate>=1e9) sprintf(datarateText,"%gG", datarate/1e9);
//        else if (datarate>=1e6) sprintf(datarateText,"%gM", datarate/1e6);
//        else if (datarate>=1e3) sprintf(datarateText,"%gK", datarate/1e3);
//        else sprintf(datarateText,"%gbps", datarate);
//
///* TBD find solution for displaying IP address without dependence on IPv6 or IPv6
//        IPAddress addr = interfaceEntry->ipv4Data()->getIPAddress();
//        sprintf(buf, "%s / %s\nrcv:%ld snt:%ld", addr.isUnspecified()?"-":addr.str().c_str(), datarateText, numRcvdOK, numSent);
//*/
//
//        char buf[80];
//        sprintf(buf, "%s\nrcv:%ld snt:%ld", datarateText, numRcvdOK, numSent);
//
//        if (numBitErr>0)
//            sprintf(buf+strlen(buf), "\nerr:%ld", numBitErr);
//
//        getDisplayString().setTagArg("t",0,buf);
//    }
//    else
//    {
//        char buf[80];
//        sprintf(buf, "not connected\ndropped:%ld", numDroppedIfaceDown);
//        getDisplayString().setTagArg("t",0,buf);
//    }
//}
//
//void PPP::updateHasSubcribers()
//{
//    hasSubscribers = nb->hasSubscribers(NF_PP_TX_BEGIN) ||
//                     nb->hasSubscribers(NF_PP_TX_END) ||
//                     nb->hasSubscribers(NF_PP_RX_END);
//}
//
//void PPP::receiveChangeNotification(int category, const cPolymorphic *)
//{
//    if (category==NF_SUBSCRIBERLIST_CHANGED)
//        updateHasSubcribers();
//}
//
//PPPFrame *PPP::encapsulate(cPacket *msg)
//{
//    PPPFrame *pppFrame = new PPPFrame(msg->getName());
//    pppFrame->setByteLength(PPP_OVERHEAD_BYTES);
//    pppFrame->encapsulate(msg);
//    return pppFrame;
//}
//
//cPacket *PPP::decapsulate(PPPFrame *pppFrame)
//{
//    cPacket *msg = pppFrame->decapsulate();
//    delete pppFrame;
//    return msg;
//}
//
//
