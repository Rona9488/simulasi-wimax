//
// Copyright (C) 2005 Andras Varga
// Copyright (C) 2005 Wei Yang, Ng
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include <omnetpp.h>
#include "ICMPv6.h"


Define_Module(ICMPv6);


void ICMPv6::initialize()
{
    CNtoSSVectorRTT.setName("CNtoSSTripTime");
    SStoCNVectorRTT.setName("SStoCNTripTime");
}

void ICMPv6::handleMessage(inet::cMessage *msg)
{
    ASSERT(!msg->isSelfMessage()); // no timers in ICMPv6

    // process arriving ICMP message
    if (msg->getArrivalGate()->isName("ipv6In"))
    {
        std::cout << "Processing ICMPv6 message.\n";
        processICMPv6Message(check_and_cast<inet::ICMPv6Message *>(msg));
        return;
    }

    // request from application
    if (msg->getArrivalGate()->isName("pingIn"))
    {
        sendEchoRequest(PK(msg));
        return;
    }
}

void ICMPv6::processICMPv6Message(inet::ICMPv6Message *icmpv6msg)
{
    ASSERT(dynamic_cast<inet::ICMPv6Message *>(icmpv6msg));
    if (dynamic_cast<inet::ICMPv6DestUnreachableMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Destination Unreachable Message Received." << std::endl;
        errorOut(icmpv6msg);
    }
    else if (dynamic_cast<inet::ICMPv6PacketTooBigMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Packet Too Big Message Received." << std::endl;
        errorOut(icmpv6msg);
    }
    else if (dynamic_cast<inet::ICMPv6TimeExceededMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Time Exceeded Message Received." << std::endl;
        errorOut(icmpv6msg);
    }
    else if (dynamic_cast<inet::ICMPv6ParamProblemMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Parameter Problem Message Received." << std::endl;
        errorOut(icmpv6msg);
    }
    else if (dynamic_cast<inet::ICMPv6EchoRequestMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Echo Request Message Received." << std::endl;
        processEchoRequest((inet::ICMPv6EchoRequestMsg *)icmpv6msg);
    }
    else if (dynamic_cast<inet::ICMPv6EchoReplyMsg *>(icmpv6msg))
    {
        std::cout << "ICMPv6 Echo Reply Message Received." << std::endl;
        processEchoReply((inet::ICMPv6EchoReplyMsg *)icmpv6msg);
    }
    else
        error("Unknown message type received.\n");
}

void ICMPv6::processEchoRequest(inet::ICMPv6EchoRequestMsg *request)
{
    //Create an ICMPv6 Reply Message
    inet::ICMPv6EchoReplyMsg *reply = new inet::ICMPv6EchoReplyMsg("Echo Reply");
    reply->setName((std::string(request->getName())+"-reply").c_str());
    reply->setType(inet::ICMPv6_ECHO_REPLY);
    reply->encapsulate(request->decapsulate());

    // TBD check what to do if dest was multicast etc?
    IPv6ControlInfo *ctrl
        = check_and_cast<IPv6ControlInfo *>(request->getControlInfo());
    IPv6ControlInfo *replyCtrl = new IPv6ControlInfo();
    replyCtrl->setProtocol(IP_PROT_IPv6_ICMP);
    //set Msg's source addr as the dest addr of request msg.
    replyCtrl->setSrcAddr(ctrl->getDestAddr());
    //set Msg's dest addr as the source addr of request msg.
    replyCtrl->setDestAddr(ctrl->getSrcAddr());
    reply->setControlInfo(replyCtrl);
    
    CNtoSSVectorRTT.record(inet::simTime() - request->getCreationTime());//============= Adam 14-10-2011 =====================

    delete request;
    sendToIP(reply);
}

void ICMPv6::processEchoReply(inet::ICMPv6EchoReplyMsg *reply)
{
    IPv6ControlInfo *ctrl = check_and_cast<IPv6ControlInfo*>(reply->removeControlInfo());
    inet::cPacket *payload = reply->decapsulate();
    payload->setControlInfo(ctrl);
    SStoCNVectorRTT.record(inet::simTime() - reply->getCreationTime()); //============= Adam 14-09-2011 =====================
    delete reply;
    send(payload, "pingOut");
}

void ICMPv6::sendEchoRequest(inet::cPacket *msg)
{
    IPv6ControlInfo *ctrl = check_and_cast<IPv6ControlInfo*>(msg->removeControlInfo());
    ctrl->setProtocol(IP_PROT_IPv6_ICMP);
    inet::ICMPv6EchoRequestMsg *request = new inet::ICMPv6EchoRequestMsg(msg->getName());
    request->setType(inet::ICMPv6_ECHO_REQUEST);
    request->encapsulate(msg);
    request->setControlInfo(ctrl);
    sendToIP(request);
}

void ICMPv6::sendErrorMessage(IPv6Datagram *origDatagram, inet::ICMPv6Type type, int code)
{
    Enter_Method("sendErrorMessage(datagram, type=%d, code=%d)", type, code);

    // get ownership
    take(origDatagram);

    if (!validateDatagramPromptingError(origDatagram))
        return;

    inet::ICMPv6Message *errorMsg;

    if (type == inet::ICMPv6_DESTINATION_UNREACHABLE) errorMsg = createDestUnreachableMsg(code);
    //TODO: implement MTU support.
    else if (type == inet::ICMPv6_PACKET_TOO_BIG) errorMsg = createPacketTooBigMsg(0);
    else if (type == inet::ICMPv6_TIME_EXCEEDED) errorMsg = createTimeExceededMsg(code);
    else if (type == inet::ICMPv6_PARAMETER_PROBLEM) errorMsg = createParamProblemMsg(code);
    else error("Unknown ICMPv6 error type\n");

    errorMsg->encapsulate(origDatagram);

    // debugging information
    std::cout << "sending ICMP error: (" << errorMsg->getClassName() << ")" << errorMsg->getName()
       << " type=" << type << " code=" << code << std::endl;

    // ICMP message length: the internet header plus the first 8 bytes of
    // the original datagram's data is returned to the sender
    //errorMessage->setByteLength(4 + origDatagram->getHeaderLength() + 8); FIXME What is this for?

    // if srcAddr is not filled in, we're still in the src node, so we just
    // process the ICMP message locally, right away
    if (origDatagram->getSrcAddress().isUnspecified())
    {
        // pretend it came from the IP layer
//        IPv6ControlInfo *ctrlInfo = new IPv6ControlInfo();
//        ctrlInfo->setSrcAddr(IPv6Address::LOOPBACK_ADDRESS); // FIXME maybe use configured loopback address
//        ctrlInfo->setProtocol(IP_PROT_ICMP);
//        errorMsg->setControlInfo(ctrlInfo);

        // then process it locally
        processICMPv6Message(errorMsg);
    }
    else
    {
        sendToIP(errorMsg, origDatagram->getSrcAddress());
    }
}


void ICMPv6::sendErrorMessage(inet::cPacket *transportPacket, IPv6ControlInfo *ctrl, inet::ICMPv6Type type, int code)
{
    Enter_Method("sendErrorMessage(transportPacket, ctrl, type=%d, code=%d)", type, code);

    IPv6Datagram *datagram = ctrl->removeOrigDatagram();
    datagram->encapsulate(transportPacket);
    sendErrorMessage(datagram, type, code);
}

void ICMPv6::sendToIP(inet::ICMPv6Message *msg, const IPv6Address& dest)
{
    // Create control info objects
    IPv6ControlInfo *ctrlInfo = new IPv6ControlInfo();
    IPv6ControlInfo *replyCtrl = new IPv6ControlInfo();

    // Check and cast the control info from the message
    IPv6ControlInfo *ctrl = check_and_cast<IPv6ControlInfo *>(msg->getControlInfo());

    // Set the destination address for the reply control info
    replyCtrl->setDestAddr(ctrl->getSrcAddr());

    // Set protocol to ICMPv6
    ctrlInfo->setProtocol(IP_PROT_ICMP);

    // Set the control info for the message
    msg->setControlInfo(ctrlInfo);

    // Send the message to the output
    send(msg, "ipv6Out");
}


void ICMPv6::sendToIP(inet::ICMPv6Message *msg)
{
    // assumes IPControlInfo is already attached
    send(msg,"ipv6Out");
}

inet::ICMPv6Message *ICMPv6::createDestUnreachableMsg(int code)
{
    inet::ICMPv6DestUnreachableMsg *errorMsg = new inet::ICMPv6DestUnreachableMsg("Dest Unreachable");
    errorMsg->setType(inet::ICMPv6_DESTINATION_UNREACHABLE);
    errorMsg->setCode(code);
    return errorMsg;
}

inet::ICMPv6Message *ICMPv6::createPacketTooBigMsg(int mtu)
{
    inet::ICMPv6PacketTooBigMsg *errorMsg = new inet::ICMPv6PacketTooBigMsg("Packet Too Big");
    errorMsg->setType(inet::ICMPv6_PACKET_TOO_BIG);
    errorMsg->setCode(0);//Set to 0 by sender and ignored by receiver.
    errorMsg->setMTU(mtu);
    return errorMsg;
}

inet::ICMPv6Message *ICMPv6::createTimeExceededMsg(int code)
{
    inet::ICMPv6TimeExceededMsg *errorMsg = new inet::ICMPv6TimeExceededMsg("Time Exceeded");
    errorMsg->setType(inet::ICMPv6_TIME_EXCEEDED);
    errorMsg->setCode(code);
    return errorMsg;
}

inet::ICMPv6Message *ICMPv6::createParamProblemMsg(int code)
{
    inet::ICMPv6ParamProblemMsg *errorMsg = new inet::ICMPv6ParamProblemMsg("Parameter Problem");
    errorMsg->setType(inet::ICMPv6_PARAMETER_PROBLEM);
    errorMsg->setCode(code);
    //TODO: What Pointer? section 3.4
    return errorMsg;
}

bool ICMPv6::validateDatagramPromptingError(IPv6Datagram *origDatagram)
{
    // don't send ICMP error messages for multicast messages
    if (origDatagram->getDestAddress().isMulticast())
    {
        std::cout << "won't send ICMP error messages for multicast message " << origDatagram << std::endl;
        delete origDatagram;
        return false;
    }

    // do not reply with error message to error message
    if (origDatagram->getTransportProtocol() == IP_PROT_IPv6_ICMP)
    {
        inet::ICMPv6Message *recICMPMsg = check_and_cast<inet::ICMPv6Message *>(origDatagram->getEncapsulatedMsg());
        if (recICMPMsg->getType()<128)
        {
            std::cout << "ICMP error received -- do not reply to it" << std::endl;
            delete origDatagram;
            return false;
        }
    }
    return true;
}

void ICMPv6::errorOut(inet::ICMPv6Message *icmpv6msg)
{
    send(icmpv6msg, "errorOut");
}
