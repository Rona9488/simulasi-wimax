//
// Copyright (C) 2005 Wei Yang, Ng
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, see <http://www.gnu.org/licenses/>.
//

cplusplus {{
#include "ICMPv6Message_m.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6Address.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\linklayer\contract\MACAddress.h"
}}
namespace inet;

packet ICMPv6Message;

class noncobject IPv6Address;

class noncobject MACAddress;
// IPv6ND Prefix Information (RFC 2461 Section 4.6.2)
class IPv6NDPrefixInformation {
        unsigned int prefixLength;
        bool onlinkFlag;            // L-bit
        bool autoAddressConfFlag;   // A-bit
        bool routerAddress;         // R-bit: used in case of MIPv6 when the H-bit is set
        unsigned int validLifetime;
        unsigned int preferredLifetime;
        IPv6Address prefix;
}


// MIPv6 New Advertisement Interval Option (RFC 3775 Section 7.3)
class MIPv6NDAdvertisementInterval {
        unsigned int advertisementInterval; // MUST be equal to "maxRtrAdvInterval"
}

// MIPv6 Home Agent Information Option (RFC 3775 Section 7.4)
class MIPv6HAInformation {
        unsigned int homeAgentPreference;
        unsigned int homeAgentLifetime;
}

// Neighbour Discovery for IPv6 (RFC 2461)
// Base message for IPv6 Neighbor Discovery
packet IPv6NDMessage extends ICMPv6Message {
        int code = 0;
}

// Router Solicitation Message Format (RFC 2461 Section 4.1)
packet IPv6RouterSolicitation extends IPv6NDMessage {
        MACAddress sourceLinkLayerAddress; // Possible Options
}

// Router Advertisement Message Format (RFC 2461 Section 4.2)
packet IPv6RouterAdvertisement extends IPv6NDMessage {
        unsigned int curHopLimit;
        bool managedAddrConfFlag;         // M-bit
        bool otherStatefulConfFlag;       // O-bit
        bool homeAgentFlag = false;       // H-bit (default false, 4.9.07 - CB)
        unsigned short routerLifetime;    // 0 indicates router is not a default router
        unsigned int reachableTime;
        unsigned int retransTimer;
        MACAddress sourceLinkLayerAddress; // Source Link Layer Option
        unsigned int MTU;                  // MTU Option
        IPv6NDPrefixInformation prefixInformation[]; // Prefix Information Option
        MIPv6NDAdvertisementInterval advInterval;    // New Advertisement Interval Option (MIPv6)
        MIPv6HAInformation haInformation;            // New Home Agent Information Option (MIPv6)
}

// Neighbour Solicitation Message Format (RFC 2461 Section 4.3)
packet IPv6NeighbourSolicitation extends IPv6NDMessage {
        IPv6Address targetAddress; // MUST NOT be a multicast address
        MACAddress sourceLinkLayerAddress; // Possible Options
}

// Neighbour Advertisement Message Format (RFC 2461 Section 4.4)
packet IPv6NeighbourAdvertisement extends IPv6NDMessage {
        bool routerFlag;            // R-flag
        bool solicitedFlag;         // S-flag
        bool overrideFlag;          // O-flag
        IPv6Address targetAddress;  // MUST NOT be a multicast address
        MACAddress targetLinkLayerAddress; // Target Link Layer Address Option
}

// Redirect Message Format (RFC 2461 Section 4.5)
packet IPv6Redirect extends IPv6NDMessage {
        IPv6Address targetAddress;
        IPv6Address destinationAddress;
        MACAddress targetLinkLayerAddress;
}

// Additional Message for Address Notification
// Adam, 14-09-2011
packet IPv6AssignAddressNotify extends IPv6NDMessage {
        int AP_ID;
        MACAddress L2_Addr;
        IPv6Address L3_Addr;
        IPv6Address Prefix;
        int PrefixLength;
}
