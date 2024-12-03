//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 Andras Varga
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


//  Cleanup and rewrite: Andras Varga, 2004
//  Implementation of IPv6 version: Wei Yang, Ng, 2005

#include <omnetpp.h>
#include "IPv6ErrorHandling.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6ControlInfo.h"
#include "IPv6Datagram.h"

Define_Module(IPv6ErrorHandling);

void IPv6ErrorHandling::initialize()
{
}

void IPv6ErrorHandling::handleMessage(inet::cMessage *msg)
{
    inet::ICMPv6Message *icmpv6Msg = check_and_cast<inet::ICMPv6Message *>(msg);
    IPv6Datagram *d = check_and_cast<IPv6Datagram *>(icmpv6Msg->getObject("encapsulatedMsg"));
    int type = (int)icmpv6Msg->getType();
    int code;
    std::cout << " Type: " << type;
    if (dynamic_cast<inet::ICMPv6DestUnreachableMsg *>(icmpv6Msg))
    {
        inet::ICMPv6DestUnreachableMsg *msg2 = (inet::ICMPv6DestUnreachableMsg *)icmpv6Msg;
        code = msg2->getCode();
        std::cout << " Code: " << code;
    }
    else if (dynamic_cast<inet::ICMPv6PacketTooBigMsg *>(icmpv6Msg))
    {
        inet::ICMPv6PacketTooBigMsg *msg2 = (inet::ICMPv6PacketTooBigMsg *)icmpv6Msg;
        code = 0;
    }
    else if (dynamic_cast<inet::ICMPv6TimeExceededMsg *>(icmpv6Msg))
    {
        inet::ICMPv6TimeExceededMsg *msg2 = (inet::ICMPv6TimeExceededMsg *)icmpv6Msg;
        code = msg2->getCode();
        std::cout  << " Code: " << code;
    }
    else if (dynamic_cast<inet::ICMPv6ParamProblemMsg *>(icmpv6Msg))
    {
        inet::ICMPv6ParamProblemMsg *msg2 = (inet::ICMPv6ParamProblemMsg *)icmpv6Msg;
        code = msg2->getCode();
        std::cout  << " Code: " << code;
    }

    std::cout  << " Byte length: " << d->getByteLength()
       << " Src: " << d->getSrcAddress()
       << " Dest: " << d->getDestAddress()
       << " Time: " << inet::simTime()
       << "\n";

    if (type == 1)
        displayType1Msg(code);
    else if (type == 2)
        displayType2Msg();
    else if (type == 3)
        displayType3Msg(code);
    else if (type == 4)
        displayType4Msg(code);
    else
        std::cout  << "Unknown Error Type!" << std::endl;
    delete icmpv6Msg;
}

void IPv6ErrorHandling::displayType1Msg(int code)
{
    std::cout  << "Destination Unreachable: ";
    if (code == 0)
        std::cout  << "no route to destination\n";
    else if (code == 1)
        std::cout  << "communication with destination administratively prohibited\n";
    else if (code == 3)
        std::cout  << "address unreachable\n";
    else if (code == 4)
        std::cout  << "port unreachable\n";
    else
        std::cout  << "Unknown Error Code!\n";
}

void IPv6ErrorHandling::displayType2Msg()
{
    std::cout  << "Packet Too Big" << std::endl;
    //Code is always 0 and ignored by the receiver.
}

void IPv6ErrorHandling::displayType3Msg(int code)
{
    std::cout  << "Time Exceeded Message: ";
    if (code == 0)
        std::cout  << "hop limit exceeded in transit\n";
    else if (code == 1)
        std::cout  << "fragment reassembly time exceeded\n";
    else
        std::cout  << "Unknown Error Code!\n";
}

void IPv6ErrorHandling::displayType4Msg(int code)
{
    std::cout  << "Parameter Problem Message: ";
    if (code == 0)
        std::cout  << "erroneous header field encountered\n";
    else if (code == 1)
        std::cout  << "unrecognized Next Header type encountered\n";
    else if (code == 2)
        std::cout  << "unrecognized IPv6 option encountered\n";
    else
        std::cout  << "Unknown Error Code!\n";
}
