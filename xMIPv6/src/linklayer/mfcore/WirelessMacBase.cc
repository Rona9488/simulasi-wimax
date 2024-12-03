/***************************************************************************
 * file:        WirelessMacBase.cc
 *
 * derived by Andras Varga using decremental programming from BasicMacLayer.cc,
 * which had the following copyright:
 *
 * author:      Daniel Willkomm
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU Lesser General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 **************************************************************************/


#include "WirelessMacBase.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\NotificationBoard.h"


void WirelessMacBase::initialize(int stage)
{
    if (stage==0)
    {
        uppergateIn  = findGate("uppergateIn");
        uppergateOut = findGate("uppergateOut");
        lowergateIn  = findGate("lowergateIn");
        lowergateOut = findGate("lowergateOut");

        // get a pointer to the NotificationBoard module
        nb = NotificationBoardAccess().get();
    }
}


void WirelessMacBase::handleMessage(inet::cMessage *msg)
{
    if (msg->isSelfMessage())
        handleSelfMsg(msg);
    else if (!msg->isPacket())
        handleCommand(msg);
    else if (msg->getArrivalGateId()==uppergateIn)
        handleUpperMsg(PK(msg));
    else
        handleLowerMsg(PK(msg));
}

bool WirelessMacBase::isUpperMsg(inet::cMessage *msg)
{
    return msg->getArrivalGateId()==uppergateIn;
}

bool WirelessMacBase::isLowerMsg(inet::cMessage *msg)
{
    return msg->getArrivalGateId()==lowergateIn;
}

void WirelessMacBase::sendDown(inet::cMessage *msg)
{
    std::cout << "sending down " << msg << "\n";
    send(msg, lowergateOut);
}

void WirelessMacBase::sendUp(inet::cMessage *msg)
{
    std::cout << "sending up " << msg << "\n";
    send(msg, uppergateOut);
}

