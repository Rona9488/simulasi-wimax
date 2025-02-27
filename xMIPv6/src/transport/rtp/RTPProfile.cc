/***************************************************************************
                          RTPProfile.cc  -  description
                             -------------------
    (C) 2007 Ahmed Ayadi  <ahmed.ayadi@sophia.inria.fr>
    (C) 2001 Matthias Oppitz <Matthias.Oppitz@gmx.de>

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** \file RTPProfile.cc
 * This file contains the implementaion of member functions of the class RTPProfile.
 */

#include <string.h>
#include "RTPProfile.h"
#include "RTPInnerPacket.h"
#include "RTPPayloadSender.h"
#include "RTPPayloadReceiver.h"
#include "RTPParticipantInfo.h"


Define_Module(RTPProfile);

RTPProfile::RTPProfile()
{
    _ssrcGates = NULL;
}

void RTPProfile::initialize()
{
    std::cout << "initialize() Enter"<<std::endl;
    _profileName = "Profile";
    _rtcpPercentage = 5;
    _preferredPort = PORT_UNDEF;

    // how many gates to payload receivers do we have
    _maxReceivers = gateSize("payloadReceiverOut");
    _ssrcGates = new inet::cArray("SSRCGates");
    _autoOutputFileNames = par("autoOutputFileNames").boolValue();
    std::cout << "initialize() Exit"<<std::endl;
}

RTPProfile::~RTPProfile()
{
    delete _ssrcGates;
}


void RTPProfile::handleMessage(inet::cMessage *msg)
{
    if (msg->getArrivalGateId() == findGate("rtpIn")) {
        handleMessageFromRTP(msg);
    }

    else if (msg->getArrivalGateId() == findGate("payloadSenderIn")) {
        handleMessageFromPayloadSender(msg);
    }

    else if (msg->getArrivalGateId() >= findGate("payloadReceiverIn") && msg->getArrivalGateId() < findGate("payloadReceiverIn") + _maxReceivers) {
        handleMessageFromPayloadReceiver(msg);
    }

    else {
        error("message coming from unknown gate");
    }

}


void RTPProfile::handleMessageFromRTP(inet::cMessage *msg)
{
    std::cout << "handleMessageFromRTP Enter "<<std::endl;

    RTPInnerPacket *rinpIn = check_and_cast<RTPInnerPacket *>(msg);

    if (rinpIn->getType() == RTPInnerPacket::RTP_INP_INITIALIZE_PROFILE) {
        initializeProfile(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_CREATE_SENDER_MODULE) {
        createSenderModule(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_DELETE_SENDER_MODULE) {
        deleteSenderModule(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_SENDER_MODULE_CONTROL) {
        senderModuleControl(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_DATA_IN) {
        dataIn(rinpIn);
    }
    else {
        error("RTPInnerPacket from RTPModule has wrong type");
    }

    std::cout << "handleMessageFromRTP Exit "<<std::endl;
}


void RTPProfile::handleMessageFromPayloadSender(inet::cMessage *msg)
{

    RTPInnerPacket *rinpIn = check_and_cast<RTPInnerPacket *>(msg);

    if (rinpIn->getType() == RTPInnerPacket::RTP_INP_DATA_OUT) {
        dataOut(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_SENDER_MODULE_INITIALIZED) {
        senderModuleInitialized(rinpIn);
    }
    else if (rinpIn->getType() == RTPInnerPacket::RTP_INP_SENDER_MODULE_STATUS) {
        senderModuleStatus(rinpIn);
    }
    else {
        error("Profile received RTPInnerPacket from sender module with wrong type");
    }

}


void RTPProfile::handleMessageFromPayloadReceiver(inet::cMessage *msg)
{
    // currently payload receiver modules don't send messages
    delete msg;
}


void RTPProfile::initializeProfile(RTPInnerPacket *rinp)
{
    std::cout << "initializeProfile Enter"<<std::endl;
    _mtu = rinp->getMTU();
    delete rinp;
    RTPInnerPacket *rinpOut = new RTPInnerPacket("profileInitialized()");
    rinpOut->profileInitialized(_rtcpPercentage, _preferredPort);
    send(rinpOut, "rtpOut");
    std::cout << "initializeProfile Exit"<<std::endl;
}


void RTPProfile::createSenderModule(RTPInnerPacket *rinp)
{
    std::cout << "createSenderModule Enter"<<std::endl;
    int ssrc = rinp->getSSRC();
    int payloadType = rinp->getPayloadType();
    char moduleName[100];

    std::cout << "ProfileName: " << _profileName << " payloadType: " << payloadType<<std::endl;
    const char *pkgPrefix = "inet.transport.rtp."; //FIXME hardcoded string
    sprintf(moduleName, "%sRTP%sPayload%iSender", pkgPrefix, _profileName, payloadType);

    inet::cModuleType *moduleType = inet::cModuleType::find(moduleName);
    if (moduleType == NULL)
    { const char* payloadReceiverName = "exampleReceiver";
        throw std::runtime_error(std::string("Receiver module type not found: ") + payloadReceiverName);
    }

    RTPPayloadSender *rtpPayloadSender = (RTPPayloadSender *)(moduleType->create(moduleName, this));
    rtpPayloadSender->finalizeParameters();

    gate("payloadSenderOut")->connectTo(rtpPayloadSender->gate("profileIn"));
    rtpPayloadSender->gate("profileOut")->connectTo(gate("payloadSenderIn"));

    rtpPayloadSender->initialize();
    rtpPayloadSender->scheduleStart(inet::simTime());

    RTPInnerPacket *rinpOut1 = new RTPInnerPacket("senderModuleCreated()");
    rinpOut1->senderModuleCreated(ssrc);
    send(rinpOut1, "rtpOut");

    RTPInnerPacket *rinpOut2 = new RTPInnerPacket("initializeSenderModule()");
    rinpOut2->initializeSenderModule(ssrc, rinp->getFileName(), _mtu);
    send(rinpOut2, "payloadSenderOut");

    delete rinp;
    std::cout << "createSenderModule Exit"<<std::endl;
}


void RTPProfile::deleteSenderModule(RTPInnerPacket *rinpIn)
{
    cModule *senderModule = gate("payloadSenderOut")->getNextGate()->getOwnerModule();
    senderModule->deleteModule();

    RTPInnerPacket *rinpOut = new RTPInnerPacket("senderModuleDeleted()");
    rinpOut->senderModuleDeleted(rinpIn->getSSRC());
    delete rinpIn;

    send(rinpOut, "rtpOut");
}


void RTPProfile::senderModuleControl(RTPInnerPacket *rinp)
{
    send(rinp, "payloadSenderOut");
}


void RTPProfile::dataIn(RTPInnerPacket *rinp)
{
    std::cout << "dataIn(RTPInnerPacket *rinp) Enter"<<std::endl;
    processIncomingPacket(rinp);

    RTPPacket *packet = check_and_cast<RTPPacket *>(rinp->getObject("encapsulatedMsg"));

    uint32_t ssrc = packet->getSSRC();

    SSRCGate *ssrcGate = findSSRCGate(ssrc);

    if (!ssrcGate) {
        ssrcGate = newSSRCGate(ssrc);
        char payloadReceiverName[100];
        const char *pkgPrefix = "inet.transport.rtp."; //FIXME hardcoded string
        sprintf(payloadReceiverName, "%sRTP%sPayload%iReceiver", pkgPrefix, _profileName, packet->getPayloadType());

        inet::cModuleType *moduleType = inet::cModuleType::find(payloadReceiverName);
        if (moduleType == NULL)
            throw std::runtime_error("Receiver module type not found: " + std::string(payloadReceiverName));

        else {
            RTPPayloadReceiver *receiverModule = (RTPPayloadReceiver *)(moduleType->create(payloadReceiverName, this));
            if (_autoOutputFileNames) {
                char outputFileName[100];
                sprintf(outputFileName, "id%i.sim", receiverModule->getId());
                receiverModule->par("outputFileName") = outputFileName;
            }
            receiverModule->finalizeParameters();

            this->gate(ssrcGate->getGateId())->connectTo(receiverModule->gate("profileIn"));
            receiverModule->gate("profileOut")->connectTo(this->gate(ssrcGate->getGateId() - findGate("payloadReceiverOut",0) + findGate("payloadReceiverIn",0)));

            receiverModule->callInitialize(0);
            receiverModule->scheduleStart(inet::simTime());
        }
    }

    send(rinp, ssrcGate->getGateId());
    std::cout << "dataIn(RTPInnerPacket *rinp) Exit"<<std::endl;
}


void RTPProfile::dataOut(RTPInnerPacket *rinp)
{
    processOutgoingPacket(rinp);
    send(rinp, "rtpOut");
}


void RTPProfile::senderModuleInitialized(RTPInnerPacket *rinp)
{
    std::cout << "senderModuleInitialized"<<std::endl;
    send(rinp, "rtpOut");
}


void RTPProfile::senderModuleStatus(RTPInnerPacket *rinp)
{
    std::cout << "senderModuleStatus"<<std::endl;
    send(rinp, "rtpOut");
}


void RTPProfile::processIncomingPacket(RTPInnerPacket *rinp)
{
    // do nothing with the packet
}


void RTPProfile::processOutgoingPacket(RTPInnerPacket *rinp)
{
    // do nothing with the packet
}


RTPProfile::SSRCGate *RTPProfile::findSSRCGate(uint32_t ssrc)
{
    const char *name = RTPParticipantInfo::ssrcToName(ssrc);
    int objectIndex = _ssrcGates->find(name);
    if (objectIndex == -1) {
        return NULL;
    }
    else {
        cObject *co = (_ssrcGates->get(objectIndex));
        return (SSRCGate *)co;
    }
}


RTPProfile::SSRCGate *RTPProfile::newSSRCGate(uint32_t ssrc)
{
    SSRCGate *ssrcGate = new SSRCGate(ssrc);
    bool assigned = false;
    int receiverGateId = findGate("payloadReceiverOut",0);
    for (int i = receiverGateId; i < receiverGateId + _maxReceivers && !assigned; i++) {
        if (!gate(i)->isConnected()) {
            ssrcGate->setGateId(i);
            assigned = true;
        }
    }

    if (!assigned)
        throw std::runtime_error("Can't manage more senders");

    _ssrcGates->add(ssrcGate);
    return ssrcGate;
}


