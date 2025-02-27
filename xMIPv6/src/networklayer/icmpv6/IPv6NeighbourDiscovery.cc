/**
 * Copyright (C) 2005 Andras Varga
 * Copyright (C) 2005 Wei Yang, Ng
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "IPv6NeighbourDiscovery.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\xmipv6\xMIPv6Access.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTableAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddressResolver.h"  // Adam
#include <C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\ModuleAccess.h>

#define MK_ASSIGN_LINKLOCAL_ADDRESS 0
#define MK_SEND_PERIODIC_RTRADV 1
#define MK_SEND_SOL_RTRADV 2
#define MK_INITIATE_RTRDIS 3
#define MK_DAD_TIMEOUT 4
#define MK_RD_TIMEOUT 5
#define MK_NUD_TIMEOUT 6
#define MK_AR_TIMEOUT 7
#define MK_AR_ASSIGN_GLOBAL_ADDRESS_WIMAX 8 // Adam

Define_Module(IPv6NeighbourDiscovery);

IPv6NeighbourDiscovery::IPv6NeighbourDiscovery()
    : neighbourCache(*this)
{
}

IPv6NeighbourDiscovery::~IPv6NeighbourDiscovery()
{
    // FIXME delete the following data structures, cancelAndDelete timers in them etc.
    // Deleting the data structures my become unnecessary if the lists store the
    // structs themselves and not pointers.
    //   RATimerList raTimerList;
    //   DADList dadList;
    //   RDList rdList;
    //   AdvIfList advIfList;
}

void IPv6NeighbourDiscovery::initialize(int stage)
{
    std::cout<<"\n++++ The IPv6NeighbourDiscovery Module Is Initialised ++++\n";
    // We have to wait until the 3rd stage (stage 2) with scheduling messages,
    // because interface registration and IPv6 configuration takes places
    // in the first two stages.

    if (stage==3)
    {
        ift = InterfaceTableAccess().get();
        ift2 = InterfaceTableAccess2().get();
        rt6 = RoutingTable6Access().get();
        icmpv6 = ICMPv6Access().get();

    if (rt6->isMobileNode())
    	mipv6 = xMIPv6Access().get();

        pendingQueue.setName("pendingQueue");

	//MIPv6Enabled = par("MIPv6Support");	// (Zarrar 14.07.07)
	/*if(rt6->isRouter()) // 12.9.07 - CB
        {
	minRAInterval = par("minIntervalBetweenRAs"); // from the omnetpp.ini file (Zarrar 15.07.07)
	maxRAInterval = par("maxIntervalBetweenRAs"); // from the omnetpp.ini file (Zarrar 15.07.07)
	//WATCH (MIPv6Enabled);	// (Zarrar 14.07.07)
	WATCH(minRAInterval);	// (Zarrar 15.07.07)
	WATCH(maxRAInterval);	// (Zarrar 15.07.07)
	}*/

        for (int i=0; i < ift->getNumInterfaces(); i++)
        {
            InterfaceEntry *ie = ift->getInterface(i);
            if (ie->ipv6Data()->getAdvSendAdvertisements() && !(ie->isLoopback()))
            {
                createRATimer(ie);
            }
        }
        //This simulates random node bootup time. Link local address assignment
        //takes place during this time.
        inet::cMessage *msg = new inet::cMessage("assignLinkLocalAddr", MK_ASSIGN_LINKLOCAL_ADDRESS);
        //We want routers to boot up faster!
        if (rt6->isRouter())
            scheduleAt(inet::simTime()+uniform(0,0.3), msg);//Random Router bootup time
        else{
            if( this->getParentModule()->getParentModule()->findSubmodule("ssInfo") != -1 )
                scheduleAt(inet::simTime()+uniform(0.4,0.7), msg);//Random Host bootup time
            else
                scheduleAt(inet::simTime()+uniform(0.4,1), msg);//Random Host bootup time
            // scheduleAt(simTime()+uniform(0.4,1), msg);//Random Host bootup time
        }

        statVectorStartDAD.setName("Starting DAD");
    }
}

void IPv6NeighbourDiscovery::handleMessage(inet::cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        std::cout << "Self message received!\n";
        if (msg->getKind()==MK_SEND_PERIODIC_RTRADV)
        {
            std::cout << "Sending periodic RA\n";
            sendPeriodicRA(msg);
        }
        else if (msg->getKind()==MK_SEND_SOL_RTRADV)
        {
            std::cout << "Sending solicited RA\n";
            sendSolicitedRA(msg);
        }
        else if (msg->getKind()==MK_ASSIGN_LINKLOCAL_ADDRESS)
        {
            std::cout << "Assigning Link Local Address\n";
            assignLinkLocalAddress(msg);
        }
        else if (msg->getKind()==MK_DAD_TIMEOUT)
        {
            std::cout << "DAD Timeout message received\n";
            processDADTimeout(msg);
        }
        else if (msg->getKind()==MK_RD_TIMEOUT)
        {
            std::cout << "Router Discovery message received\n";
            processRDTimeout(msg);
        }
        else if (msg->getKind()==MK_INITIATE_RTRDIS)
        {
            std::cout << "initiate router discovery.\n";
            initiateRouterDiscovery(msg);
        }
        else if (msg->getKind()==MK_NUD_TIMEOUT)
        {
            std::cout << "NUD Timeout message received\n";
            processNUDTimeout(msg);
        }
        else if (msg->getKind()==MK_AR_TIMEOUT)
        {
        
            std::cout << "Address Resolution Timeout message received\n";
            processARTimeout(msg);
        }
        else if (msg->getKind()==MK_AR_ASSIGN_GLOBAL_ADDRESS_WIMAX)
        {
        
            std::cout << "Address Resolution Timeout message received\n";
            CreateAndSendAssignAddressNotify();
            delete msg;
        }        
        else
            error("Unrecognized Timer");//stops sim w/ error msg.
    }
    else if (dynamic_cast<inet::ICMPv6Message *>(msg))
    {
        //This information will serve as input parameters to various processors.
        IPv6ControlInfo *ctrlInfo
            = check_and_cast<IPv6ControlInfo*>(msg->removeControlInfo());
        inet::ICMPv6Message *ndMsg = (inet::ICMPv6Message *)msg;
        processNDMessage(ndMsg, ctrlInfo);
    }
    else if (dynamic_cast<IPv6Datagram *>(msg))// not ND message
    {
        IPv6Datagram *datagram = (IPv6Datagram *)msg;
        processIPv6Datagram(datagram);
    }
    else
        error("Unknown message type received.\n");
}

void IPv6NeighbourDiscovery::processNDMessage(inet::ICMPv6Message *msg,
    IPv6ControlInfo *ctrlInfo)
{
    std::cout << "/// processNDMessage" << std::endl;

    if (dynamic_cast<inet::IPv6RouterSolicitation *>(msg))
    {
        inet::IPv6RouterSolicitation *rs = (inet::IPv6RouterSolicitation *)msg;
        std::cout << "processRSPacket" << std::endl;
        processRSPacket(rs, ctrlInfo);
    }
    else if (dynamic_cast<inet::IPv6RouterAdvertisement *>(msg))
    {
        inet::IPv6RouterAdvertisement *ra = (inet::IPv6RouterAdvertisement *)msg;
        std::cout << "processRAPacket" << std::endl;
        processRAPacket(ra, ctrlInfo);
    }
    else if (dynamic_cast<inet::IPv6NeighbourSolicitation *>(msg))
    {
        inet::IPv6NeighbourSolicitation *ns = (inet::IPv6NeighbourSolicitation *)msg;
        std::cout << "processNSPacket" << std::endl;
        processNSPacket(ns, ctrlInfo);
    }
    else if (dynamic_cast<inet::IPv6NeighbourAdvertisement *>(msg))
    {
        inet::IPv6NeighbourAdvertisement *na = (inet::IPv6NeighbourAdvertisement *)msg;
        std::cout << "processNAPacket" << std::endl;
        processNAPacket(na, ctrlInfo);
    }
    else if (dynamic_cast<inet::IPv6Redirect *>(msg))
    {
        inet::IPv6Redirect *redirect = (inet::IPv6Redirect *)msg;
        std::cout << "processRedirectPacket" << std::endl;
        processRedirectPacket(redirect, ctrlInfo);
    }
//============= Adam 10-09-2011 =====================
    else if (dynamic_cast<inet::IPv6AssignAddressNotify *>(msg))
    {
        inet::IPv6AssignAddressNotify *notify = (inet::IPv6AssignAddressNotify *)msg;
    std::cout << "process Assig nAddress Notify" << std::endl;
    setAP_InfoAndCreateMsg( notify->getAP_ID() ,notify->getL2_Addr() ,notify->getL3_Addr() ,notify->getPrefix() ,notify->getPrefixLength() );
    delete msg;
    }    
//============= Adam, end  10-09-2011==================        
    else
    {
        error("Unrecognized ND message!");
    }
}

void IPv6NeighbourDiscovery::finish()
{
}

void IPv6NeighbourDiscovery::processIPv6Datagram(IPv6Datagram *msg)
{
    std::cout << "Packet " << msg << " arrived from IPv6 module.\n";

    int nextHopIfID;
    std::cout << "Determining Next Hop" << std::endl;
    IPv6Address nextHopAddr = determineNextHop(msg->getDestAddress(), nextHopIfID);
    if (nextHopIfID == -1)
    {
        //draft-ietf-ipv6-2461bis-04 has omitted on-link assumption.
        //draft-ietf-v6ops-onlinkassumption-03 explains why.
        icmpv6->sendErrorMessage(msg, inet::ICMPv6_DESTINATION_UNREACHABLE, inet::NO_ROUTE_TO_DEST);
        return;
    }
    std::cout << "Next Hop Address is: " << nextHopAddr << " on interface: " << nextHopIfID << std::endl;

    //RFC2461: Section 5.2 Conceptual Sending Algorithm
    //Once the IP address of the next-hop node is known, the sender examines the
    //Neighbor Cache for link-layer information about that neighbor.
    Neighbour *nce = neighbourCache.lookup(nextHopAddr, nextHopIfID);

    if (nce==NULL)
    {
        //If no entry exists,
        std::cout << "No Entry exists in the Neighbour Cache.\n";

        //the sender creates one, sets its state to INCOMPLETE,
        std::cout << "Creating an INCOMPLETE entry in the neighbour cache.\n";
        nce = neighbourCache.addNeighbour(nextHopAddr, nextHopIfID);

        //initiates Address Resolution,
        std::cout << "Initiating Address Resolution for:" << nextHopAddr
           << " on Interface:" << nextHopIfID << endl;
        initiateAddressResolution(msg->getSrcAddress(), nce);

        //and then queues the data packet pending completion of address resolution.
        std::cout << "Add packet to entry's queue until Address Resolution is complete.\n";
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::INCOMPLETE)
    {
        std::cout << "Reachability State is INCOMPLETE.Address Resolution already initiated.\n";
        bubble("Packet added to queue until Address Resolution is complete.");
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->macAddress.isUnspecified())
    {
        std::cout << "NCE's MAC address is unspecified.\n";
        std::cout << "Initiate Address Resolution and add packet to queue.\n";
        initiateAddressResolution(msg->getSrcAddress(), nce);
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::STALE)
    {
        std::cout << "Reachability State is STALE.\n";
        send(msg,"ipv6Out");
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::REACHABLE)
    {
        std::cout << "Next hop is REACHABLE, sending packet to next-hop address.";
        sendPacketToIPv6Module(msg, nextHopAddr, msg->getSrcAddress(), nextHopIfID);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::DELAY)//TODO: What if NCE is in PROBE state?
    {
        std::cout << "Next hop is in DELAY state, sending packet to next-hop address.";
        sendPacketToIPv6Module(msg, nextHopAddr, msg->getSrcAddress(), nextHopIfID);
    }
    else
        error("Unknown Neighbour cache entry state.");
}

IPv6NeighbourDiscovery::AdvIfEntry *IPv6NeighbourDiscovery::fetchAdvIfEntry(InterfaceEntry *ie)
{
   for (AdvIfList::iterator it=advIfList.begin(); it!=advIfList.end(); it++)
   {
       AdvIfEntry *advIfEntry = (*it);
       if (advIfEntry->interfaceId == ie->getInterfaceId())
       {
           return advIfEntry;
       }
   }
   return NULL;
}

IPv6NeighbourDiscovery::RDEntry *IPv6NeighbourDiscovery::fetchRDEntry(InterfaceEntry *ie)
{
   for (RDList::iterator it=rdList.begin(); it!=rdList.end(); it++)
   {
       RDEntry *rdEntry = (*it);
       if (rdEntry->interfaceId == ie->getInterfaceId())
       {
           return rdEntry;
       }
   }
   return NULL;
}

const MACAddress& IPv6NeighbourDiscovery::resolveNeighbour(const IPv6Address& nextHop, int interfaceId)
{
    Enter_Method("resolveNeighbor(%s,if=%d)", nextHop.str().c_str(), interfaceId);

    Neighbour *nce = neighbourCache.lookup(nextHop, interfaceId);
    //InterfaceEntry *ie = ift->getInterfaceById(interfaceId);

    if (!nce || nce->reachabilityState==IPv6NeighbourCache::INCOMPLETE)
        return MACAddress::UNSPECIFIED_ADDRESS;
    else if (nce->reachabilityState==IPv6NeighbourCache::STALE)
        initiateNeighbourUnreachabilityDetection(nce);
    else if (nce->reachabilityState==IPv6NeighbourCache::REACHABLE &&
            inet::simTime() > nce->reachabilityExpires)
    {
        nce->reachabilityState = IPv6NeighbourCache::STALE;
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState!=IPv6NeighbourCache::REACHABLE)
    {
        //reachability state must be either in DELAY or PROBE
        ASSERT(nce->reachabilityState==IPv6NeighbourCache::DELAY ||
               nce->reachabilityState==IPv6NeighbourCache::PROBE);
        std::cout << "NUD in progress.\n";
    }
    //else the entry is REACHABLE and no further action is required here.
    return nce->macAddress;
}

void IPv6NeighbourDiscovery::reachabilityConfirmed(const IPv6Address& neighbour, int interfaceId)
{
    Enter_Method("reachabilityConfirmed(%s,if=%d)", neighbour.str().c_str(), interfaceId);
    //hmmm... this should only be invoked if a TCP ACK was received and NUD is
    //currently being performed on the neighbour where the TCP ACK was received from.

    Neighbour *nce = neighbourCache.lookup(neighbour, interfaceId);

    inet::cMessage *msg = nce->nudTimeoutEvent;
    if (msg != NULL)
    {
        std::cout << "NUD in progress. Cancelling NUD Timer\n";
        bubble("Reachability Confirmed via NUD.");
        cancelEvent(msg);
        delete msg;
    }
    nce->nudTimeoutEvent = NULL; // update 20.09.07 - CB

    // TODO (see header file for description)
    /*A neighbor is considered reachable if the node has recently received
    a confirmation that packets sent recently to the neighbor were
    received by its IP layer.  Positive confirmation can be gathered in
    two ways: hints from upper layer protocols that indicate a connection
    is making "forward progress", or receipt of a Neighbor Advertisement
    message that is a response to a Neighbor Solicitation message.

    A connection makes "forward progress" if the packets received from a
    remote peer can only be arriving if recent packets sent to that peer
    are actually reaching it.  In TCP, for example, receipt of a (new)
    acknowledgement indicates that previously sent data reached the peer.
    Likewise, the arrival of new (non-duplicate) data indicates that

    earlier acknowledgements are being delivered to the remote peer.  If
    packets are reaching the peer, they must also be reaching the
    sender's next-hop neighbor; thus "forward progress" is a confirmation
    that the next-hop neighbor is reachable.  For off-link destinations,
    forward progress implies that the first-hop router is reachable.
    When available, this upper-layer information SHOULD be used.

    In some cases (e.g., UDP-based protocols and routers forwarding
    packets to hosts) such reachability information may not be readily
    available from upper-layer protocols.  When no hints are available
    and a node is sending packets to a neighbor, the node actively probes
    the neighbor using unicast Neighbor Solicitation messages to verify
    that the forward path is still working.

    The receipt of a solicited Neighbor Advertisement serves as
    reachability confirmation, since advertisements with the Solicited
    flag set to one are sent only in response to a Neighbor Solicitation.
    Receipt of other Neighbor Discovery messages such as Router
    Advertisements and Neighbor Advertisement with the Solicited flag set
    to zero MUST NOT be treated as a reachability confirmation.  Receipt
    of unsolicited messages only confirm the one-way path from the sender
    to the recipient node.  In contrast, Neighbor Unreachability
    Detection requires that a node keep track of the reachability of the
    forward path to a neighbor from the its perspective, not the
    neighbor's perspective.  Note that receipt of a solicited
    advertisement indicates that a path is working in both directions.
    The solicitation must have reached the neighbor, prompting it to
    generate an advertisement.  Likewise, receipt of an advertisement
    indicates that the path from the sender to the recipient is working.
    However, the latter fact is known only to the recipient; the
    advertisement's sender has no direct way of knowing that the
    advertisement it sent actually reached a neighbor.  From the
    perspective of Neighbor Unreachability Detection, only the
    reachability of the forward path is of interest.*/
}

IPv6Address IPv6NeighbourDiscovery::determineNextHop(
    const IPv6Address& destAddr, int& outIfID)
{
    IPv6Address nextHopAddr;

    //RFC 2461 Section 5.2
    //Next-hop determination for a given unicast destination operates as follows.

    //The sender performs a longest prefix match against the Prefix List to
    //determine whether the packet's destination is on- or off-link.
    std::cout << "Find out if supplied dest addr is on-link or off-link.\n";
    const IPv6Route *route = rt6->doLongestPrefixMatch(destAddr);

    if (route != NULL)
    {
        //If the destination is on-link, the next-hop address is the same as the
        //packet's destination address.
        if (route->getNextHop().isUnspecified())
        {
            std::cout << "Dest is on-link, next-hop addr is same as dest addr.\n";
            outIfID = route->getInterfaceId();
            nextHopAddr = destAddr;
        }
        else
        {
            std::cout << "A next-hop address was found with the route, dest is off-link\n";
            std::cout << "Assume next-hop address as the selected default router.\n";
            outIfID = route->getInterfaceId();
            nextHopAddr = route->getNextHop();
        }
    }
    else
    {
        //Otherwise, the sender selects a router from the Default Router List
        //(following the rules described in Section 6.3.6).

        std::cout << "No routes were found, Dest addr is off-link.\n";
        nextHopAddr = selectDefaultRouter(outIfID);

        if (outIfID == -1) std::cout << "No Default Routers were found.";
        else std::cout << "Default router found.\n";
    }

    /*the results of next-hop determination computations are saved in the Destination
    Cache (which also contains updates learned from Redirect messages).*/
    rt6->updateDestCache(destAddr, nextHopAddr, outIfID);
    return nextHopAddr;
}

void IPv6NeighbourDiscovery::initiateNeighbourUnreachabilityDetection(
    Neighbour *nce)
{
    ASSERT(nce->reachabilityState==IPv6NeighbourCache::STALE);
    const Key *nceKey = nce->nceKey;
    std::cout << "Initiating Neighbour Unreachability Detection";
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    std::cout << "Setting NCE state to DELAY.\n";
    /*The first time a node sends a packet to a neighbor whose entry is
    STALE, the sender changes the state to DELAY*/
    nce->reachabilityState = IPv6NeighbourCache::DELAY;

    /*and sets a timer to expire in DELAY_FIRST_PROBE_TIME seconds.*/
    inet::cMessage *msg = new inet::cMessage("NUDTimeout", MK_NUD_TIMEOUT);
    msg->setContextPointer(nce);
    nce->nudTimeoutEvent = msg;
    scheduleAt(inet::simTime()+ie->ipv6Data()->_getDelayFirstProbeTime(), msg);
}

void IPv6NeighbourDiscovery::processNUDTimeout(inet::cMessage *timeoutMsg)
{
    std::cout << "NUD has timed out\n";
    Neighbour *nce = (Neighbour *) timeoutMsg->getContextPointer();
    const Key *nceKey = nce->nceKey;
    if ( nceKey == NULL ) // 19.09.07 - CB
    	throw inet::cException("nce->MAC=%s, isRouter=%d", nce->macAddress.str().c_str(), nce->isRouter);
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    if (nce->reachabilityState == IPv6NeighbourCache::DELAY)
    {
        /*If the entry is still in the DELAY state when the timer expires, the
        entry's state changes to PROBE. If reachability confirmation is received,
        the entry's state changes to REACHABLE.*/
        std::cout << "Neighbour Entry is still in DELAY state.\n";
        std::cout << "Entering PROBE state. Sending NS probe.\n";
        nce->reachabilityState = IPv6NeighbourCache::PROBE;
        nce->numProbesSent = 0;
    }

    /*If no response is received after waiting RetransTimer milliseconds
    after sending the MAX_UNICAST_SOLICIT solicitations, retransmissions cease
    and the entry SHOULD be deleted. Subsequent traffic to that neighbor will
    recreate the entry and performs address resolution again.*/
    if (nce->numProbesSent == (int)ie->ipv6Data()->_getMaxUnicastSolicit())
    {
        std::cout << "Max number of probes have been sent." << std::endl;
        std::cout << "Neighbour is Unreachable, removing NCE." << std::endl;
        neighbourCache.remove(nceKey->address, nceKey->interfaceID);
        return;
    }

    /*Upon entering the PROBE state, a node sends a unicast Neighbor Solicitation
    message to the neighbor using the cached link-layer address.*/
    createAndSendNSPacket(nceKey->address, nceKey->address,
        ie->ipv6Data()->getPreferredAddress(), ie);
    nce->numProbesSent++;
    /*While in the PROBE state, a node retransmits Neighbor Solicitation messages
    every RetransTimer milliseconds until reachability confirmation is obtained.
    Probes are retransmitted even if no additional packets are sent to the
    neighbor.*/
    scheduleAt(inet::simTime()+ie->ipv6Data()->_getRetransTimer(), timeoutMsg);
}

IPv6Address IPv6NeighbourDiscovery::selectDefaultRouter(int& outIfID)
{
    std::cout << "Selecting default router...\n";
    //draft-ietf-ipv6-2461bis-04.txt Section 6.3.6
    /*The algorithm for selecting a router depends in part on whether or not a
    router is known to be reachable. The exact details of how a node keeps track
    of a neighbor's reachability state are covered in Section 7.3.  The algorithm
    for selecting a default router is invoked during next-hop determination when
    no Destination Cache entry exists for an off-link destination or when
    communication through an existing router appears to be failing.  Under normal
    conditions, a router would be selected the first time traffic is sent to a
    destination, with subsequent traffic for that destination using the same router
    as indicated in the Destination Cache modulo any changes to the Destination
    Cache caused by Redirect messages.

    The policy for selecting routers from the Default Router List is as
    follows:*/

    IPv6Address routerAddr;
    //Cycle through all entries in the neighbour cache entry.
    for(IPv6NeighbourCache::iterator it=neighbourCache.begin(); it != neighbourCache.end(); it++)
    {
        Key key = it->first;
        Neighbour nce = it->second;
        bool routerExpired = false;
        if (nce.isDefaultRouter)
        {
            if (inet::simTime()>nce.routerExpiryTime)
            {
                std::cout << "Found an expired default router. Deleting entry...\n";
                neighbourCache.remove(key.address,key.interfaceID);
                routerExpired = true;
            }
        }

        if (routerExpired == false)
        {
            if (nce.reachabilityState == IPv6NeighbourCache::REACHABLE ||
                nce.reachabilityState == IPv6NeighbourCache::STALE ||
                nce.reachabilityState == IPv6NeighbourCache::DELAY)//TODO: Need to improve this algorithm!
            {
                std::cout << "Found a router in the neighbour cache(default router list).\n";
                outIfID = key.interfaceID;
                if (routerExpired == false) return key.address;
            }
        }
    }
    std::cout << "No suitable routers found.\n";

    /*1) Routers that are reachable or probably reachable (i.e., in any state
    other than INCOMPLETE) SHOULD be preferred over routers whose reachability
    is unknown or suspect (i.e., in the INCOMPLETE state, or for which no Neighbor
    Cache entry exists). An implementation may choose to always return the same
    router or cycle through the router list in a round-robin fashion as long as
    it always returns a reachable or a probably reachable router when one is
    available.*/

    /*2) When no routers on the list are known to be reachable or probably
    reachable, routers SHOULD be selected in a round-robin fashion, so that
    subsequent requests for a default router do not return the same router until
    all other routers have been selected.

    Cycling through the router list in this case ensures that all available
    routers are actively probed by the Neighbor Unreachability Detection algorithm.
    A request for a default router is made in conjunction with the sending of a
    packet to a router, and the selected router will be probed for reachability
    as a side effect.*/

    outIfID = -1;//nothing found yet
    return IPv6Address();
}

void IPv6NeighbourDiscovery::timeoutPrefixEntry(const IPv6Address& destPrefix,
    int prefixLength)//REDUNDANT
{
    //RFC 2461: Section 6.3.5
    /*Whenever the invalidation timer expires for a Prefix List entry, that
    entry is discarded.*/
    rt6->removeOnLinkPrefix(destPrefix, prefixLength);
    //hmmm... should the unicast address associated with this prefix be deleted
    //as well?-TODO: The address should be timeout/deleted as well!!

    /*No existing Destination Cache entries need be updated, however. Should a
    reachability problem arise with an existing Neighbor Cache entry, Neighbor
    Unreachability Detection will perform any needed recovery.*/
}

void IPv6NeighbourDiscovery::timeoutDefaultRouter(const IPv6Address& addr,
    int interfaceID)
{
    //RFC 2461: Section 6.3.5
    /*Whenever the Lifetime of an entry in the Default Router List expires,
    that entry is discarded.*/
    neighbourCache.remove(addr, interfaceID);

    /*When removing a router from the Default Router list, the node MUST update
    the Destination Cache in such a way that all entries using the router perform
    next-hop determination again rather than continue sending traffic to the
    (deleted) router.*/
    rt6->purgeDestCacheEntriesToNeighbour(addr, interfaceID);
}

void IPv6NeighbourDiscovery::initiateAddressResolution(const IPv6Address& dgSrcAddr,
    Neighbour *nce)
{
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    IPv6Address neighbourAddr = nceKey->address;
    int ifID = nceKey->interfaceID;

    //RFC2461: Section 7.2.2
    //When a node has a unicast packet to send to a neighbor, but does not
    //know the neighbor's link-layer address, it performs address
    //resolution.  For multicast-capable interfaces this entails creating a
    //Neighbor Cache entry in the INCOMPLETE state(already created if not done yet)
    //WEI-If entry already exists, we still have to ensure that its state is INCOMPLETE.
    nce->reachabilityState = IPv6NeighbourCache::INCOMPLETE;

    //and transmitting a Neighbor Solicitation message targeted at the
    //neighbor.  The solicitation is sent to the solicited-node multicast
    //address "corresponding to"(or "derived from") the target address.
    //(in this case, the target address is the address we are trying to resolve)
    std::cout << "Preparing to send NS to solicited-node multicast group\n";
    std::cout << "on the next hop interface\n";
    IPv6Address nsDestAddr = neighbourAddr.formSolicitedNodeMulticastAddress();//for NS datagram
    IPv6Address nsTargetAddr = neighbourAddr;//for the field within the NS
    IPv6Address nsSrcAddr;

    /*If the source address of the packet prompting the solicitation is the
    same as one of the addresses assigned to the outgoing interface,*/
    if (ie->ipv6Data()->hasAddress(dgSrcAddr))
        /*that address SHOULD be placed in the IP Source Address of the outgoing
        solicitation.*/
        nsSrcAddr = dgSrcAddr;
    else
        /*Otherwise, any one of the addresses assigned to the interface
        should be used.*/
        nsSrcAddr = ie->ipv6Data()->getPreferredAddress();
    ASSERT(ifID != -1);
    //Sending NS on specified interface.
    createAndSendNSPacket(nsTargetAddr, nsDestAddr, nsSrcAddr, ie);
    nce->numOfARNSSent = 1;
    nce->nsSrcAddr = nsSrcAddr;

    /*While awaiting a response, the sender SHOULD retransmit Neighbor Solicitation
    messages approximately every RetransTimer milliseconds, even in the absence
    of additional traffic to the neighbor. Retransmissions MUST be rate-limited
    to at most one solicitation per neighbor every RetransTimer milliseconds.*/
    inet::cMessage *msg = new inet::cMessage("arTimeout", MK_AR_TIMEOUT);//AR msg timer
    nce->arTimer = msg;
    msg->setContextPointer(nce);
    scheduleAt(inet::simTime()+ie->ipv6Data()->_getRetransTimer(), msg);
}


void IPv6NeighbourDiscovery::processARTimeout(inet::cMessage *arTimeoutMsg)
{
    //AR timeouts are cancelled when a valid solicited NA is received.
    Neighbour *nce = (Neighbour *)arTimeoutMsg->getContextPointer();
    const Key *nceKey = nce->nceKey;
    IPv6Address nsTargetAddr = nceKey->address;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);
    std::cout << "Num Of NS Sent:" << nce->numOfARNSSent << std::endl;
    std::cout << "Max Multicast Solicitation:" << ie->ipv6Data()->_getMaxMulticastSolicit() << std::endl;
    if (nce->numOfARNSSent < ie->ipv6Data()->_getMaxMulticastSolicit())
    {
        std::cout << "Sending another Address Resolution NS message" << std::endl;
        IPv6Address nsDestAddr = nsTargetAddr.formSolicitedNodeMulticastAddress();
        createAndSendNSPacket(nsTargetAddr, nsDestAddr, nce->nsSrcAddr, ie);
        nce->numOfARNSSent++;
        scheduleAt(inet::simTime()+ie->ipv6Data()->_getRetransTimer(), arTimeoutMsg);
        return;
    }
    std::cout << "Address Resolution has failed." << std::endl;
    dropQueuedPacketsAwaitingAR(nce);
    std::cout << "Deleting AR timeout msg\n";
    delete arTimeoutMsg;
}

void IPv6NeighbourDiscovery::dropQueuedPacketsAwaitingAR(Neighbour *nce)
{
    const Key *nceKey = nce->nceKey;
    //RFC 2461: Section 7.2.2
    /*If no Neighbor Advertisement is received after MAX_MULTICAST_SOLICIT
    solicitations, address resolution has failed. The sender MUST return ICMP
    destination unreachable indications with code 3 (Address Unreachable) for
    each packet queued awaiting address resolution.*/
    MsgPtrVector pendingPackets = nce->pendingPackets;
    std::cout << "Pending Packets empty:" << pendingPackets.empty() << std::endl;
    while (!pendingPackets.empty())
    {
        MsgPtrVector::iterator i = pendingPackets.begin();
        inet::cMessage *msg = (*i);
        IPv6Datagram *ipv6Msg = (IPv6Datagram *)msg;
        //Assume msg is the packet itself. I need the datagram's source addr.
        //The datagram's src addr will be the destination of the unreachable msg.
        std::cout << "Sending ICMP unreachable destination." << std::endl;
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        icmpv6->sendErrorMessage(ipv6Msg, inet::ICMPv6_DESTINATION_UNREACHABLE, inet::ADDRESS_UNREACHABLE);
    }

    //RFC 2461: Section 7.3.3
    /*If address resolution fails, the entry SHOULD be deleted, so that subsequent
    traffic to that neighbor invokes the next-hop determination procedure again.*/
    std::cout << "Removing neighbour cache entry" << std::endl;
    neighbourCache.remove(nceKey->address, nceKey->interfaceID);
}

void IPv6NeighbourDiscovery::sendPacketToIPv6Module(inet::cMessage *msg, const IPv6Address& destAddr,
        const IPv6Address& srcAddr, int interfaceId)
    {
        IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
        controlInfo->setProtocol(IP_PROT_IPv6_ICMP);
        controlInfo->setDestAddr(destAddr);
        controlInfo->setSrcAddr(srcAddr);
        controlInfo->setHopLimit(255);
        controlInfo->setInterfaceId(interfaceId);
        msg->setControlInfo(controlInfo);

        send(msg,"ipv6Out");

}


/**Not used yet-unsure if we really need it. --DELETED, Andras*/

void IPv6NeighbourDiscovery::sendQueuedPacketsToIPv6Module(Neighbour *nce)
{
    MsgPtrVector& pendingPackets = nce->pendingPackets;
    while(!pendingPackets.empty())//FIXME: pendingPackets are always empty!!!!
    {
        MsgPtrVector::iterator i = pendingPackets.begin();
        inet::cMessage *msg = (*i);
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        std::cout << "Sending queued packet " << msg << std::endl;
        send(msg,"ipv6Out");
    }
}

void IPv6NeighbourDiscovery::assignLinkLocalAddress(inet::cMessage *timerMsg)
{
    //Node has booted up. Start assigning a link-local address for each
    //interface in this node.
    for (int i=0; i < ift->getNumInterfaces(); i++)
    {
        InterfaceEntry *ie = ift->getInterface(i);

        //Skip the loopback interface.
        if (ie->isLoopback()) continue;

        IPv6Address linkLocalAddr = ie->ipv6Data()->getLinkLocalAddress();
        if (linkLocalAddr.isUnspecified())
        {
            //if no link local address exists for this interface, we assign one to it.
            std::cout << "No link local address exists. Forming one" << std::endl;
            linkLocalAddr = IPv6Address().formLinkLocalAddress(ie->getInterfaceToken());
            ie->ipv6Data()->assignAddress(linkLocalAddr, true, 0, 0);
        }

        //Before we can use this address, we MUST initiate DAD first.
        initiateDAD(linkLocalAddr, ie);
    }
    delete timerMsg;
}

void IPv6NeighbourDiscovery::initiateDAD(const IPv6Address& tentativeAddr,
    InterfaceEntry *ie)
{
    Enter_Method_Silent();
    std::cout<<"----------INITIATING DUPLICATE ADDRESS DISCOVERY----------"<<std::endl;
	ie->ipv6Data()->setDADInProgress(true);
    DADEntry *dadEntry = new DADEntry();
    dadEntry->interfaceId = ie->getInterfaceId();
    dadEntry->address = tentativeAddr;
    dadEntry->numNSSent = 0;
    dadList.insert(dadEntry);
    /*
    RFC2462: Section 5.4.2
    To check an address, a node sends DupAddrDetectTransmits Neighbor
    Solicitations, each separated by RetransTimer milliseconds. The
    solicitation's Target Address is set to the address being checked,
    the IP source is set to the unspecified address and the IP
    destination is set to the solicited-node multicast address of the
    target address.*/
    IPv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
    //Send a NS
    createAndSendNSPacket(tentativeAddr, destAddr,
        IPv6Address::UNSPECIFIED_ADDRESS, ie);
    dadEntry->numNSSent++;

    inet::cMessage *msg = new inet::cMessage("dadTimeout", MK_DAD_TIMEOUT);
    msg->setContextPointer(dadEntry);
    // update: added uniform(0,1) to account for joining the solicited-node multicast
    // group which is delay up to one 1 second (RFC 4862, 5.4.2) - 16.01.08, CB
    scheduleAt(inet::simTime()+ie->ipv6Data()->getRetransTimer()+uniform(0,1), msg);

    statVectorStartDAD.record(1);
}

void IPv6NeighbourDiscovery::processDADTimeout(inet::cMessage *msg)
{
    DADEntry *dadEntry = (DADEntry *)msg->getContextPointer();
    InterfaceEntry *ie = (InterfaceEntry *)ift->getInterfaceById(dadEntry->interfaceId);
    IPv6Address tentativeAddr = dadEntry->address;
    //Here, we need to check how many DAD messages for the interface entry were
    //sent vs. DupAddrDetectTransmits
    std::cout << "numOfDADMessagesSent is: " << dadEntry->numNSSent << std::endl;
    std::cout << "dupAddrDetectTrans is: " << ie->ipv6Data()->dupAddrDetectTransmits() << std::endl;
    if (dadEntry->numNSSent < ie->ipv6Data()->dupAddrDetectTransmits())
    {
        bubble("Sending another DAD NS message.");
        IPv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
        createAndSendNSPacket(dadEntry->address, destAddr, IPv6Address::UNSPECIFIED_ADDRESS, ie);
        dadEntry->numNSSent++;
        //Reuse the received msg
        scheduleAt(inet::simTime()+ie->ipv6Data()->getRetransTimer(), msg);
    }
    else
    {
        bubble("Max number of DAD messages for interface sent. Address is unique.");
        ie->ipv6Data()->permanentlyAssign(tentativeAddr);
        dadList.erase(dadEntry);
        std::cout << "delete dadEntry and msg\n";
        delete dadEntry;
        delete msg;
        ie->ipv6Data()->setDADInProgress(false);

        // update 28.09.07 - CB
        // after the link-local address was verified to be unique
        // we can assign the address and initiate the MIPv6 protocol
        // in case there are any pending entries in the list
        DADGlobalList::iterator it = dadGlobalList.find(ie);
        if ( it != dadGlobalList.end() )
        {
        	DADGlobalEntry& entry = it->second;

        	ie->ipv6Data()->assignAddress(entry.addr, false, inet::simTime()+entry.validLifetime,
        			inet::simTime()+entry.preferredLifetime, entry.hFlag);

        	// moved from processRAPrefixInfoForAddrAutoConf()
        	// we can remove the old CoA now
        	if ( !entry.CoA.isUnspecified() )
        		ie->ipv6Data()->removeAddress(entry.CoA);

        	// set addresses on this interface to tentative=false
        	for (int i=0; i < ie->ipv6Data()->getNumAddresses(); i++ )
			{
				// TODO improve this code so that only addresses are permanently assigned
        		// which are formed based on the new prefix from the RA
				IPv6Address addr = ie->ipv6Data()->getAddress(i);
				ie->ipv6Data()->permanentlyAssign(addr);
			}

        	// if we have MIPv6 protocols on this node we will eventually have to
        	// call some appropriate methods
        	if ( rt6->isMobileNode() )
        	{
		    	if ( entry.hFlag == false ){ // if we are not in the home network, send BUs
		    	    std::cout << std::endl << std::endl << ">>>>>>>>>>>>> SEND BU <<<<<<<<<<<<" << std::endl;
		  			mipv6->initiateMIPv6Protocol(ie, tentativeAddr);
                }
		  		/*
		    	else if ( entry.returnedHome ) // if we are again in the home network
		  		{
		  			ASSERT(entry.CoA.isUnspecified() == false);
		  			mipv6->returningHome(entry.CoA, ie); // initiate the returning home procedure
		  		}*/
        	}

        	dadGlobalList.erase(it->first);
        }

        // an optimization to make sure that the access router on the link gets our L2 address
        //sendUnsolicitedNA(ie);
// =================================Start: Zarrar Yousaf 08.07.07 ===============================================
/* == Calling the routine to assign global scope adddresses to the the routers only. At present during the simulation initialization, the FlatNetworkConfigurator6 assigns a 64 bit prefix to the routers but for xMIPv6 operation, we need full 128bit global scope address, only for routers. The call to  autoConfRouterGlobalScopeAddress() will autoconfigure the full 128 bit global scope address, which will be used by the MN in its BU message destination address, especially for home registeration.
*/
        if (rt6->isRouter() && !(ie->isLoopback())) {
            for(int i=0; i< ie->ipv6Data()->getNumAdvPrefixes();i++) {
                IPv6Address globalAddress = ie->ipv6Data()->autoConfRouterGlobalScopeAddress(i);
                ie->ipv6Data()->assignAddress(globalAddress, false, 0, 0);

        //=== Adam ==================================================================
                if( this->getParentModule()->getParentModule()->getSubmodule("bsIPv6") && ift->getInterface(1) == ie ){ 
                // jesli interface to WiMAX BS        
                    std::cout << "ie->info = " << ie->info() << std::endl;
                    std::cout << "index BS = " << this->getParentModule()->getParentModule()->getIndex() << std::endl;
                    // ustawienie AP_Info dla BSa
                    setAP_InfoAndCreateMsg( this->getParentModule()->getParentModule()->getIndex() ,ie->getMacAddress() ,globalAddress ,ie->ipv6Data()->getAdvPrefix(i).prefix, ie->ipv6Data()->getAdvPrefix(i).prefixLength   );
                }
        //=== Adam end ==============================================================
        // 		ie->ipv6Data()->deduceAdvPrefix(); //commented out but the above two statements can be replaced with this single statement. But i am using the above two statements for clarity reasons.
            }
        }
// ==================================End: Zarrar Yousaf 08.07.07===========================================
        /*RFC 2461: Section 6.3.7 2nd Paragraph
        Before a host sends an initial solicitation, it SHOULD delay the
        transmission for a random amount of time between 0 and
        MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
        many hosts start up on a link at the same time, such as might happen
        after recovery from a power failure.*/
        //TODO: Placing these operations here means fast router solicitation is
        //not adopted. Will relocate.
        if (ie->ipv6Data()->getAdvSendAdvertisements() == false)
        {
            std::cout << "creating router discovery message timer\n";
            inet::cMessage *rtrDisMsg = new inet::cMessage("initiateRTRDIS",MK_INITIATE_RTRDIS);
            rtrDisMsg->setContextPointer(ie);
            inet::simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay()); // random delay
            scheduleAt(inet::simTime()+interval, rtrDisMsg);
        }
    }
}

//=== Adam ,ustawia we wszystkch BSach tablice AP_Info ======================
void IPv6NeighbourDiscovery::setAP_InfoAndCreateMsg(int BSindex ,MACAddress Macaddr ,IPv6Address IPv6Addr ,IPv6Address prefix ,int prefixLength )
{
    std::cout << "Changing AP_InfoTable" << std::endl;
    std::cout << "MACAddress = " << Macaddr.str() << std::endl;
    std::cout << "IPv6Addr = " << IPv6Addr.str() << std::endl;
    std::cout << "prefix = " << prefix.str() << std::endl;
    std::cout << "prefixLength = " << prefixLength << std::endl;

    
    ift2 -> setAP_Info( BSindex ,Macaddr ,IPv6Addr ,prefix ,prefixLength );
    if( BSindex == this->getParentModule()->getParentModule()->getIndex() ){
        // jesli AR sam dostal nowy adres to wysyla do innych ARow msg o tym ( u mnie tylko 2 ARy )
        // wyslac self msg po 5 sek od otrzymania globalnego adresu WiMAX
        inet::cMessage *assignTimeout = new inet::cMessage("TimeoutAssignAddressNotify", MK_AR_ASSIGN_GLOBAL_ADDRESS_WIMAX);
        scheduleAt(inet::simTime()+5, assignTimeout);
    }
    
}

void IPv6NeighbourDiscovery::CreateAndSendAssignAddressNotify()
{
    inet::IPv6AssignAddressNotify *assign = new inet::IPv6AssignAddressNotify("IPv6AssignAddressNotify");
    InterfaceEntry *ie = ift -> getInterface(2);    // eth BS
    
    int myIndex = this->getParentModule()->getParentModule()->getIndex();
    
    assign -> setAP_ID( myIndex );
    assign -> setL2_Addr( ift2->getL2_Addr(myIndex) );
    assign -> setL3_Addr( ift2->getL3_Addr(myIndex) );
    assign -> setPrefix( ift2->getPrefix(myIndex) );
    assign -> setPrefixLength( ift2->getPrefixLength(myIndex) );

    IPv6Address myIPv6Address = ie->ipv6Data()->getPreferredAddress();
    IPv6Address destAddr;
    
    if( this->getParentModule()->getParentModule()->getIndex() == 0 ){  // jesli BS[0]
        destAddr = IPAddressResolver().resolve("BS[1]").get6();
        ASSERT(!destAddr.isUnspecified());
    }else{  // jesli BS[1]
        destAddr = IPAddressResolver().resolve("BS[0]").get6();
        ASSERT(!destAddr.isUnspecified());
    }
    
    sendPacketToIPv6Module(assign, destAddr, myIPv6Address, ie->getInterfaceId());
}

//=== Adam end ==============================================================

inet::IPv6RouterSolicitation *IPv6NeighbourDiscovery::createAndSendRSPacket(InterfaceEntry *ie)
{
    ASSERT(ie->ipv6Data()->getAdvSendAdvertisements() == false);
    //RFC 2461: Section 6.3.7 Sending Router Solicitations
    //A host sends Router Solicitations to the All-Routers multicast address. The
    //IP source address is set to either one of the interface's unicast addresses
    //or the unspecified address.
    IPv6Address myIPv6Address = ie->ipv6Data()->getPreferredAddress();
    if (myIPv6Address.isUnspecified())
        myIPv6Address = ie->ipv6Data()->getLinkLocalAddress();//so we use the link local address instead
    if (ie->ipv6Data()->isTentativeAddress(myIPv6Address))
        myIPv6Address = IPv6Address::UNSPECIFIED_ADDRESS;//set my IPv6 address to unspecified.
    IPv6Address destAddr = IPv6Address::ALL_ROUTERS_2;//all_routers multicast
    inet::IPv6RouterSolicitation *rs = new inet::IPv6RouterSolicitation("RSpacket");
    rs->setType(inet::ICMPv6_ROUTER_SOL);

    //The Source Link-Layer Address option SHOULD be set to the host's link-layer
    //address, if the IP source address is not the unspecified address.
    if (!myIPv6Address.isUnspecified())
        rs->setSourceLinkLayerAddress(ie->getMacAddress());

    //Construct a Router Solicitation message
    sendPacketToIPv6Module(rs, destAddr, myIPv6Address, ie->getInterfaceId());
    return rs;
}

void IPv6NeighbourDiscovery::initiateRouterDiscovery(inet::cMessage *msg)
{
    std::cout << "Initiating Router Discovery" << std::endl;
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    delete msg;
    //RFC2461: Section 6.3.7
    /*When an interface becomes enabled, a host may be unwilling to wait for the
    next unsolicited Router Advertisement to locate default routers or learn
    prefixes.  To obtain Router Advertisements quickly, a host SHOULD transmit up
    to MAX_RTR_SOLICITATIONS Router Solicitation messages each separated by at
    least RTR_SOLICITATION_INTERVAL seconds.(FIXME:Therefore this should be invoked
    at the beginning of the simulation-WEI)*/
    RDEntry *rdEntry = new RDEntry();
    rdEntry->interfaceId = ie->getInterfaceId();
    rdEntry->numRSSent = 0;
    createAndSendRSPacket(ie);
    rdEntry->numRSSent++;

    //Create and schedule a message for retransmission to this module
    inet::cMessage *rdTimeoutMsg = new inet::cMessage("processRDTimeout", MK_RD_TIMEOUT);
    rdTimeoutMsg->setContextPointer(ie);
    rdEntry->timeoutMsg = rdTimeoutMsg;
    rdList.insert(rdEntry);
    /*Before a host sends an initial solicitation, it SHOULD delay the
    transmission for a random amount of time between 0 and
    MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
    many hosts start up on a link at the same time, such as might happen
    after recovery from a power failure.  If a host has already performed
    a random delay since the interface became (re)enabled (e.g., as part
    of Duplicate Address Detection [ADDRCONF]) there is no need to delay
    again before sending the first Router Solicitation message.*/
    //simtime_t rndInterval = uniform(0, ie->ipv6Data()->_getMaxRtrSolicitationDelay());
    scheduleAt(inet::simTime()+ie->ipv6Data()->_getRtrSolicitationInterval(), rdTimeoutMsg);
}

void IPv6NeighbourDiscovery::cancelRouterDiscovery(InterfaceEntry *ie)
{
    //Next we retrieve the rdEntry with the Interface Entry.
    RDEntry *rdEntry = fetchRDEntry(ie);
    if (rdEntry != NULL)
    {
        std::cout << "rdEntry is not NULL, RD cancelled!" << std::endl;
        
        cancelEvent(rdEntry->timeoutMsg);
        //rdEntry->timeoutMsg = NULL;  // FIX 18.12.07 - CB
        rdList.erase(rdEntry);
        delete rdEntry;
        //rdEntry = NULL; // FIX 18.12.07 - CB
    }
    else
        std::cout << "rdEntry is NULL, not cancelling RD!" << std::endl;
}

void IPv6NeighbourDiscovery::processRDTimeout(inet::cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    RDEntry *rdEntry = fetchRDEntry(ie);
    if (rdEntry->numRSSent < ie->ipv6Data()->_getMaxRtrSolicitations())
    {
        bubble("Sending another RS message.");
        createAndSendRSPacket(ie);
        rdEntry->numRSSent++;
        //Need to find out if this is the last RS we are sending out.
        if (rdEntry->numRSSent == ie->ipv6Data()->_getMaxRtrSolicitations())
            scheduleAt(inet::simTime()+ie->ipv6Data()->_getMaxRtrSolicitationDelay(), msg);
        else
            scheduleAt(inet::simTime()+ie->ipv6Data()->_getRtrSolicitationInterval(), msg);
    }
    else
    {
        //RFC 2461, Section 6.3.7
        /*If a host sends MAX_RTR_SOLICITATIONS solicitations, and receives no Router
        Advertisements after having waited MAX_RTR_SOLICITATION_DELAY seconds after
        sending the last solicitation, the host concludes that there are no routers
        on the link for the purpose of [ADDRCONF]. However, the host continues to
        receive and process Router Advertisements messages in the event that routers
        appear on the link.*/
        bubble("Max number of RS messages sent");
        std::cout << "No RA messages were received. Assume no routers are on-link";
        delete rdEntry;
        rdList.erase(rdEntry); // update 19.12.07 - CB
        //rdEntry = NULL; // update 19.12.07 - CB
        delete msg;
    }
}

void IPv6NeighbourDiscovery::processRSPacket(inet::IPv6RouterSolicitation *rs,
    IPv6ControlInfo *rsCtrlInfo)
{
    if (validateRSPacket(rs, rsCtrlInfo) == false) return;
    //Find out which interface the RS message arrived on.
    InterfaceEntry *ie = ift->getInterfaceById(rsCtrlInfo->getInterfaceId());
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);//fetch advertising interface entry.

    //RFC 2461: Section 6.2.6
    //A host MUST silently discard any received Router Solicitation messages.
    if (ie->ipv6Data()->getAdvSendAdvertisements())
    {
        std::cout << "This is an advertising interface, processing RS\n";

        if (validateRSPacket(rs, rsCtrlInfo) == false) return;
        std::cout << "RS message validated\n";

        //First we extract RS specific information from the received message
        MACAddress macAddr = rs->getSourceLinkLayerAddress();
        std::cout << "MAC Address extracted\n";
        delete rs;

        /*A router MAY choose to unicast the response directly to the soliciting
        host's address (if the solicitation's source address is not the unspecified
        address), but the usual case is to multicast the response to the
        all-nodes group. In the latter case, the interface's interval timer is
        reset to a new random value, as if an unsolicited advertisement had just
        been sent(see Section 6.2.4).*/

        /*In all cases, Router Advertisements sent in response to a Router
        Solicitation MUST be delayed by a random time between 0 and
        MAX_RA_DELAY_TIME seconds. (If a single advertisement is sent in
        response to multiple solicitations, the delay is relative to the
        first solicitation.)  In addition, consecutive Router Advertisements
        sent to the all-nodes multicast address MUST be rate limited to no
        more than one advertisement every MIN_DELAY_BETWEEN_RAS seconds.*/

        /*A router might process Router Solicitations as follows:
        - Upon receipt of a Router Solicitation, compute a random delay
        within the range 0 through MAX_RA_DELAY_TIME. If the computed
        value corresponds to a time later than the time the next multicast
        Router Advertisement is scheduled to be sent, ignore the random
        delay and send the advertisement at the already-scheduled time.*/
        inet::cMessage *msg = new inet::cMessage("sendSolicitedRA", MK_SEND_SOL_RTRADV);
        msg->setContextPointer(ie);
        inet::simtime_t interval = uniform(0, ie->ipv6Data()->_getMaxRADelayTime());

        if (interval < advIfEntry->nextScheduledRATime)
        {
            inet::simtime_t nextScheduledTime;
            nextScheduledTime = inet::simTime()+interval;
            scheduleAt(nextScheduledTime, msg);
            advIfEntry->nextScheduledRATime = nextScheduledTime;
        }
        //else we ignore the generate interval and send it at the next scheduled time.

        //We need to keep a log here each time an RA is sent. Not implemented yet.
        //Assume the first course of action.
        /*- If the router sent a multicast Router Advertisement (solicited or
        unsolicited) within the last MIN_DELAY_BETWEEN_RAS seconds,
        schedule the advertisement to be sent at a time corresponding to
        MIN_DELAY_BETWEEN_RAS plus the random value after the previous
        advertisement was sent. This ensures that the multicast Router
        Advertisements are rate limited.

        - Otherwise, schedule the sending of a Router Advertisement at the
        time given by the random value.*/
    }
    else
    {
        std::cout << "This interface is a host, discarding RA message\n";
        delete rs;
    }
}

bool IPv6NeighbourDiscovery::validateRSPacket(inet::IPv6RouterSolicitation *rs,
    IPv6ControlInfo *rsCtrlInfo)
{
    bool result = true;
    /*6.1.1.  Validation of Router Solicitation Messages
    A router MUST silently discard any received Router Solicitation
    messages that do not satisfy all of the following validity checks:

    - The IP Hop Limit field has a value of 255, i.e., the packet
    could not possibly have been forwarded by a router.*/
    if (rsCtrlInfo->getHopLimit() != 255)
    {
        std::cout << "Hop limit is not 255! RS validation failed!\n";
        result = false;
    }
    //- ICMP Code is 0.
    if (rsCtrlInfo->getProtocol() != IP_PROT_IPv6_ICMP)
    {
        std::cout << "ICMP Code is not 0! RS validation failed!\n";
        result = false;
    }
    //- If the IP source address is the unspecified address, there is no
    //source link-layer address option in the message.
    if (rsCtrlInfo->getSrcAddr().isUnspecified())
    {
        std::cout << "IP source address is unspecified\n";
        if (rs->getSourceLinkLayerAddress().isUnspecified() == false)
        {
            std::cout << " but source link layer address is provided. RS validation failed!\n";
        }
    }
    return result;
}

inet::IPv6RouterAdvertisement *IPv6NeighbourDiscovery::createAndSendRAPacket(
    const IPv6Address& destAddr, InterfaceEntry *ie)
{
    std::cout << "Create and send RA invoked!\n";
    //Must use link-local addr. See: RFC2461 Section 6.1.2
    IPv6Address sourceAddr = ie->ipv6Data()->getLinkLocalAddress();

    //This operation includes all options, regardless whether it is solicited or unsolicited.
    if (ie->ipv6Data()->getAdvSendAdvertisements()) //if this is an advertising interface
    {
        //Construct a Router Advertisment message
        inet::IPv6RouterAdvertisement *ra = new inet::IPv6RouterAdvertisement("RApacket");
        ra->setType(inet::ICMPv6_ROUTER_AD);

        //RFC 2461: Section 6.2.3 Router Advertisment Message Content
        /*A router sends periodic as well as solicited Router Advertisements out
        its advertising interfaces.  Outgoing Router Advertisements are filled
        with the following values consistent with the message format given in
        Section 4.2:*/

        //- In the Router Lifetime field: the interface's configured AdvDefaultLifetime.
        ra->setRouterLifetime(SIMTIME_DBL(ie->ipv6Data()->getAdvDefaultLifetime()));

        //- In the M and O flags: the interface's configured AdvManagedFlag and
        //AdvOtherConfigFlag, respectively.  See [ADDRCONF].
        ra->setManagedAddrConfFlag(ie->ipv6Data()->getAdvManagedFlag());
        ra->setOtherStatefulConfFlag(ie->ipv6Data()->getAdvOtherConfigFlag());

		// Configuring the HomeAgentFlag (H-bit) (RFC 3775): Zarrar 25.02.07
		if ( rt6->isHomeAgent() )
			ra->setHomeAgentFlag(true);  //Set H-bit if the router is a HA
		else
			ra->setHomeAgentFlag(ie->ipv6Data()->getAdvHomeAgentFlag()); //else unset it, which is default

        //- In the Cur Hop Limit field: the interface's configured CurHopLimit.
        ra->setCurHopLimit(ie->ipv6Data()->getAdvCurHopLimit());

        //- In the Reachable Time field: the interface's configured AdvReachableTime.
        ra->setReachableTime(ie->ipv6Data()->getAdvReachableTime());

        //- In the Retrans Timer field: the interface's configured AdvRetransTimer.
        ra->setRetransTimer(ie->ipv6Data()->getAdvRetransTimer());

        //- In the options:
        /*o Source Link-Layer Address option: link-layer address of the sending
            interface.  (Assumption: We always send this)*/
        ra->setSourceLinkLayerAddress(ie->getMacAddress());
        ra->setMTU(ie->ipv6Data()->getAdvLinkMTU());

        //Add all Advertising Prefixes to the RA
        int numAdvPrefixes = ie->ipv6Data()->getNumAdvPrefixes();
        std::cout << "Number of Adv Prefixes: " << numAdvPrefixes << endl;
        ra->setPrefixInformationArraySize(numAdvPrefixes);
        for (int i = 0; i < numAdvPrefixes; i++)
        {
            IPv6InterfaceData::AdvPrefix advPrefix = ie->ipv6Data()->getAdvPrefix(i);
            inet::IPv6NDPrefixInformation prefixInfo;
            // EV << "advPrefix" << ie->ipv6Data()->detailedInfo()<< endl;
            std::cout<<"\n+=+=+=+= Appendign Prefix Info Option to RA +=+=+=+=\n";
            std::cout<<"Prefix Vaue: " <<advPrefix.prefix <<endl;
            std::cout<<"Prefix Length: " <<advPrefix.prefixLength <<endl;
            std::cout<<"L-Flag: " <<advPrefix.advOnLinkFlag <<endl;
            std::cout<<"A-Flag: " <<advPrefix.advAutonomousFlag <<endl;
            std::cout<<"R-Flag: " <<advPrefix.advRtrAddr <<endl;
            std::cout<<"Global Address from Prefix: " <<advPrefix.rtrAddress <<endl;

			if ( rt6->isHomeAgent() && advPrefix.advRtrAddr == true)
				prefixInfo.setPrefix(advPrefix.rtrAddress); //add the global-scope address of the HA's interface in the prefix option list of the RA message.
			else
				prefixInfo.setPrefix(advPrefix.prefix);  //adds the prefix only of the router's interface in the prefix option list of the RA message.

            prefixInfo.setPrefixLength(advPrefix.prefixLength);

            //- In the "on-link" flag: the entry's AdvOnLinkFlag.
            prefixInfo.setOnlinkFlag(advPrefix.advOnLinkFlag);
            //- In the Valid Lifetime field: the entry's AdvValidLifetime.
            prefixInfo.setValidLifetime(SIMTIME_DBL(advPrefix.advValidLifetime));
            //- In the "Autonomous address configuration" flag: the entry's
            //AdvAutonomousFlag.
            prefixInfo.setAutoAddressConfFlag(advPrefix.advAutonomousFlag);

		    if ( rt6->isHomeAgent() )
		    	prefixInfo.setRouterAddress(true); // set the R-bit if the node is a HA

		    //- In the Valid Lifetime field: the entry's AdvValidLifetime.
		    prefixInfo.setValidLifetime(SIMTIME_DBL(advPrefix.advValidLifetime));

            //- In the Preferred Lifetime field: the entry's AdvPreferredLifetime.
            prefixInfo.setPreferredLifetime(SIMTIME_DBL(advPrefix.advPreferredLifetime));
            //Now we pop the prefix info into the RA.
            ra->setPrefixInformation(i, prefixInfo);
        }
        sendPacketToIPv6Module(ra, destAddr, sourceAddr, ie->getInterfaceId());
        return ra;
    }
    return NULL; //XXX is this OK?
}

void IPv6NeighbourDiscovery::processRAPacket(inet::IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    //EV << "/// processRAPacket" << endl;

    InterfaceEntry *ie = ift->getInterfaceById(raCtrlInfo->getInterfaceId());

    if (ie->ipv6Data()->getAdvSendAdvertisements())
    {
        std::cout << "Interface is an advertising interface, dropping RA message.\n";
        delete ra;
        return;
    }
    else
    {
        if (validateRAPacket(ra, raCtrlInfo) == false)
        {
            delete ra;
            return;
        }

    	if ( ie->ipv6Data()->isDADInProgress() )
    	{
    		// in case we are currently performing DAD we ignore this RA
    		// TODO improve this procedure in order to allow reinitiating DAD
    		// (which means cancel current DAD, start new DAD)
    	    std::cout << "DAD in progress, ignore RA" << std::endl;
    		delete ra;
    		return;
    	}

        cancelRouterDiscovery(ie);//Cancel router discovery if it is in progress.
        std::cout << "Interface is a host, processing RA.\n";

        processRAForRouterUpdates(ra, raCtrlInfo);//See RFC2461: Section 6.3.4

        //Possible options
        MACAddress macAddress = ra->getSourceLinkLayerAddress();
        uint mtu = ra->getMTU();
        for (int i = 0; i < (int)ra->getPrefixInformationArraySize(); i++)
        {
            inet::IPv6NDPrefixInformation& prefixInfo = ra->getPrefixInformation(i);
            if (prefixInfo.getAutoAddressConfFlag() == true)//If auto addr conf is set
            {
            	// code update - overloaded function is not required anymore
            	// 3.9.07 - CB

            	//if ( ! rt6->isMobileNode() ) // If auto addr conf is set and node is not MN (Zarrar Yousaf 20.07.07)
	                //processRAPrefixInfoForAddrAutoConf(prefixInfo, ie); // We process prefix Info and form an addr for all nodes except MN
	            //else // but if the node is a MN
                std::cout << "auto addr conf is set" << std::endl;
            	processRAPrefixInfoForAddrAutoConf( prefixInfo, ie, ra->getHomeAgentFlag() ); // then calling the overloaded function for address configuration. The address conf for MN is different from other nodes as it needs to classify the newly formed address as HoA or CoA, depending on the status of the H-Flag. (Zarrar Yousaf 20.07.07)
            }

            // When in foreign network(s), the MN needs info about its HA address and its own Home Address (HoA), when sending BU to HA and CN(s). Therefore while in the home network I intialise struct HomeNetworkInfo{} with HoA and HA address, which will eventually be used by the MN while sending BUs from within visit networks. (Zarrar Yousaf 12.07.07)
            if ( ra->getHomeAgentFlag() && (prefixInfo.getRouterAddress() == true) )//If R-Flag is set and RA is from HA
			{
				// homeNetworkInfo now carries HoA, global unicast HA address and the home network prefix
            	// update 4.9.07 - CB
            	IPv6Address HoA = ie->ipv6Data()->getGlobalAddress(); //MN's home address
				IPv6Address HA = raCtrlInfo->getSrcAddr().setPrefix(prefixInfo.getPrefix(), prefixInfo.getPrefixLength());
				std::cout<<"The HoA of MN is: " << HoA <<", MN's HA Address is: "<< HA << " and the home prefix is " << prefixInfo.getPrefix() << std::endl;
				ie->ipv6Data()->updateHomeNetworkInfo(HoA, HA, prefixInfo.getPrefix(), prefixInfo.getPrefixLength()); //populate the HoA of MN, the HA global scope address and the home network prefix
			}
        }
    }
    delete raCtrlInfo;
    delete ra;
}

void IPv6NeighbourDiscovery::processRAForRouterUpdates(inet::IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    std::cout << "Processing RA for Router Updates\n";
    //RFC2461: Section 6.3.4
    //Paragraphs 1 and 2 omitted.

    //On receipt of a valid Router Advertisement, a host extracts the source
    //address of the packet and does the following:
    IPv6Address raSrcAddr = raCtrlInfo->getSrcAddr();
    InterfaceEntry *ie = ift->getInterfaceById(raCtrlInfo->getInterfaceId());
    int ifID = ie->getInterfaceId();

    /*- If the address is not already present in the host's Default Router List,
    and the advertisement's Router Lifetime is non-zero, create a new entry in
    the list, and initialize its invalidation timer value from the advertisement's
    Router Lifetime field.*/
    Neighbour *neighbour = neighbourCache.lookup(raSrcAddr, ifID);


    // update 3.9.07 - CB // if (neighbour == NULL && (ra->homeAgentFlag()==true)) //the RA is from a Router acting as a Home Agent as well
    if (neighbour == NULL)
    {
        std::cout << "Neighbour Cache Entry does not contain RA's source address\n";
        if (ra->getRouterLifetime() != 0)
        {
            std::cout << "RA's router lifetime is non-zero, creating an entry in the "
               << "Host's default router list with lifetime=" << ra->getRouterLifetime() << "\n";

        	// initiate neighbour unreachability detection for existing routers and remove default route(r), 3.9.07 - CB
        	// TODO improve this code
        	routersUnreachabilityDetection(ie);

            //If a Neighbor Cache entry is created for the router its reachability
            //state MUST be set to STALE as specified in Section 7.3.3.
            if (ra->getSourceLinkLayerAddress().isUnspecified())
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    inet::simTime()+ra->getRouterLifetime(), ra->getHomeAgentFlag() );
                //Note:invalidation timers are not explicitly defined.
            }
            else
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    ra->getSourceLinkLayerAddress(), inet::simTime()+ra->getRouterLifetime(), ra->getHomeAgentFlag() );
                //According to Greg, we should add a default route for hosts as well!
                rt6->addDefaultRoute(raSrcAddr, ifID, inet::simTime()+ra->getRouterLifetime());
            }
        }
        else
        {
            std::cout << "Router Lifetime is 0, adding NON-default router.\n";
            //WEI-The router is advertising itself, BUT not as a default router.
            if (ra->getSourceLinkLayerAddress().isUnspecified())
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID);
            else
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID,
                    ra->getSourceLinkLayerAddress());
            neighbour->isRouter = true;
        }
    }

    // uncommented the following block, 3.9.07 - CB
    /*
    else

    //================================Zarrar Yousaf 09.03.07=========================================
    if (neighbour == NULL && (ra->homeAgentFlag()==false))
    {
        EV << "Neighbour Cache Entry does not contain RA's source address\n";
        if (ra->routerLifetime() != 0)
        {
            EV << "RA's router lifetime is non-zero, creating an entry in the "
               << "Host's default router list with lifetime=" << ra->routerLifetime() << endl;
            //If a Neighbor Cache entry is created for the router its reachability
            //state MUST be set to STALE as specified in Section 7.3.3.
            if (ra->sourceLinkLayerAddress().isUnspecified())
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    simTime()+ra->routerLifetime());
                //Note:invalidation timers are not explicitly defined.
            }
            else
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    ra->sourceLinkLayerAddress(), simTime()+ra->routerLifetime());
                //According to Greg, we should add a default route for hosts as well!
                // - yes, but before adding a default route, we'll first have to invalidate the previous existing default route - CB
                rt6->removeDefaultRoute(ifID); // 27.08.07 - CB
                rt6->addDefaultRoute(raSrcAddr, ifID, simTime()+ra->routerLifetime());
            }
        }
        else
        {
            EV << "Router Lifetime is 0, adding NON-default router.\n";
            //WEI-The router is advertising itself, BUT not as a default router.
            if (ra->sourceLinkLayerAddress().isUnspecified())
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID);
            else
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID,
                    ra->sourceLinkLayerAddress());
            neighbour->isRouter = true;
        }
    }
    */

    //=================================================================================================


    else
    {
        //If no Source Link-Layer Address is included, but a corresponding Neighbor
        //Cache entry exists, its IsRouter flag MUST be set to TRUE.
        neighbour->isRouter = true;

	//=========if HomeAgentFlag == true, then the status should be recorded in the Neighbour Cache: Zarrar Yousaf (09.03.07)======
	//if(ra->getHomeAgentFlag()) 		//if the homeAgentFlag is set
	//	neighbour->isHomeAgent = true;
	//else
	//	continue;
	//=================================The homeAgentFlag check ends here========================================================


        //If a cache entry already exists and is updated with a different link-
        //layer address the reachability state MUST also be set to STALE.
        if (ra->getSourceLinkLayerAddress().isUnspecified() == false &&
            neighbour->macAddress.equals(ra->getSourceLinkLayerAddress()) == false)
            neighbour->macAddress = ra->getSourceLinkLayerAddress();

        /*- If the address is already present in the host's Default Router List
        as a result of a previously-received advertisement, reset its invalidation
        timer to the Router Lifetime value in the newly-received advertisement.*/
        neighbour->routerExpiryTime = inet::simTime()+ra->getRouterLifetime();

        /*- If the address is already present in the host's Default Router List
        and the received Router Lifetime value is zero, immediately time-out the
        entry as specified in Section 6.3.5.*/
        if (ra->getRouterLifetime() == 0)
        {
            std::cout << "RA's router lifetime is ZERO. Timing-out entry.\n";
            timeoutDefaultRouter(raSrcAddr, ifID);
        }
    }

    //Paragraph Omitted.

    //If the received Cur Hop Limit value is non-zero the host SHOULD set
    //its CurHopLimit variable to the received value.
    if (ra->getCurHopLimit() != 0)
    {
        std::cout << "RA's Cur Hop Limit is non-zero. Setting host's Cur Hop Limit to "
           << "received value.\n";
        ie->ipv6Data()->setCurHopLimit(ra->getCurHopLimit());
    }

    //If the received Reachable Time value is non-zero the host SHOULD set its
    //BaseReachableTime variable to the received value.
    if (ra->getReachableTime() != 0)
    {
        std::cout << "RA's reachable time is non-zero ";
        if (ra->getReachableTime() != SIMTIME_DBL(ie->ipv6Data()->getReachableTime()))
        {
            std::cout << " and RA's and Host's reachable time differ, \nsetting host's base"
               << " reachable time to received value.\n";
            ie->ipv6Data()->setBaseReachableTime(ra->getReachableTime());
            //If the new value differs from the previous value, the host SHOULD
            //recompute a new random ReachableTime value.
            ie->ipv6Data()->setReachableTime(ie->ipv6Data()->generateReachableTime());
        }
        std::cout << std::endl;
    }

    //The RetransTimer variable SHOULD be copied from the Retrans Timer field,
    //if the received value is non-zero.
    if (ra->getRetransTimer() != 0)
    {
        std::cout << "RA's retrans timer is non-zero, copying retrans timer variable.\n";
        ie->ipv6Data()->setRetransTimer(ra->getRetransTimer());
    }

    /*If the MTU option is present, hosts SHOULD copy the option's value into
    LinkMTU so long as the value is greater than or equal to the minimum link MTU
    [IPv6] and does not exceed the default LinkMTU value specified in the link
    type specific document (e.g., [IPv6-ETHER]).*/
    //TODO: not done yet

    processRAPrefixInfo(ra, ie);
}

void IPv6NeighbourDiscovery::processRAPrefixInfo(inet::IPv6RouterAdvertisement *ra,
    InterfaceEntry *ie)
{
    //Continued from section 6.3.4
    /*Prefix Information options that have the "on-link" (L) flag set indicate a
    prefix identifying a range of addresses that should be considered on-link.
    Note, however, that a Prefix Information option with the on-link flag set to
    zero conveys no information concerning on-link determination and MUST NOT be
    interpreted to mean that addresses covered by the prefix are off-link. The
    only way to cancel a previous on-link indication is to advertise that prefix
    with the L-bit set and the Lifetime set to zero. The default behavior (see
    Section 5.2) when sending a packet to an address for which no information is
    known about the on-link status of the address is to forward the packet to a
    default router; the reception of a Prefix Information option with the "on-link "
    (L) flag set to zero does not change this behavior. The reasons for an address
    being treated as on-link is specified in the definition of "on-link" in
    Section 2.1. Prefixes with the on-link flag set to zero would normally have
    the autonomous flag set and be used by [ADDRCONF].*/
    inet::IPv6NDPrefixInformation prefixInfo;
    //For each Prefix Information option
    for (int i = 0; i < (int)ra->getPrefixInformationArraySize(); i++)
    {
        prefixInfo = ra->getPrefixInformation(i);
        if (!prefixInfo.getOnlinkFlag()) break;//skip to next prefix option

        //with the on-link flag set, a host does the following:
        std::cout << "Fetching Prefix Information:" << i+1 << " of "
           << ra->getPrefixInformationArraySize() << std::endl;
        uint prefixLength = prefixInfo.getPrefixLength();
        inet::simtime_t validLifetime = prefixInfo.getValidLifetime();
        uint preferredLifetime = prefixInfo.getPreferredLifetime();
        IPv6Address prefix = prefixInfo.getPrefix();

        //- If the prefix is the link-local prefix, silently ignore the Prefix
        //Information option.
        if (prefix.isLinkLocal())
        {
            std::cout << "Prefix is link-local, ignoring prefix.\n";
            return;
        }

        //- If the prefix is not already present in the Prefix List,
        if (!rt6->isPrefixPresent(prefix)) {
            //and the Prefix Information option's Valid Lifetime field is non-zero,
            if (validLifetime != 0)
            {
                /*create a new entry for the prefix and initialize its invalidation
                timer to the Valid Lifetime value in the Prefix Information option.*/
                rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->getInterfaceId(),
                    inet::simTime()+validLifetime);
            }
            /*- If the Prefix Information option's Valid Lifetime field is zero,
            and the prefix is not present in the host's Prefix List,
            silently ignore the option.*/
        }
        else
        {
            /* If the new Lifetime value is zero, time-out the prefix immediately
            (see Section 6.3.5).*/
            if (validLifetime == 0)
            {
                std::cout << "Prefix Info's valid lifetime is 0, time-out prefix\n";
                rt6->removeOnLinkPrefix(prefix, prefixLength);
                return;
            }
            /*- If the prefix is already present in the host's Prefix List as
            the result of a previously-received advertisement, reset its
            invalidation timer to the Valid Lifetime value in the Prefix
            Information option.*/
            rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->getInterfaceId(),
                inet::simTime()+validLifetime);
        }

        /*Stateless address autoconfiguration [ADDRCONF] may in some
        circumstances increase the Valid Lifetime of a prefix or ignore it
        completely in order to prevent a particular denial of service attack.
        However, since the effect of the same denial of service targeted at
        the on-link prefix list is not catastrophic (hosts would send packets
        to a default router and receive a redirect rather than sending
        packets directly to a neighbor) the Neighbor Discovery protocol does
        not impose such a check on the prefix lifetime values.*/
    }
}

/*void IPv6NeighbourDiscovery::processRAPrefixInfoForAddrAutoConf(
    IPv6NDPrefixInformation& prefixInfo, InterfaceEntry *ie)
{
    EV << "Processing Prefix Info for address auto-configuration.\n";
    IPv6Address prefix = prefixInfo.getPrefix();
    uint prefixLength = prefixInfo.getPrefixLength();
    simtime_t preferredLifetime = prefixInfo.getPreferredLifetime();
    simtime_t validLifetime = prefixInfo.getValidLifetime();


    EV << "/// standard prefix: " << prefix << std::endl;


    //RFC 2461: Section 5.5.3
    //First condition tested, the autonomous flag is already set

    //b) If the prefix is the link-local prefix, silently ignore the Prefix
    //Information option.
    if (prefixInfo.getPrefix().isLinkLocal() == true)
    {
        EV << "Prefix is link-local, ignore Prefix Information Option\n";
        return;
    }

    //c) If the preferred lifetime is greater than the valid lifetime, silently
    //ignore the Prefix Information option. A node MAY wish to log a system
    //management error in this case.
    if (preferredLifetime > validLifetime)
    {
        EV << "Preferred lifetime is greater than valid lifetime, ignore Prefix Information\n";
        return;
    }

    bool isPrefixAssignedToInterface = false;
    for (int i = 0; i < ie->ipv6Data()->getNumAddresses(); i++)
    {
        if (ie->ipv6Data()->getAddress(i).matches(prefix, prefixLength) == true)
            isPrefixAssignedToInterface = true;
		EV <<"The received Prefix is already assigned to the interface"<<endl; //Zarrar Yousaf 19.07.07
		}
    }
    /*d) If the prefix advertised does not match the prefix of an address already
         in the list, and the Valid Lifetime is not 0, form an address (and add
         it to the list) by combining the advertised prefix with the link�s
         interface identifier as follows:
    if (isPrefixAssignedToInterface == false && validLifetime != 0)
    {
	EV<<"Prefix not assigned to interface. Possible new router detected. Auto-configuring new address."<<endl;
        IPv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
        ASSERT(linkLocalAddress.isUnspecified() == false);
        IPv6Address newAddr = linkLocalAddress.setPrefix(prefix, prefixLength);
        //TODO: for now we leave the newly formed address as not tentative,
        //according to Greg, we have to always perform DAD for a newly formed address.
        EV << "Assigning new address to: " << ie->getName() << endl;
        ie->ipv6Data()->assignAddress(newAddr, false, simTime()+validLifetime,
            simTime()+preferredLifetime);
    }

    //TODO: this is the simplified version.
    /*e) If the advertised prefix matches the prefix of an autoconfigured
       address (i.e., one obtained via stateless or stateful address
       autoconfiguration) in the list of addresses associated with the
       interface, the specific action to perform depends on the Valid
       Lifetime in the received advertisement and the Lifetime
       associated with the previously autoconfigured address (which we
       call StoredLifetime in the discussion that follows):

       1) If the received Lifetime is greater than 2 hours or greater
          than StoredLifetime, update the stored Lifetime of the
          corresponding address.

       2) If the StoredLifetime is less than or equal to 2 hours and the
          received Lifetime is less than or equal to StoredLifetime,
          ignore the prefix, unless the Router Advertisement from which

          this Prefix Information option was obtained has been
          authenticated (e.g., via IPSec [RFC2402]). If the Router
          Advertisment was authenticated, the StoredLifetime should be
          set to the Lifetime in the received option.

       3) Otherwise, reset the stored Lifetime in the corresponding
          address to two hours.

}
*/

void IPv6NeighbourDiscovery::createRATimer(InterfaceEntry *ie)
{
    inet::cMessage *msg = new inet::cMessage("sendPeriodicRA", MK_SEND_PERIODIC_RTRADV);
    msg->setContextPointer(ie);
    AdvIfEntry *advIfEntry = new AdvIfEntry();
    advIfEntry->interfaceId = ie->getInterfaceId();
    advIfEntry->numRASent = 0;

    // 20.9.07 - CB
    /*if ( rt6->isRouter() )
    {
    	EV<<"\n+=+=+= Getting min RA Interval from omneptp.ini =+=+=\n";
    	ie->ipv6()->setMinRtrAdvInterval(IPv6NeighbourDiscovery::getMinRAInterval()); //should be 0.07 for MIPv6 Support
    	EV<<"\n+=+=+= Getting max RA Interval from omneptp.ini =+=+=\n";
    	ie->ipv6()->setMaxRtrAdvInterval(IPv6NeighbourDiscovery::getMaxRAInterval()); //should be 0.03 for MIPv6 Support
   	}*/
    // update 23.10.07 - CB

    if( isConnectedToWirelessAP(ie) )
    {
        std::cout<<"This Interface is connected to a WLAN AP, hence using MIPv6 Default Values"<<std::endl;
    	inet::simtime_t minRAInterval = par("minIntervalBetweenRAs"); //reading from the omnetpp.ini (ZY 23.07.09)
    	inet::simtime_t maxRAInterval = par("maxIntervalBetweenRAs"); //reading from the omnetpp.ini (ZY 23.07.09
    	//EV<<"\n+=+=+= Getting min and max RA Interval from omneptp.ini =+=+=\n";
    	ie->ipv6Data()->setMinRtrAdvInterval(minRAInterval);
    	ie->ipv6Data()->setMaxRtrAdvInterval(maxRAInterval);
    }
    else
    {
        std::cout<<"This Interface is not connected to a WLAN AP, hence using default values"<<std::endl;
    	//interval = uniform( ie->ipv6()->minRtrAdvInterval(), ie->ipv6()->maxRtrAdvInterval() );
    	//EV<<"\nThe random calculated RA_ND interval is: "<< interval<<" seconds\n";
    }
    // end CB

    inet::simtime_t interval = uniform(ie->ipv6Data()->getMinRtrAdvInterval(), ie->ipv6Data()->getMaxRtrAdvInterval());


    std::cout<<"\nThe random calculated RA interval is: " << interval << " seconds\n";
    advIfEntry->raTimeoutMsg = msg;

    inet::simtime_t nextScheduledTime = inet::simTime() + interval;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    advIfList.insert(advIfEntry);
    std::cout << "Interval: " << interval << std::endl;
    std::cout << "Next scheduled time: " << nextScheduledTime << std::endl;
    //now we schedule the msg for whatever time that was derived
    scheduleAt(nextScheduledTime, msg);
}

void IPv6NeighbourDiscovery::resetRATimer(InterfaceEntry *ie)
{//Not used yet but could be useful later on.-WEI
    //Iterate through all RA timers within the Neighbour Discovery module.
/*
    for (RATimerList::iterator it=raTimerList.begin(); it != raTimerList.end(); it++)
    {
        cMessage *msg = (*it);
        InterfaceEntry *msgIE = (InterfaceEntry *)msg->getContextPointer();
        //Find the timer that matches the given Interface Entry.
        if (msgIE->outputPort() == ie->outputPort())
        {
            EV << "Resetting RA timer for port: " << ie->outputPort();
            cancelEvent(msg);//Cancel the next scheduled msg.
            simtime_t interval
                = uniform(ie->ipv6Data()->getMinRtrAdvInterval(),ie->ipv6Data()->getMaxRtrAdvInterval());
            scheduleAt(simTime()+interval, msg);
        }
    }
*/
}

void IPv6NeighbourDiscovery::sendPeriodicRA(inet::cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);
    IPv6Address destAddr = IPv6Address("FF02::1");
    createAndSendRAPacket(destAddr, ie);
    advIfEntry->numRASent++;
    inet::simtime_t nextScheduledTime;

    //RFC 2461, Section 6.2.4
    /*Whenever a multicast advertisement is sent from an interface, the timer is
    reset to a uniformly-distributed random value between the interface's
    configured MinRtrAdvInterval and MaxRtrAdvInterval; expiration of the timer
    causes the next advertisement to be sent and a new random value to be chosen.*/
// /*
inet::simtime_t interval;
std::cout<<"\n+=+=+= MIPv6 Feature: "<< rt6->hasMIPv6Support()<<" +=+=+=\n";

// update 13.9.07 - CB
/*
//if ( rt6->hasMIPv6Support() )
//if(mobileIPv6Enabled()) //If MIPv6 Supoprt is enabled then set the min and max of RtrAdvInterval to 0.03 and 0.07 seconds as per Section 7.5 RFC 3775
// if(!(mipv6-> mIPv6Enabled()))
{
	EV<<"\n+=+=+= Getting min RA Interval from omneptp.ini =+=+=\n";
	ie->ipv6Data()->setMinRtrAdvInterval(IPv6NeighbourDiscovery::getMinRAInterval()); //should be 0.07 for MIPv6 Support
	EV<<"\n+=+=+= Getting max RA Interval from omneptp.ini =+=+=\n";
	ie->ipv6Data()->setMaxRtrAdvInterval(IPv6NeighbourDiscovery::getMaxRAInterval()); //should be 0.03 for MIPv6 Support
	//simtime_t lb = ie->ipv6Data()->getMinRtrAdvInterval();
	//simtime_t ub = ie->ipv6Data()->getMaxRtrAdvInterval();
	//EV<<"\n +=+=+= The random calculated interval is bounded by[" << lb << "," << ub << "] +=+=+=\n";
	//interval  = uniform(lb,ub);
 	//EV<<"\n +=+=+= The random calculated interval is: "<< interval<<" +=+=+=\n";
	}
// */
//     simtime_t interval
	//else
	//{
	//EV<<"\n+=+=+= Using default min/max RA Interval from IPv6 Interface Data =+=+=\n";
	interval = uniform(ie->ipv6Data()->getMinRtrAdvInterval(),ie->ipv6Data()->getMaxRtrAdvInterval());
	std::cout<<"\n +=+=+= The random calculated interval is: "<< interval<<" +=+=+=\n";
	//}

    nextScheduledTime = inet::simTime() + interval;

    /*For the first few advertisements (up to MAX_INITIAL_RTR_ADVERTISEMENTS)
    sent from an interface when it becomes an advertising interface,*/
    std::cout << "Num RA sent is: " << advIfEntry->numRASent << std::endl;
    std::cout << "maxInitialRtrAdvertisements is: " << ie->ipv6Data()->_getMaxInitialRtrAdvertisements() << std::endl;
    if(advIfEntry->numRASent <= ie->ipv6Data()->_getMaxInitialRtrAdvertisements())
    {
        if (interval > ie->ipv6Data()->_getMaxInitialRtrAdvertInterval())
        {
            //if the randomly chosen interval is greater than MAX_INITIAL_RTR_ADVERT_INTERVAL,
            //the timer SHOULD be set to MAX_INITIAL_RTR_ADVERT_INTERVAL instead.
            nextScheduledTime = inet::simTime() + ie->ipv6Data()->_getMaxInitialRtrAdvertInterval();
            std::cout << "Sending initial RA but interval is too long. Using default value." << std::endl;
        }
        else
            std::cout << "Sending initial RA. Using randomly generated interval." << std::endl;
    }
    std::cout << "Next scheduled time: " << nextScheduledTime << std::endl;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    ASSERT(nextScheduledTime > inet::simTime());
    scheduleAt(nextScheduledTime, msg);
}

void IPv6NeighbourDiscovery::sendSolicitedRA(inet::cMessage *msg)
{
    std::cout << "Send Solicited RA invoked!\n";
    InterfaceEntry *ie = (InterfaceEntry *)msg->getContextPointer();
    IPv6Address destAddr = IPv6Address("FF02::1");
    std::cout << "Testing condition!\n";
    createAndSendRAPacket(destAddr, ie);
    delete msg;
}

bool IPv6NeighbourDiscovery::validateRAPacket(inet::IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    bool result = true;

    //RFC 2461: Section 6.1.2 Validation of Router Advertisement Messages
    /*A node MUST silently discard any received Router Advertisement
    messages that do not satisfy all of the following validity checks:*/
    raCtrlInfo->getSrcAddr();
    //- IP Source Address is a link-local address.  Routers must use
    //  their link-local address as the source for Router Advertisement
    //  and Redirect messages so that hosts can uniquely identify
    //  routers.
    if (raCtrlInfo->getSrcAddr().isLinkLocal() == false)
    {
        std::cout << "RA source address is not link-local. RA validation failed!\n";
        result = false;
    }

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.
    if (raCtrlInfo->getHopLimit() != 255)
    {
        std::cout << "Hop limit is not 255! RA validation failed!\n";
        result = false;
    }

    //- ICMP Code is 0.
    if (raCtrlInfo->getProtocol() != IP_PROT_IPv6_ICMP)
    {
        std::cout << "ICMP Code is not 0! RA validation failed!\n";
        result = false;
    }

    // - All included options have a length that is greater than zero.
    // CB
    if ( ra->getPrefixInformationArraySize() == 0)
    {
        std::cout << "No prefix information available! RA validation failed\n";
    	result = false;
    }

    return result;
}

inet::IPv6NeighbourSolicitation *IPv6NeighbourDiscovery::createAndSendNSPacket(
    const IPv6Address& nsTargetAddr, const IPv6Address& dgDestAddr,
    const IPv6Address& dgSrcAddr, InterfaceEntry *ie)
{
	Enter_Method_Silent();
    MACAddress myMacAddr = ie->getMacAddress();

    //Construct a Neighbour Solicitation message
    inet::IPv6NeighbourSolicitation *ns = new inet::IPv6NeighbourSolicitation("NSpacket!");
    ns->setType(inet::ICMPv6_NEIGHBOUR_SOL);

    //Neighbour Solicitation Specific Information
    ns->setTargetAddress(nsTargetAddr);

    /*If the solicitation is being sent to a solicited-node multicast
    address, the sender MUST include its link-layer address (if it has
    one) as a Source Link-Layer Address option.*/
    if (dgDestAddr.matches(IPv6Address("FF02::1:FF00:0"),104) && // FIXME what's this? make constant...
        !dgSrcAddr.isUnspecified())
        ns->setSourceLinkLayerAddress(myMacAddr);

    sendPacketToIPv6Module(ns, dgDestAddr, dgSrcAddr, ie->getInterfaceId());

    return ns;
}

void IPv6NeighbourDiscovery::processNSPacket(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    //Control Information
    InterfaceEntry *ie = ift->getInterfaceById(nsCtrlInfo->getInterfaceId());

    IPv6Address nsTargetAddr = ns->getTargetAddress();

    //RFC 2461:Section 7.2.3
    //If target address is not a valid "unicast" or anycast address assigned to the
    //receiving interface, we should silently discard the packet.
    if (validateNSPacket(ns, nsCtrlInfo) == false
        || ie->ipv6Data()->hasAddress(nsTargetAddr) == false)
    {
        bubble("NS validation failed\n");
        delete nsCtrlInfo;
        delete ns;
        return;
    }
    bubble("NS validation passed.\n");
    if (ie->ipv6Data()->isTentativeAddress(nsTargetAddr))
    {
        //If the Target Address is tentative, the Neighbor Solicitation should
        //be processed as described in [ADDRCONF].
        std::cout << "Process NS for Tentative target address.\n";
        processNSForTentativeAddress(ns, nsCtrlInfo);
    }
    else
    {
        //Otherwise, the following description applies.
        std::cout << "Process NS for Non-Tentative target address.\n";
        processNSForNonTentativeAddress(ns, nsCtrlInfo, ie);
    }
    delete nsCtrlInfo;
    delete ns;
}

bool IPv6NeighbourDiscovery::validateNSPacket(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    bool result = true;
    /*RFC 2461:7.1.1. Validation of Neighbor Solicitations(some checks are omitted)
    A node MUST silently discard any received Neighbor Solicitation
    messages that do not satisfy all of the following validity checks:*/
    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //could not possibly have been forwarded by a router.
    if (nsCtrlInfo->getHopLimit() != 255)
    {
        std::cout << "Hop limit is not 255! NS validation failed!\n";
        result = false;
    }
    //- Target Address is not a multicast address.
    if (ns->getTargetAddress().isMulticast() == true)
    {
        std::cout << "Target address is a multicast address! NS validation failed!\n";
        result = false;
    }
    //- If the IP source address is the unspecified address,
    if (nsCtrlInfo->getSrcAddr().isUnspecified())
    {
        std::cout << "Source Address is unspecified\n";
        //the IP destination address is a solicited-node multicast address.
        if (nsCtrlInfo->getDestAddr().matches(IPv6Address::SOLICITED_NODE_PREFIX,104) == false)
        {
            std::cout << " but IP dest address is not a solicited-node multicast address! NS validation failed!\n";
            result = false;
        }
        //there is no source link-layer address option in the message.
        else if (ns->getSourceLinkLayerAddress().isUnspecified() == false)
        {
            std::cout << " but Source link-layer address is not empty! NS validation failed!\n";
            result = false;
        }
        else
            std::cout << "NS Validation Passed\n";
    }

    return result;
}

void IPv6NeighbourDiscovery::processNSForTentativeAddress(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    //Control Information
    IPv6Address nsSrcAddr = nsCtrlInfo->getSrcAddr();
    IPv6Address nsDestAddr = nsCtrlInfo->getDestAddr();

    ASSERT(nsSrcAddr.isUnicast() || nsSrcAddr.isUnspecified());
    //solicitation is processed as described in RFC2462:section 5.4.3

    if (nsSrcAddr.isUnspecified())
    {
        std::cout << "Source Address is UNSPECIFIED. Sender is performing DAD\n";
        //Sender performing Duplicate Address Detection
        if (rt6->isLocalAddress(nsSrcAddr))
            std::cout << "NS comes from myself. Ignoring NS\n";
        else
            std::cout << "NS comes from another node. Address is duplicate!\n";
            error("Duplicate Address Detected! Manual Attention Required!");
    }
    else if (nsSrcAddr.isUnicast())
    {
        //Sender performing address resolution
        std::cout << "Sender is performing Address Resolution\n";
        std::cout << "Target Address is tentative. Ignoring NS.\n";
    }
}

void IPv6NeighbourDiscovery::processNSForNonTentativeAddress(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    //Neighbour Solicitation Information
    MACAddress nsMacAddr = ns->getSourceLinkLayerAddress();

    int ifID = ie->getInterfaceId();

    //target addr is not tentative addr
    //solicitation processed as described in RFC2461:section 7.2.3
    if (nsCtrlInfo->getSrcAddr().isUnspecified())
    {
        std::cout << "Address is duplicate! Inform Sender of duplicate address!\n";
        sendSolicitedNA(ns, nsCtrlInfo, ie);
    }
    else
    {
        processNSWithSpecifiedSrcAddr(ns, nsCtrlInfo, ie);
    }
}

void IPv6NeighbourDiscovery::processNSWithSpecifiedSrcAddr(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    //RFC 2461, Section 7.2.3
    /*If the Source Address is not the unspecified address and, on link layers
    that have addresses, the solicitation includes a Source Link-Layer Address
    option, then the recipient SHOULD create or update the Neighbor Cache entry
    for the IP Source Address of the solicitation.*/

    //Neighbour Solicitation Information
    MACAddress nsMacAddr = ns->getSourceLinkLayerAddress();

    int ifID = ie->getInterfaceId();

    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookup(nsCtrlInfo->getSrcAddr(), ifID);

    if (entry == NULL)
    {
        /*If an entry does not already exist, the node SHOULD create a new one
        and set its reachability state to STALE as specified in Section 7.3.3.*/
        std::cout << "Neighbour Entry not found. Create a Neighbour Cache Entry.\n";
        neighbourCache.addNeighbour(nsCtrlInfo->getSrcAddr(), ifID, nsMacAddr);
    }
    else
    {
        /*If an entry already exists, and the cached link-layer address differs from
        the one in the received Source Link-Layer option,*/
        if (!(entry->macAddress.equals(nsMacAddr)) && !nsMacAddr.isUnspecified())
        {
            //the cached address should be replaced by the received address
            entry->macAddress = nsMacAddr;
            //and the entry's reachability state MUST be set to STALE.
            entry->reachabilityState = IPv6NeighbourCache::STALE;
        }
    }
    /*After any updates to the Neighbor Cache, the node sends a Neighbor
    Advertisement response as described in the next section.*/
    sendSolicitedNA(ns, nsCtrlInfo, ie);
}

void IPv6NeighbourDiscovery::sendSolicitedNA(inet::IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    inet::IPv6NeighbourAdvertisement *na = new inet::IPv6NeighbourAdvertisement("NApacket");
    //RFC 2461: Section 7.2.4
    /*A node sends a Neighbor Advertisement in response to a valid Neighbor
    Solicitation targeting one of the node's assigned addresses.  The
    Target Address of the advertisement is copied from the Target Address
    of the solicitation.*/
    na->setTargetAddress(ns->getTargetAddress());

    /*If the solicitation's IP Destination Address is not a multicast address,
    the Target Link-Layer Address option MAY be omitted; the neighboring node's
    cached value must already be current in order for the solicitation to have
    been received. If the solicitation's IP Destination Address is a multicast
    address, the Target Link-Layer option MUST be included in the advertisement.*/
    na->setTargetLinkLayerAddress(ie->getMacAddress());//here, we always include the MAC addr.

    /*Furthermore, if the node is a router, it MUST set the Router flag to one;
    otherwise it MUST set the flag to zero.*/
    na->setRouterFlag(rt6->isRouter());

    /*If the (NS)Target Address is either an anycast address or a unicast
    address for which the node is providing proxy service, or the Target
    Link-Layer Address option is not included,*/
    //TODO:ANYCAST will not be implemented here!
    if (ns->getSourceLinkLayerAddress().isUnspecified())
        //the Override flag SHOULD be set to zero.
        na->setOverrideFlag(false);
    else
        //Otherwise, the Override flag SHOULD be set to one.
        na->setOverrideFlag(true);
    /*Proper setting of the Override flag ensures that nodes give preference to
    non-proxy advertisements, even when received after proxy advertisements, and
    also ensures that the first advertisement for an anycast address "wins".*/

    IPv6Address naDestAddr;
    //If the source of the solicitation is the unspecified address,
    if(nsCtrlInfo->getSrcAddr().isUnspecified())
    {
        /*the node MUST set the Solicited flag to zero and multicast the advertisement
        to the all-nodes address.*/
        na->setSolicitedFlag(false);
        naDestAddr = IPv6Address::ALL_NODES_2;
    }
    else
    {
        /*Otherwise, the node MUST set the Solicited flag to one and unicast
        the advertisement to the Source Address of the solicitation.*/
        na->setSolicitedFlag(true);
        naDestAddr = nsCtrlInfo->getSrcAddr();
    }

    /*If the Target Address is an anycast address the sender SHOULD delay sending
    a response for a random time between 0 and MAX_ANYCAST_DELAY_TIME seconds.*/
    /*TODO: More associated complexity for this one. We will have to delay
    sending off the solicitation. Perhaps the self message could have a context
    pointer pointing to a struct with enough info to create and send a NA packet.*/

    /*Because unicast Neighbor Solicitations are not required to include a
    Source Link-Layer Address, it is possible that a node sending a
    solicited Neighbor Advertisement does not have a corresponding link-
    layer address for its neighbor in its Neighbor Cache.  In such
    situations, a node will first have to use Neighbor Discovery to
    determine the link-layer address of its neighbor (i.e, send out a
    multicast Neighbor Solicitation).*/
    //TODO: if above mentioned happens, can addr resolution be performed for ND messages?
    //if no link-layer addr exists for unicast addr when sending solicited NA, we should
    //add the NA to the list of queued packets. What if we have a list of queued
    //packets for different unicast solicitations? each time addr resolution is
    //done we should check the destinations of the list of queued packets and send
    //off the respective ones.
    IPv6Address myIPv6Addr = ie->ipv6Data()->getPreferredAddress();
    sendPacketToIPv6Module(na, naDestAddr, myIPv6Addr, ie->getInterfaceId());
}

void IPv6NeighbourDiscovery::sendUnsolicitedNA(InterfaceEntry *ie)
{
    //RFC 2461
    //Section 7.2.6: Sending Unsolicited Neighbor Advertisements
	Enter_Method_Silent();
	std::cout << "sending unsolicited NA" << std::endl;

	inet::IPv6NeighbourAdvertisement *na = new inet::IPv6NeighbourAdvertisement("NApacket");
    IPv6Address myIPv6Addr = ie->ipv6Data()->getPreferredAddress();
    //RFC 2461: Section 7.2.6
    /*The Target Address field in the unsolicited advertisement is set to
	  an IP address of the interface, and the Target Link-Layer Address
	  option is filled with the new link-layer address.*/
    na->setTargetAddress(myIPv6Addr);
    na->setTargetLinkLayerAddress( ie->getMacAddress() );

    /*The Solicited flag MUST be set to zero, in order to avoid confusing
      the Neighbor Unreachability Detection algorithm.*/
    na->setSolicitedFlag(false);

    /*If the node is a router, it MUST set the Router flag to one;
      otherwise it MUST set it to zero.*/
    na->setRouterFlag( rt6->isRouter() );

   /*The Override flag MAY be set to either zero or one.  In either case,
    neighboring nodes will immediately change the state of their Neighbor
    Cache entries for the Target Address to STALE, prompting them to
    verify the path for reachability.  If the Override flag is set to
    one, neighboring nodes will install the new link-layer address in
    their caches.  Otherwise, they will ignore the new link-layer
	 address, choosing instead to probe the cached address.*/
    na->setOverrideFlag(true);

    /*A node that has multiple IP addresses assigned to an interface MAY
    multicast a separate Neighbor Advertisement for each address.  In
    such a case the node SHOULD introduce a small delay between the
    sending of each advertisement to reduce the probability of the
    advertisements being lost due to congestion.

    A proxy MAY multicast Neighbor Advertisements when its link-layer
    address changes or when it is configured (by system management or
    other mechanisms) to proxy for an address.  If there are multiple
    nodes that are providing proxy services for the same set of addresses
    the proxies SHOULD provide a mechanism that prevents multiple proxies
    from multicasting advertisements for any one address, in order to
    reduce the risk of excessive multicast traffic.

    Also, a node belonging to an anycast address MAY multicast
    unsolicited Neighbor Advertisements for the anycast address when the
    node's link-layer address changes.

    Note that because unsolicited Neighbor Advertisements do not reliably
    update caches in all nodes (the advertisements might not be received
    by all nodes), they should only be viewed as a performance
    optimization to quickly update the caches in most neighbors.  The
    Neighbor Unreachability Detection algorithm ensures that all nodes
    obtain a reachable link-layer address, though the delay may be
    slightly longer.*/
    sendPacketToIPv6Module(na, IPv6Address::ALL_NODES_2, myIPv6Addr, ie->getInterfaceId());
}

void IPv6NeighbourDiscovery::processNAPacket(inet::IPv6NeighbourAdvertisement *na,
    IPv6ControlInfo *naCtrlInfo)
{
    if (validateNAPacket(na, naCtrlInfo) == false)
    {
        delete naCtrlInfo;
        delete na;
        return;
    }

    //Neighbour Advertisement Information
    IPv6Address naTargetAddr = na->getTargetAddress();

    //First, we check if the target address in NA is found in the interface it
    //was received on is tentative.
    InterfaceEntry *ie = ift->getInterfaceById(naCtrlInfo->getInterfaceId());
    if (ie->ipv6Data()->isTentativeAddress(naTargetAddr))
    {
        error("Duplicate Address Detected! Manual attention needed!");
    }
    //Logic as defined in Section 7.2.5
    Neighbour *neighbourEntry = neighbourCache.lookup(naTargetAddr, ie->getInterfaceId());

    if (neighbourEntry == NULL)
    {
        std::cout << "NA received. Target Address not found in Neighbour Cache\n";
        std::cout << "Dropping NA packet.\n";
        delete naCtrlInfo;
        delete na;
        return;
    }

    //Target Address has entry in Neighbour Cache
    std::cout << "NA received. Target Address found in Neighbour Cache\n";

    if (neighbourEntry->reachabilityState == IPv6NeighbourCache::INCOMPLETE)
        processNAForIncompleteNCEState(na, neighbourEntry);
    else
        processNAForOtherNCEStates(na, neighbourEntry);
    delete naCtrlInfo;
    delete na;
}

bool IPv6NeighbourDiscovery::validateNAPacket(inet::IPv6NeighbourAdvertisement *na,
    IPv6ControlInfo *naCtrlInfo)
{
    bool result = true;//adopt optimistic approach

    //RFC 2461:7.1.2 Validation of Neighbor Advertisments(some checks are omitted)
    //A node MUST silently discard any received Neighbor Advertisment messages
    //that do not satisfy all of the following validity checks:

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.
    if (naCtrlInfo->getHopLimit() != 255)
    {
        std::cout << "Hop Limit is not 255! NA validation failed!\n";
        result = false;
    }

    //- Target Address is not a multicast address.
    if (na->getTargetAddress().isMulticast() == true)
    {
        std::cout << "Target Address is a multicast address! NA validation failed!\n";
        result = false;
    }

    //- If the IP Destination Address is a multicast address the Solicited flag
    //  is zero.
    if (naCtrlInfo->getDestAddr().isMulticast())
    {
        if (na->getSolicitedFlag() == true)
        {
            std::cout << "Dest Address is multicast address but solicted flag is 0!\n";
            result = false;
        }
    }

    if (result == true) bubble("NA validation passed.");
    else bubble("NA validation failed.");
    return result;
}

void IPv6NeighbourDiscovery::processNAForIncompleteNCEState(
        inet::IPv6NeighbourAdvertisement *na, Neighbour *nce)
{
    MACAddress naMacAddr = na->getTargetLinkLayerAddress();
    bool naRouterFlag = na->getRouterFlag();
    bool naSolicitedFlag = na->getSolicitedFlag();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    /*If the target's neighbour Cache entry is in the INCOMPLETE state when the
    advertisement is received, one of two things happens.*/
    if (naMacAddr.isUnspecified())
    {
        /*If the link layer has addresses and no Target Link-Layer address option
        is included, the receiving node SHOULD silently discard the received
        advertisement.*/
        std::cout << "No MAC Address specified in NA. Ignoring NA\n";
        return;
    }
    else
    {
        //Otherwise, the receiving node performs the following steps:
        //- It records the link-layer address in the neighbour Cache entry.
        std::cout << "ND is updating Neighbour Cache Entry.\n";
        nce->macAddress = naMacAddr;

        //- If the advertisement's Solicited flag is set, the state of the
        //  entry is set to REACHABLE, otherwise it is set to STALE.
        if (naSolicitedFlag == true)
        {
            nce->reachabilityState = IPv6NeighbourCache::REACHABLE;
            std::cout << "Reachability confirmed through successful Addr Resolution.\n";
            nce->reachabilityExpires = inet::simTime() + ie->ipv6Data()->_getReachableTime();
        }
        else{
            std::cout << "Reachability confirmed : STALE.\n";//============= Adam 13-09-2011 =====================
            nce->reachabilityState = IPv6NeighbourCache::STALE;
        }

        //- It sets the IsRouter flag in the cache entry based on the Router
        //  flag in the received advertisement.
        nce->isRouter = naRouterFlag;

        //- It sends any packets queued for the neighbour awaiting address
        //  resolution.
        sendQueuedPacketsToIPv6Module(nce);
        cancelEvent(nce->arTimer);
    }
}

void IPv6NeighbourDiscovery:: processNAForOtherNCEStates(
        inet::IPv6NeighbourAdvertisement *na, Neighbour *nce)
{
    bool naRouterFlag = na->getRouterFlag();
    bool naSolicitedFlag = na->getSolicitedFlag();
    bool naOverrideFlag = na->getOverrideFlag();
    MACAddress naMacAddr = na->getTargetLinkLayerAddress();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->getInterfaceById(nceKey->interfaceID);

    /*draft-ietf-ipv6-2461bis-04
    Section 7.2.5: Receipt of Neighbour Advertisements
    If the target's Neighbor Cache entry is in any state other than INCOMPLETE
    when the advertisement is received, the following actions take place:*/

    if (naOverrideFlag == false && !(naMacAddr.equals(nce->macAddress))
        && !(naMacAddr.isUnspecified()))
    {
        std::cout << "NA override is FALSE and NA MAC addr is different.\n";
        //I. If the Override flag is clear and the supplied link-layer address
        //   differs from that in the cache, then one of two actions takes place:
        //(Note: An unspecified MAC should not be compared with the NCE's mac!)
        //a. If the state of the entry is REACHABLE,
        if (nce->reachabilityState == IPv6NeighbourCache::REACHABLE)
        {
            std::cout << "NA mac is different. Change NCE state from REACHABLE to STALE\n";
            //set it to STALE, but do not update the entry in any other way.
            nce->reachabilityState = IPv6NeighbourCache::STALE;
        }
        else
            //b. Otherwise, the received advertisement should be ignored and
            //MUST NOT update the cache.
            std::cout << "NCE is not in REACHABLE state. Ignore NA.\n";
    }
    else if (naOverrideFlag == true || naMacAddr.equals(nce->macAddress)
        || naMacAddr.isUnspecified())
    {
        std::cout << "NA override flag is TRUE. or Advertised MAC is same as NCE's. or"
           << " NA MAC is not specified.\n";
        /*II. If the Override flag is set, or the supplied link-layer address
        is the same as that in the cache, or no Target Link-layer address
        option was supplied, the received advertisement MUST update the
        Neighbor Cache entry as follows:*/

        /*- The link-layer address in the Target Link-Layer Address option
            MUST be inserted in the cache (if one is supplied and is
            Different than the already recorded address).*/
        if (!(naMacAddr.isUnspecified()) &&
            !(naMacAddr.equals(nce->macAddress)))
        {
            std::cout << "Updating NCE's MAC addr with NA's.\n";
            nce->macAddress = naMacAddr;
        }

        //- If the Solicited flag is set,
        if (naSolicitedFlag == true)
        {
            std::cout << "Solicited Flag is TRUE. Set NCE state to REACHABLE.\n";
            //the state of the entry MUST be set to REACHABLE.
            nce->reachabilityState = IPv6NeighbourCache::REACHABLE;
            //We have to cancel the NUD self timer message if there is one.
            inet::cMessage *msg = nce->nudTimeoutEvent;
            if (msg != NULL)
            {
                std::cout << "NUD in progress. Cancelling NUD Timer\n";
                bubble("Reachability Confirmed via NUD.");
                nce->reachabilityExpires = inet::simTime() + ie->ipv6Data()->_getReachableTime();
                cancelEvent(msg);
                delete msg;
            }
            nce->nudTimeoutEvent = NULL;
        }
        else
        {
            //If the Solicited flag is zero
            std::cout << "Solicited Flag is FALSE.\n";
            //and the link layer address was updated with a different address
            if (!(naMacAddr.equals(nce->macAddress)))
            {
                std::cout << "NA's MAC is different from NCE's.Set NCE state to STALE\n";
                //the state MUST be set to STALE.
                nce->reachabilityState = IPv6NeighbourCache::STALE;
            }
            else
                //Otherwise, the entry's state remains unchanged.
                std::cout << "NA's MAC is the same as NCE's. State remains unchanged.\n";
        }
        //(Next paragraph with explanation is omitted.-WEI)

        /*- The IsRouter flag in the cache entry MUST be set based on the
        Router flag in the received advertisement.*/
        std::cout << "Updating NCE's router flag to " << naRouterFlag << endl;
        nce->isRouter = naRouterFlag;

        //TODO: To be implemented
        /*In those cases where the IsRouter flag changes from TRUE to FALSE as a
        result of this update, the node MUST remove that router from the Default
        Router List and update the Destination Cache entries for all destinations
        using that neighbor as a router as specified in Section 7.3.3. This is
        needed to detect when a node that is used as a router stops forwarding
        packets due to being configured as a host.*/
    }
}

inet::IPv6Redirect *IPv6NeighbourDiscovery::createAndSendRedirectPacket(InterfaceEntry *ie)
{
    //Construct a Redirect message
    inet::IPv6Redirect *redirect = new inet::IPv6Redirect("redirectMsg");
    redirect->setType(inet::ICMPv6_REDIRECT);

    //Redirect Message Specific Information
    //redirect->setTargetAddress();
    //redirect->setDestinationAddress();

    //Possible Option
    //redirect->setTargetLinkLayerAddress();

    return redirect;
}

void IPv6NeighbourDiscovery::processRedirectPacket(inet::IPv6Redirect *redirect,
    IPv6ControlInfo *ctrlInfo)
{
    //First we need to extract information from the redirect message
    IPv6Address targetAddr = redirect->getTargetAddress();//Addressed to me
    IPv6Address destAddr = redirect->getDestinationAddress();//new dest addr

    //Optional
    MACAddress macAddr = redirect->getTargetLinkLayerAddress();
}


//The overlaoded function has been added by zarrar yousaf on 20.07.07
void IPv6NeighbourDiscovery::processRAPrefixInfoForAddrAutoConf(inet::IPv6NDPrefixInformation& prefixInfo, InterfaceEntry* ie, bool hFlag)
{
    std::cout << "Processing Prefix Info for address auto-configuration.\n";
    IPv6Address prefix = prefixInfo.getPrefix();
    uint prefixLength = prefixInfo.getPrefixLength();
    inet::simtime_t preferredLifetime = prefixInfo.getPreferredLifetime();
    inet::simtime_t validLifetime = prefixInfo.getValidLifetime();

    //EV << "/// prefix: " << prefix << std::endl; // CB

    //RFC 2461: Section 5.5.3
    //First condition tested, the autonomous flag is already set

    //b) If the prefix is the link-local prefix, silently ignore the Prefix
    //Information option.
    if (prefixInfo.getPrefix().isLinkLocal() == true)
    {
        std::cout << "Prefix is link-local, ignore Prefix Information Option\n";
        return;
    }

    //c) If the preferred lifetime is greater than the valid lifetime, silently
    //ignore the Prefix Information option. A node MAY wish to log a system
    //management error in this case.
    if (preferredLifetime > validLifetime)
    {
        std::cout << "Preferred lifetime is greater than valid lifetime, ignore Prefix Information\n";
        return;
    }

    // changed structure of code below, 12.9.07 - CB
    bool isPrefixAssignedToInterface = false;
    bool returnedHome = false; // 4.9.07 - CB

    for (int i = 0; i < ie->ipv6Data()->getNumAddresses(); i++)
	{
    	if ( ie->ipv6Data()->getAddress(i).getScope() == IPv6Address::LINK ){
    	    std::cout << "skip the link local address - it's not relevant for movement detection"<<endl;
    		continue;
        }

    	/*RFC 3775, 11.5.4
    	  A mobile node detects that it has returned to its home link through
          the movement detection algorithm in use (Section 11.5.1), when the
          mobile node detects that its home subnet prefix is again on-link. */
        if (ie->ipv6Data()->getAddress(i).matches(prefix, prefixLength) == true)
        {
			// A MN can have the following address combinations:
			// * only a link-local address -> at home
			// * link-local plus a HoA -> at home
			// * link-local, HoA plus CoA -> at foreign network
        	// The prefix of the home network can only match the HoA
        	// address, and if it does (=we received a RA from the HA),
        	// and we have a CoA as well (three addresses) then we have
        	// returned home
        	// TODO the MN can have several global scope addresses configured from
        	// different prefixes advertised via a RA -> not supported with this code
            std::cout << "Mobile Node has moved to different network" << endl; // Adam
        	if ( rt6->isMobileNode() && ie->ipv6Data()->getAddressType(i) == IPv6InterfaceData::HoA && ie->ipv6Data()->getNumAddresses() > 2)
        		returnedHome = true;
        	else
        	{
	        	isPrefixAssignedToInterface = true;
	        	std::cout <<"The received Prefix is already assigned to the interface"<<endl; //Zarrar Yousaf 19.07.07
	        	break;
        	}
		}
    }
    /*d) If the prefix advertised does not match the prefix of an address already
         in the list, and the Valid Lifetime is not 0, form an address (and add
         it to the list) by combining the advertised prefix with the link's
         interface identifier as follows:*/
	    if ( (isPrefixAssignedToInterface == false) && (validLifetime != 0) )
	    {
	        std::cout<<"Prefix not assigned to interface. Possible new router detected. Auto-configuring new address."<<endl;
		    IPv6Address linkLocalAddress = ie->ipv6Data()->getLinkLocalAddress();
		    ASSERT(linkLocalAddress.isUnspecified() == false);
		    IPv6Address newAddr = linkLocalAddress.setPrefix(prefix, prefixLength);
		    IPv6Address CoA;
		    //TODO: for now we leave the newly formed address as not tentative,
		    //according to Greg, we have to always perform DAD for a newly formed address.
		    std::cout << "Assigning new address to: " << ie->getName() << endl;

			// we are for sure either in the home network or in a new foreign network
			// -> remove CoA
			//CoA = ie->ipv6()->removeCoAAddr();
			// moved code from above to processDADTimeout()

			// 27.9.07 - CB
			if ( returnedHome )
			{
				// we have to remove the CoA before we create a new one
			    std::cout << "Node returning home - removing CoA...\n";
			    std::cout << std::endl << ie->info() << std::endl;
				CoA = ie->ipv6Data()->removeAddress(IPv6InterfaceData::CoA);

				// nothing to do more wrt managing addresses, as we are at home and a HoA is
				// already existing at the interface

				// @todo: Fix this properly
				if (CoA.isUnspecified()) {
				    return;
				}
				// initiate the returning home procedure
				ASSERT( !CoA.isUnspecified() );
				mipv6->returningHome(CoA, ie);
			}
			else // non-mobile nodes will never have returnedHome == true, so they will always assign a new address
			{
				CoA = ie->ipv6Data()->getGlobalAddress(IPv6InterfaceData::CoA);

				// form new address and initiate DAD, as we are in a foreign network

				if ( ie->ipv6Data()->getNumAddresses() == 1 )
				{
					// we only have a link-layer and no unicast address of scope > link-local
					// this means DAD is already running or has already been completed
					// create a unicast address with scope > link-local
					bool isLinkLocalTentative = ie->ipv6Data()->isTentativeAddress( linkLocalAddress );
					// if the link local address is tentative, then we make the global unicast address tentative as well
					ie->ipv6Data()->assignAddress(newAddr, isLinkLocalTentative, inet::simTime()+validLifetime, inet::simTime()+preferredLifetime, hFlag);
				}
				else
				{
					// set tentative flag for all addresses on this interface
					for (int j=0; j < ie->ipv6Data()->getNumAddresses(); j++ )
					{
						// TODO improve this code so that only addresses are set to tentative which are
						// formed based on the link-local address from above
						ie->ipv6Data()->tentativelyAssign(j);
						std::cout << "Setting address " << ie->ipv6Data()->getAddress(j) << " to tentative." << std::endl;
					}

					initiateDAD(ie->ipv6Data()->getLinkLocalAddress(), ie);

			        // set MIPv6Init structure that will later on be used for initiating MIPv6 protocol after DAD was performed
					dadGlobalList[ie].hFlag = hFlag;
					dadGlobalList[ie].validLifetime = validLifetime;
					dadGlobalList[ie].preferredLifetime = preferredLifetime;
					dadGlobalList[ie].addr = newAddr;
					//dadGlobalList[ie].returnedHome = returnedHome;
					dadGlobalList[ie].CoA = CoA;
				}
			}
	    }
}


void IPv6NeighbourDiscovery::routersUnreachabilityDetection(const InterfaceEntry* ie)
{
	// remove all entries from the destination cache for this interface
	//rt6->purgeDestCacheForInterfaceID( ie->interfaceId() );
	// invalidate entries in the destination cache for this interface
	//neighbourCache.invalidateEntriesForInterfaceID( ie->interfaceId() );
	// remove default routes on this interface
	rt6->removeDefaultRoutes( ie->getInterfaceId() );
	rt6->removePrefixes( ie->getInterfaceId() );

	for( IPv6NeighbourCache::iterator it=neighbourCache.begin(); it != neighbourCache.end(); )
	{
		if ( (*it).first.interfaceID == ie->getInterfaceId() &&  it->second.isDefaultRouter )
		{
			// update 14.9.07 - CB
			IPv6Address rtrLnkAddress = (*it).first.address;
			std::cout << "Setting router (address=" << rtrLnkAddress << ", ifID=" << (*it).first.interfaceID << ") to unreachable" << std::endl;
			++it;

			//if ( rtrLnkAddress.isLinkLocal() )
				timeoutDefaultRouter(rtrLnkAddress, ie->getInterfaceId() );

			// reset reachability state of this router
			//Neighbour* nbor = neighbourCache.lookup( (*it).first.address, (*it).first.interfaceID );
			//nbor->reachabilityState = IPv6NeighbourCache::STALE;
			//initiateNeighbourUnreachabilityDetection(nbor);
		}
		else
			++it;
	}
}


void IPv6NeighbourDiscovery::invalidateNeigbourCache()
{
	//Enter_Method("Invalidating Neigbour Cache Entries");
	neighbourCache.invalidateAllEntries();
}

bool IPv6NeighbourDiscovery::isConnectedToWirelessAP(InterfaceEntry *ie)
{
	//EV<<"Determination of whether an interface is connected to a WLAN AP or not."<<endl;
	inet::cModule* node = findContainingNode(this); // FIXME find the node ancestor by @node
    // Adam wyjatek na BS[0] i BS[1]
    
    if( node -> findSubmodule("bsMac") != -1  )
        return true;
    inet::cGate* gate = node->gate(ie->getNodeOutputGateId());
	ASSERT(gate!=NULL); //to make sure that the gate exists
	// TODO generalize
	inet::cGate* connectedGate = gate->getNextGate();
	std::cout << "connectedGate->getFullName()=" << connectedGate->getFullName() << "  connectedGate->getOwnerModule()=" << connectedGate->getOwnerModule() << std::endl;
	std::cout << "isNode(connectedGate->getOwnerModule())=" << isNode(connectedGate->getOwnerModule());
    if (connectedGate!=NULL)
	{
		ASSERT(isNode(connectedGate->getOwnerModule()));
		inet::cModule* wlanMAC = connectedGate->getOwnerModule()->getSubmodule("relayUnit");
		if ( wlanMAC!=NULL )
			return true;
		else
		{
			wlanMAC = connectedGate->getOwnerModule()->getSubmodule("wlan");//to search for a "wlan" module which, in the INET fw scheme of things, resides inside a WLAN AP
			return wlanMAC!=NULL;
		}
	}
	return false;
}

