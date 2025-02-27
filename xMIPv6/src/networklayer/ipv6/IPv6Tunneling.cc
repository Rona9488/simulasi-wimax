/**
 * Copyright (C) 2007
 * Christian Bauer
 * Institute of Communications and Navigation, German Aerospace Center (DLR)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

//
// Implementation of RFC 2473
// Generic Packet Tunneling in IPv6
//
// This module implements the basic tunneling functionality.
// Packet flow is modeled as in the RFC: each two input and output
// gates are used to exchange packets with the IPv6 core.
//
// Not implemented:
//	- 4.1.1
//	- 5.1
//	- 7.
//
// TODO
//	- 8.: Tunnel Error Reporting and Processing


#include <omnetpp.h>
#include <stdlib.h>
#include <string.h>
#include "IPv6Tunneling.h"
#include "IPv6Datagram.h"
#include "IPv6InterfaceData.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6ControlInfo.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\xmipv6\MobilityHeader_m.h"// for HA Option header
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\xmipv6\xMIPv6Access.h"

#include <algorithm>
#include <utility>


Define_Module(IPv6Tunneling);

IPv6Tunneling::IPv6Tunneling()
{
	ift = NULL;
	rt = NULL;
}


void IPv6Tunneling::initialize()
{
	ift = InterfaceTableAccess().get();
	rt = RoutingTable6Access().get();

	vIfIndexTop = INT_MAX; // virtual interface number set to maximum int value
	noOfNonSplitTunnels = 0; // current number of non-split tunnels on this host

	WATCH_MAP(tunnels);
}


void IPv6Tunneling::handleMessage(inet::cMessage* msg)
{
	if (msg->getArrivalGate()->isName("upperLayerIn") && dynamic_cast<IPv6Datagram*>(msg))
	{
		// decapsulate
		IPv6Datagram *dgram = check_and_cast<IPv6Datagram*>(msg);
		decapsulateDatagram(dgram);
	}
	else if (msg->getArrivalGate()->isName("linkLayerIn") && dynamic_cast<IPv6Datagram*>(msg))
	{
		// encapsulate
		IPv6Datagram *dgram = check_and_cast<IPv6Datagram*>(msg);
		encapsulateDatagram(dgram);
	}
	else
		throw inet::cException("IPv6Tunneling: Unknown message type - must be IPv6Datagram!");
}


IPv6Tunneling::Tunnel::Tunnel(const IPv6Address& _entry, const IPv6Address& _exit, const IPv6Address& _destTrigger)
	:entry(_entry), exit(_exit), destTrigger(_destTrigger), tunnelType(SPLIT), tunnelMTU(IPv6_MIN_MTU - 40)
{}


int IPv6Tunneling::createTunnel(TunnelType tunnelType, const IPv6Address& entry, const IPv6Address& exit, const IPv6Address& destTrigger)
{
	ASSERT(entry!=IPv6Address::UNSPECIFIED_ADDRESS);
	ASSERT(exit!=IPv6Address::UNSPECIFIED_ADDRESS);

	// Test for entry and exit point node pointing to same node i.e. localDeliver
	// addresses to prevent loopback encapsulation 4.1.2
	if ( (tunnelType == NORMAL || tunnelType == SPLIT || tunnelType == NON_SPLIT) // check does not work for T2RH or HoA_Opt. Why?
		 && rt->isLocalAddress(entry) && rt->isLocalAddress(exit) )
	{
		std::cout << "Cannot create tunnel with local endpoints (prevents loopback tunneling)" << std::endl;
		return 0;
	}

	int search = findTunnel(entry, exit, destTrigger);
	if (search != 0)
	{
		std::cout << "Tunnel with entry = " << entry << ", exit = " << exit << " and trigger = "
		   << destTrigger << " already exists!" << std::endl;
		return search;
	}

	if ( vIfIndexTop == (ift->getNumInterfaces() - 1) )
		throw inet::cException("Error: Not more than %d tunnels supported!", INT_MAX - ift->getNumInterfaces());

	if ( (destTrigger == IPv6Address::UNSPECIFIED_ADDRESS) && (noOfNonSplitTunnels == 1) )
		throw inet::cException("Error: Not more than 1 non-split tunnel supported!");

	// 6.1-6.2
	ASSERT( entry.isUnicast() );
	tunnels[vIfIndexTop] = Tunnel(entry, exit, destTrigger);

	if ( tunnelType == NORMAL || tunnelType == SPLIT || tunnelType == NON_SPLIT )
	{
	 	if (destTrigger == IPv6Address::UNSPECIFIED_ADDRESS)
		{
			// this is a "full" tunnel over which everything gets routed
			tunnels[vIfIndexTop].tunnelType = NON_SPLIT;
			noOfNonSplitTunnels++;
		}

		// default values: 5.
		// 6.4
		tunnels[vIfIndexTop].trafficClass = 0;
		// 6.5
		tunnels[vIfIndexTop].flowLabel = 0;
		// 6.3
		// The tunnel hop limit default value for hosts is the IPv6 Neighbor
		// Discovery advertised hop limit [ND-Spec].
		if ( rt->isRouter() )
			tunnels[vIfIndexTop].hopLimit = IPv6__INET_DEFAULT_ROUTER_HOPLIMIT;
		else
			tunnels[vIfIndexTop].hopLimit = 255;
		// 6.7
		// TODO perform path MTU on link (interface resolved via exit address)
		tunnels[vIfIndexTop].tunnelMTU = IPv6_MIN_MTU - 40;

		std::cout << "Tunneling: Created tunnel with entry=" << entry << ", exit=" << exit << " and trigger=" << destTrigger << std::endl;
	}
	else if ( tunnelType == T2RH || tunnelType == HA_OPT )
	{
		tunnels[vIfIndexTop].tunnelType = tunnelType;

		if (tunnelType == T2RH)
			std::cout << "Tunneling: Created RH2 path with entry=" << entry << ", exit=" << exit << " and trigger=" << destTrigger << std::endl;
		else
			std::cout << "Tunneling: Created HA option path with entry=" << entry << ", exit=" << exit << " and trigger=" << destTrigger << std::endl;
	}
	else
	{
		throw inet::cException("tunnel type %d not supported for createTunnel()", tunnelType);
	}

	if (!inet::getEnvir()->isGUI())
		bubble("Created Tunnel");

	return vIfIndexTop--; // decrement vIfIndex for use with next createTunnel() call
}



int IPv6Tunneling::findTunnel(const IPv6Address& src, const IPv6Address& dest, const IPv6Address& destTrigger) const
{
	TI it = find_if( tunnels.begin(), tunnels.end(), bind1st( equalTunnel(), std::make_pair( (int) 0, Tunnel(src, dest, destTrigger) ) ) );
	if (it != tunnels.end())
		return it->first;
	return 0;
}


bool IPv6Tunneling::destroyTunnel(const IPv6Address& src, const IPv6Address& dest, const IPv6Address& destTrigger)
{
	std::cout << "Destroy tunnel entry =" << src << ", exit = " << dest << ", destTrigger = " << destTrigger << "\n";

	// search for tunnel with given entry and exit point as well as trigger
	int vIfIndex = findTunnel(src, dest, destTrigger);

	if (vIfIndex == 0)
	{
		std::cout << "Tunnel not found\n";
		return false;
	}

	// if we delete a non-split tunnel, then we can
	// also decrement the appropriate counter
	if ( tunnels[vIfIndex].tunnelType == NON_SPLIT )
		noOfNonSplitTunnels--;

	// TODO store vIfIndex for later reuse when creating a new tunnel
	tunnels.erase(vIfIndex);

	// reset the index if we do not have a single tunnel anymore
	resetVIfIndex();

	if (!inet::getEnvir()->isGUI())
		bubble("Destroyed Tunnel");

	return true;
}


void IPv6Tunneling::destroyTunnel(const IPv6Address& entry, const IPv6Address& exit)
{
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); )
	{
    	if (it->second.entry == entry && it->second.exit == exit)
        {
    		destroyTunnel(it->second.entry, it->second.exit, it->second.destTrigger);
    		break;
        }
    	else
    		++it;
    }

	// reset the index if we do not have a single tunnel anymore
	resetVIfIndex();
}


void IPv6Tunneling::destroyTunnelForExitAndTrigger(const IPv6Address& exit, const IPv6Address& trigger)
{
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); )
	{
    	if (it->second.exit == exit && it->second.destTrigger == trigger)
        {
    		destroyTunnel(it->second.entry, it->second.exit, it->second.destTrigger);
    		break;
        }
    	else
    		++it;

    }

	// reset the index if we do not have a single tunnel anymore
	resetVIfIndex();
}


void IPv6Tunneling::destroyTunnelForEntryAndTrigger(const IPv6Address& entry, const IPv6Address& trigger)
{
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); )
	{
    	if (it->second.entry == entry && it->second.destTrigger == trigger)
        {
    		destroyTunnel(it->second.entry, it->second.exit, it->second.destTrigger);
    		break;
        }
    	else
    		++it;

    }

	// reset the index if we do not have a single tunnel anymore
	resetVIfIndex();
}


void IPv6Tunneling::destroyTunnels(const IPv6Address& entry)
{
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); )
	{
    	if (it->second.entry == entry)
        {
    		Tunnels::iterator oldIt = it;
    		++it;

    		destroyTunnel(oldIt->second.entry, oldIt->second.exit, oldIt->second.destTrigger);
        }
    	else
    		++it;

    }

	// reset the index if we do not have a single tunnel anymore
	resetVIfIndex();
}


void IPv6Tunneling::destroyTunnelFromTrigger(const IPv6Address& trigger)
{
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); ++it)
	{
    	if (it->second.destTrigger == trigger)
        {
    		destroyTunnel(it->second.entry, it->second.exit, it->second.destTrigger);

    		// reset the index if we do not have a single tunnel anymore
    		resetVIfIndex();

    		return; // there can not be more than one tunnel for a trigger
        }
    }

}


int IPv6Tunneling::getVIfIndexForDest(const IPv6Address& destAddress)
{
    //Enter_Method("Looking up Tunnels (%s)", destAddress.str().c_str());
	std::cout << "Looking up tunnels...";

	// first we look for tunnels with destAddress as trigger
    int vIfIndex = lookupTunnels(destAddress);

	if (vIfIndex == -1)
	{
		// then the only chance left for finding a suitable tunnel
		// is to find a non-split tunnel
		vIfIndex = doPrefixMatch(destAddress);
	}

	std::cout << "found vIf=" << vIfIndex << std::endl;

	return vIfIndex;
}


int IPv6Tunneling::getVIfIndexForDest(const IPv6Address& destAddress, TunnelType tunnelType)
{
	int outInterfaceId = -1;

    for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); it++)
    {
    	if (tunnelType == NORMAL || tunnelType == NON_SPLIT || tunnelType == SPLIT )
    	{
        	// we search here for tunnels which have a destination trigger and
        	// check whether the trigger is equal to the destination
        	// only "normal" tunnels, both split and non-split, are possible entry points
        	if ( (it->second.tunnelType == NON_SPLIT) ||
        		 (it->second.tunnelType == SPLIT && it->second.destTrigger == destAddress)
        	   )
            {
            	outInterfaceId = it->first;
            	break;
            }
    	}
    	else if ( tunnelType == MOBILITY || tunnelType == HA_OPT || tunnelType == T2RH)
    	{
   	    	if ( it->second.tunnelType != NON_SPLIT &&
   	    		 it->second.tunnelType != SPLIT &&
   	    		 it->second.destTrigger == destAddress
   	    	   )
   	        {
   	        	outInterfaceId = it->first;
   	        	break;
   	        }
    	}
    }

    return outInterfaceId;
}


void IPv6Tunneling::encapsulateDatagram(IPv6Datagram* dgram)
{
	int vIfIndex = -1;

	if ( dgram->getTransportProtocol() == IP_PROT_IPv6EXT_MOB )
	{
		// only look at non-split tunnel
		// (HoTI is only sent over HA tunnel)
		vIfIndex = doPrefixMatch( dgram->getDestAddress() );
	}

	if ( (dgram->getTransportProtocol() != IP_PROT_IPv6EXT_MOB) || (vIfIndex == -1) )
	{
		// look up all tunnels for dgram's destination
		vIfIndex = getVIfIndexForDest( dgram->getDestAddress() );
		//std::cout << "looked up again!" << std::endl;
	}

	if (vIfIndex == -1)
		throw inet::cException("encapsulateDatagram(): tunnel not existent");

	// TODO copy information from old ctrlInfo into new one (Traffic Class, Flow label, etc.)
	delete dgram->removeControlInfo();

	if ( (tunnels[vIfIndex].tunnelType == T2RH) || (tunnels[vIfIndex].tunnelType == HA_OPT) )
	{
		// pseudo-tunnel for Type 2 Routing Header
		// or Home Address Option

		IPv6Address src = dgram->getSrcAddress();
		IPv6Address dest = dgram->getDestAddress();
		IPv6Address rh2; //dest

		if ( src.isUnspecified() )
		{
			// if we do not have a valid source address, we'll have to ask
			// the routing table for the correct interface.
			int interfaceId;
			IPv6Address nextHop = rt->lookupDestCache(dest, interfaceId);
		}

		if (tunnels[vIfIndex].tunnelType == T2RH) // update 15.01.08 - CB
		{
			// this is the CN -> MN path
			src = tunnels[vIfIndex].entry; // CN address
			dest = tunnels[vIfIndex].exit; // CoA
			rh2 = tunnels[vIfIndex].destTrigger; // HoA
		}
		else
		{
			// path MN -> CN
			src = tunnels[vIfIndex].entry; // CoA
			dest = tunnels[vIfIndex].destTrigger; // CN address
			rh2 = tunnels[vIfIndex].exit; // HoA
		}

		// and now construct the new control info for the packet
		IPv6ControlInfo* controlInfo = new IPv6ControlInfo();
		controlInfo->setProtocol( dgram->getTransportProtocol() );

		// get rid of the encapsulation of the IPv6 module
		inet::cMessage* packet = dgram->decapsulate();
		delete dgram;

		if ( tunnels[vIfIndex].tunnelType == T2RH )
		{
			// construct Type 2 Routing Header (RFC 3775 - 6.4.1)
			/*For a type 2 routing header, the Hdr Ext Len MUST be 2.  The Segments
	   		  Left value describes the number of route segments remaining; i.e.,
	   		  number of explicitly listed intermediate nodes still to be visited
	   		  before reaching the final destination.  Segments Left MUST be 1.*/
			IPv6RoutingHeader* t2RH = new IPv6RoutingHeader();
			t2RH->setRoutingType(2);
			t2RH->setSegmentsLeft(1);
			t2RH->setAddressArraySize(1);
			// old src becomes address of T2RH
			t2RH->setAddress(0, rh2);

			// append T2RH to routing headers
			controlInfo->addExtensionHeader(t2RH);

			std::cout << "Added Type 2 Routing Header." << std::endl;
		}
		else // HA_OPT
		{
			/*The Home Address option is carried by the Destination Option
   			  extension header (Next Header value = 60).  It is used in a packet
   			  sent by a mobile node while away from home, to inform the recipient
   			  of the mobile node's home address.*/
			HomeAddressOption* haOpt = new HomeAddressOption();
			haOpt->setHomeAddress(rh2);

			// append HA option to routing headers
			controlInfo->addExtensionHeader(haOpt);

			std::cout << "Added Home Address Option header." << std::endl;
		}

		// new src is tunnel entry (either CoA or CN)
		controlInfo->setSrcAddr( src );
		// copy old dest addr
		controlInfo->setDestAddr( dest );

		packet->setControlInfo(controlInfo);
		send(packet, "upperLayerOut");
	}
	else
	{
		// normal tunnel - just modify controlInfo and send
		// datagram back to IPv6 module for encapsulation

		IPv6ControlInfo* controlInfo = new IPv6ControlInfo();
		controlInfo->setProtocol(IP_PROT_IPv6);
		controlInfo->setSrcAddr( tunnels[vIfIndex].entry );
		controlInfo->setDestAddr( tunnels[vIfIndex].exit );
		controlInfo->setInterfaceId(-1);

		dgram->setControlInfo(controlInfo);
		send(dgram, "upperLayerOut");
	}
}


void IPv6Tunneling::decapsulateDatagram(IPv6Datagram* dgram)
{
	// decapsulation is performed in IPv6 module
	// just update controlInfo
	IPv6ControlInfo *controlInfo = check_and_cast<IPv6ControlInfo*>(dgram->removeControlInfo());

	// Alain Tigyo, 21.03.2008
	InterfaceEntry *ie = ift->getInterfaceById( controlInfo->getInterfaceId() );

	// we only decapsulate packets for which we have a tunnel
	// where the exit point is equal to the packets source
	// 11.9.07 - CB
	if ( !isTunnelExit( controlInfo->getSrcAddr()) )
	{
		/*RFC 3775, 10.4.5
		  Otherwise, when a home agent decapsulates a tunneled packet from
		  the mobile node, the home agent MUST verify that the Source
		  Address in the tunnel IP header is the mobile node's primary
		  care-of address.  Otherwise, any node in the Internet could send
		  traffic through the home agent and escape ingress filtering
		  limitations.  This simple check forces the attacker to know the
		  current location of the real mobile node and be able to defeat
		  ingress filtering. This check is not necessary if the reverse-
		  tunneled packet is protected by ESP in tunnel mode.*/
		std::cout << "Dropping packet: source address of tunnel IP header different from tunnel exit points!" << std::endl;
		delete controlInfo;
		delete dgram;
		return;
	}

	// FIX: we leave the interface Id to it's previous value to make sure
	// that later processing knowns from which interface the datagram came from
	// (important if several interfaces are available)
	//controlInfo->setInterfaceId(-1);
	dgram->setControlInfo(controlInfo);

	send(dgram, "linkLayerOut");

	// Alain Tigyo, 21.03.2008
	// The following code is used for triggering RO to a CN
	if ( rt->isMobileNode() && (controlInfo->getSrcAddr() == ie->ipv6Data()->getHomeAgentAddress())
		 && (dgram->getTransportProtocol() != IP_PROT_IPv6EXT_MOB) )
	{
		std::cout << "Checking Route Optimization for: " << dgram->getSrcAddress() << std::endl;
		xMIPv6* mipv6 = NULL;
		mipv6 = xMIPv6Access().getIfExists();
		if (!mipv6)
			return;
		mipv6->triggerRouteOptimization( dgram->getSrcAddress(), ie->ipv6Data()->getMNHomeAddress(), ie);
	}
}


int IPv6Tunneling::lookupTunnels(const IPv6Address& dest)
{
	int outInterfaceId = -1;

	// we search here for tunnels which have a destination trigger and
	// check whether the trigger is equal to the destination
	// only split tunnels or mobility paths are possible entry points
    for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); it++)
    {
    	if ( (it->second.tunnelType != NON_SPLIT) && (it->second.destTrigger == dest) )
        {
        	outInterfaceId = it->first;
        	break;
        }
    }

    return outInterfaceId;
}


int IPv6Tunneling::doPrefixMatch(const IPv6Address& dest)
{
    int outInterfaceId = -1;

    // we'll just stop at the first match, because it is assumed that not
    // more than a single non-split tunnel is possible
	for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); it++)
    {
		if ( it->second.tunnelType == NON_SPLIT )
		{
			outInterfaceId = it->first;
			break;
		}
    }

	return outInterfaceId;
}


bool IPv6Tunneling::isTunnelExit(const IPv6Address& exit)
{
    for (Tunnels::iterator it=tunnels.begin(); it!=tunnels.end(); it++)
    {
    	// mobility "tunnels" are not relevant for decapsulation
    	// 17.10.07 - same for Home Address Option
    	if ( it->second.tunnelType != T2RH && it->second.tunnelType != HA_OPT
    		 && it->second.exit == exit
    		)
        {
    		return true;
        }
    }

    return false;
}


/*TunnelType IPv6Tunneling::getTunnelType(const int vIfIndex)
{
	Tunnels::iterator i = tunnels.find(vIfIndex);

	if ( i == tunnels.end() )
		return 0;
	else
		return i->second.tunnelType;
}*/


std::ostream& operator<<(std::ostream& os, const IPv6Tunneling::Tunnel& tun)
{
	os << "tunnel entry = " << tun.entry << ", exit = " << tun.exit << ", tunnelMTU = "
		<< tun.tunnelMTU << ", dest = " << tun.destTrigger << ", type: ";

	switch (tun.tunnelType)
	{
		case IPv6Tunneling::SPLIT:
			os << "split tunnel";
			break;
		case IPv6Tunneling::NON_SPLIT:
			os << "non-split tunnel";
			break;
		case IPv6Tunneling::T2RH:
			os << "T2RH path";
			break;
		case IPv6Tunneling::HA_OPT:
			os << "Home Address Option path";
			break;
		default:
			throw inet::cException("Not a valid type for an existing tunnel!");
			break;
	}

	os << std::endl;

	return os;
}
