//
// (C) 2005 Vojtech Janota, Andras Varga
//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#include <omnetpp.h>
#include <algorithm>

#include "LinkStateRouting.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPControlInfo.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\IPv4InterfaceData.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\NotifierConsts.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\RoutingTableAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTableAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\NotificationBoard.h"
#include "TED.h"
#include "TEDAccess.h"

Define_Module(LinkStateRouting);

LinkStateRouting::LinkStateRouting()
{
    announceMsg = NULL;
}

LinkStateRouting::~LinkStateRouting()
{
    cancelAndDelete(announceMsg);
}

void LinkStateRouting::initialize(int stage)
{
    // we have to wait until routerId gets assigned in stage 3
    if (stage==4)
    {
        tedmod = TEDAccess().get();

        IRoutingTable *rt = RoutingTableAccess().get();
        routerId = rt->getRouterId();

        // listen for TED modifications
        NotificationBoard *nb = NotificationBoardAccess().get();
        nb->subscribe(this, NF_TED_CHANGED);

        // peers are given as interface names in the "peers" module parameter;
        // store corresponding interface addresses in peerIfAddrs[]
        inet::cStringTokenizer tokenizer(par("peers"));
        IInterfaceTable *ift = InterfaceTableAccess().get();
        const char *token;
        while ((token = tokenizer.nextToken())!=NULL)
        {
            ASSERT(ift->getInterfaceByName(token));
            peerIfAddrs.push_back(ift->getInterfaceByName(token)->ipv4Data()->getIPAddress());
        }

        // schedule start of flooding link state info
        announceMsg = new inet::cMessage("announce");
        scheduleAt(inet::simTime() + exponential(0.01), announceMsg);
    }
}

void LinkStateRouting::handleMessage(inet::cMessage * msg)
{
    if (msg == announceMsg)
    {
        delete announceMsg;
        announceMsg = NULL;
        sendToPeers(tedmod->ted, true, IPAddress());
    }
    else if (!strcmp(msg->getArrivalGate()->getName(), "ipIn"))
    {
        std::cout << "Processing message from IP: " << msg << std::endl;
        IPControlInfo *controlInfo = check_and_cast<IPControlInfo *>(msg->getControlInfo());
        IPAddress sender = controlInfo->getSrcAddr();
        processLINK_STATE_MESSAGE(check_and_cast<LinkStateMsg*>(msg), sender);
    }
    else
        ASSERT(false);
}

void LinkStateRouting::receiveChangeNotification(int category, const inet::cObject *details)
{
    Enter_Method_Silent();
    printNotificationBanner(category, details);

    ASSERT(category == NF_TED_CHANGED);

    std::cout << "TED changed\n";

    const TEDChangeInfo *d = check_and_cast<const TEDChangeInfo *>(details);

    unsigned int k = d->getTedLinkIndicesArraySize();

    ASSERT(k > 0);

    // build linkinfo list
    std::vector<TELinkStateInfo> links;
    for (unsigned int i = 0; i < k; i++)
    {
        unsigned int index = d->getTedLinkIndices(i);

        tedmod->updateTimestamp(&tedmod->ted[index]);
        links.push_back(tedmod->ted[index]);
    }

    sendToPeers(links, false, IPAddress());
}

void LinkStateRouting::processLINK_STATE_MESSAGE(LinkStateMsg* msg, IPAddress sender)
{
    std::cout << "received LINK_STATE message from " << sender << std::endl;

    TELinkStateInfoVector forward;

    unsigned int n = msg->getLinkInfoArraySize();

    bool change = false; // in topology

    // loop through every link in the message
    for (unsigned int i = 0; i < n; i++)
    {
        const TELinkStateInfo& link = msg->getLinkInfo(i);

        TELinkStateInfo *match;

        // process link if we haven't seen this already and timestamp is newer
        if(tedmod->checkLinkValidity(link, match))
        {
            ASSERT(link.sourceId == link.advrouter.getInt());

            std::cout << "new information found" << std::endl;

            if(!match)
            {
                // and we have no info on this link so far, store it as it is
                tedmod->ted.push_back(link);
                change = true;
            }
            else
            {
                // copy over the information from it
                if(match->state != link.state)
                {
                    match->state = link.state;
                    change = true;
                }
                match->messageId = link.messageId;
                match->sourceId = link.sourceId;
                match->timestamp = link.timestamp;
                for(int i = 0; i < 8; i++)
                    match->UnResvBandwidth[i] = link.UnResvBandwidth[i];
                match->MaxBandwidth = link.MaxBandwidth;
                match->metric = link.metric;
            }

            forward.push_back(link);
        }
    }

    if(change)
        tedmod->rebuildRoutingTable();

    if(msg->getRequest())
    {
        sendToPeer(sender, tedmod->ted, false);
    }

    if(forward.size() > 0)
    {
        sendToPeers(forward, false, sender);
    }

    delete msg;
}

void LinkStateRouting::sendToPeers(const std::vector<TELinkStateInfo>& list, bool req, IPAddress exceptPeer)
{
    std::cout << "sending LINK_STATE message to peers" << std::endl;

    // send "list" to every peer (linkid in our ted[] entries???) in a LinkStateMsg
    for (unsigned int i = 0; i < tedmod->ted.size(); i++)
    {
        if(tedmod->ted[i].advrouter != routerId)
            continue;

        if(tedmod->ted[i].linkid == exceptPeer)
            continue;

        if(!tedmod->ted[i].state)
            continue;

        if(find(peerIfAddrs.begin(), peerIfAddrs.end(), tedmod->ted[i].local) == peerIfAddrs.end())
            continue;

        // send a copy
        sendToPeer(tedmod->ted[i].linkid, list, req);
    }
}

void LinkStateRouting::sendToPeer(IPAddress peer, const std::vector<TELinkStateInfo> & list, bool req)
{
    std::cout << "sending LINK_STATE message to " << peer << std::endl;

    LinkStateMsg *out = new LinkStateMsg("link state");

    out->setLinkInfoArraySize(list.size());
    for (unsigned int j = 0; j < list.size(); j++)
        out->setLinkInfo(j, list[j]);

    out->setRequest(req);

    sendToIP(out, peer);
}

void LinkStateRouting::sendToIP(LinkStateMsg *msg, IPAddress destAddr)
{
    // attach control info to packet
    IPControlInfo *controlInfo = new IPControlInfo();
    controlInfo->setDestAddr(destAddr);
    controlInfo->setSrcAddr(routerId);
    controlInfo->setProtocol(IP_PROT_OSPF);
    msg->setControlInfo(controlInfo);

    int length = msg->getLinkInfoArraySize() * 72;
    msg->setByteLength(length);

    msg->addPar("color") = TED_TRAFFIC;

    send(msg, "ipOut");
}

