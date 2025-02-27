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

#ifndef IPV6NEIGHBOURDISCOVERY_H
#define IPV6NEIGHBOURDISCOVERY_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6Address.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6Datagram.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\IPv6NDMessage_m.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6ControlInfo.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6InterfaceData.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceEntry.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\IInterfaceTable.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTableAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\RoutingTable6.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\RoutingTable6Access.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\IPv6NeighbourCache.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\ICMPv6.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\ICMPv6Access.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\linklayer\contract\MACAddress.h"

//#include "xMIPv6Access.h" // 13.9.07 - CB

/**
 * Implements RFC 2461 Neighbor Discovery for IPv6.
 */
class INET_API IPv6NeighbourDiscovery : public omnetpp::cSimpleModule
{
    public:
        typedef std::vector<omnetpp::cMessage*> MsgPtrVector;
        typedef IPv6NeighbourCache::Key Key;//for convenience
        typedef IPv6NeighbourCache::Neighbour Neighbour;  // for convenience

    public:
        IPv6NeighbourDiscovery();
        virtual ~IPv6NeighbourDiscovery();

    private:
	//bool MIPv6Enabled; //zarrar yousaf 14.07.07
	//double minRAInterval; //zarrar yousaf 15.07.07
	//double maxRAInterval; //zarrar yousaf 15.07.07
    inet::cOutVector statVectorStartDAD;

    public:
        /**
         * Public method, to be invoked from the IPv6 module to determine
         * link-layer address and the output interface of the next hop.
         *
         * If the neighbor cache does not contain this address or it's in the
         * state INCOMPLETE, this method will return the NULL address, and the
         * IPv6 module should then send the datagram here to IPv6NeighbourDiscovery
         * where it will be stored until neighbour resolution completes.
         *
         * If the neighbour cache entry is STALE (or REACHABLE but more than
         * reachableTime elapsed since reachability was last confirmed),
         * the link-layer address is still returned and IPv6 can send the
         * datagram, but simultaneously, this call should trigger the Neighbour
         * Unreachability Detection procedure to start in the
         * IPv6NeighbourDiscovery module.
         */
        const MACAddress& resolveNeighbour(const IPv6Address& nextHop, int interfaceId);

        /**
         * Public method, it can be invoked from the IPv6 module or any other
         * module to let Neighbour Discovery know that the reachability
         * of the given neighbor has just been confirmed (e.g. TCP received
         * ACK of new data from it). Neighbour Discovery can then update
         * the neighbour cache with this information, and cancel the
         * Neighbour Unreachability Detection procedure if it is currently
         * running.
         */
        virtual void reachabilityConfirmed(const IPv6Address& neighbour, int interfaceId);
        IPv6NeighbourCache neighbourCache; // Adam zmiana z protected na public !!!

    protected:

        //Packets awaiting Address Resolution or Next-Hop Determination.
        inet::cQueue pendingQueue;

        IInterfaceTable *ift;
        InterfaceTable *ift2;
        RoutingTable6 *rt6;
        ICMPv6 *icmpv6;
        class INET_API xMIPv6 *mipv6; // in case the node has MIP support

        typedef std::set<omnetpp::cMessage*> RATimerList;

        // stores information about a pending Duplicate Address Detection for
        // an interface
        struct DADEntry {
            int interfaceId;// interface on which DAD is performed
            IPv6Address address;// link-local address subject to DAD
            int numNSSent;// number of DAD solicitations sent since start of sim
            omnetpp::cMessage *timeoutMsg;// the message to cancel when NA is received
        };
        typedef std::set<DADEntry*> DADList; //FIXME why ptrs are stored?

        //stores information about Router Discovery for an interface
        struct RDEntry {
            int interfaceId; //interface on which Router Discovery is performed
            int numRSSent; //number of Router Solicitations sent since start of sim
            omnetpp::cMessage *timeoutMsg; //the message to cancel when RA is received
        };
        typedef std::set<RDEntry*> RDList; //FIXME why ptrs are stored?

        //An entry that stores information for an Advertising Interface
        struct AdvIfEntry {
            int interfaceId;
            int numRASent;//number of Router Advertisements sent since start of sim
            omnetpp::simtime_t nextScheduledRATime;//stores time when next RA will be sent.
            omnetpp::cMessage *raTimeoutMsg;//the message to cancel when resetting RA timer
        };
        typedef std::set<AdvIfEntry*> AdvIfList; //FIXME why ptrs are stored?

        //List of periodic RA msgs(used only for router interfaces)
        RATimerList raTimerList;
        //List of pending Duplicate Address Detections
        DADList dadList;
        //List of pending Router & Prefix Discoveries
        RDList rdList;
        //List of Advertising Interfaces
        AdvIfList advIfList;

        // An entry that stores information for configuring the global unicast
        // address, after DAD was succesfully performed
        struct DADGlobalEntry
        {
        	bool hFlag; // home network flag from RA
            inet::simtime_t validLifetime; // valid lifetime of the received prefix
            inet::simtime_t preferredLifetime; // preferred lifetime of the received prefix
            IPv6Address addr; // the address with scope > link local that the interface will get

        	//bool returnedHome; // MIPv6-related: whether we returned home after a visit in a foreign network
        	IPv6Address CoA; // MIPv6-related: the old CoA, in case we returned home
        };
        typedef std::map<InterfaceEntry*, DADGlobalEntry> DADGlobalList;
        DADGlobalList dadGlobalList;

    protected:
        /************************Miscellaneous Stuff***************************/
        virtual int numInitStages() const {return 4;}
        virtual void initialize(int stage);
        virtual void handleMessage(omnetpp::cMessage *msg);
        virtual void processNDMessage(inet::ICMPv6Message *msg, IPv6ControlInfo *ctrlInfo);
        virtual void finish();

        virtual void processIPv6Datagram(IPv6Datagram *datagram);
        virtual IPv6NeighbourDiscovery::AdvIfEntry *fetchAdvIfEntry(InterfaceEntry *ie);
        virtual IPv6NeighbourDiscovery::RDEntry *fetchRDEntry(InterfaceEntry *ie);
        /************************End of Miscellaneous Stuff********************/
        /**
         *  This function accepts the datagram's destination address and attempts
         *  to determine the destination's next hop address and interface ID by:
         *  (1) looking up the destination cache, (2)looking up the routing table,
         *  or (3) selecting a default router. It then updates the destination
         *  cache. If no default router can be selected than we assume the
         *  destination address to be onlink and simply return any available
         *  interface.
         */
        virtual IPv6Address determineNextHop(const IPv6Address& destAddr, int& outIfID);
        virtual void initiateNeighbourUnreachabilityDetection(Neighbour *neighbour);
        virtual void processNUDTimeout(omnetpp::cMessage *timeoutMsg);
        virtual IPv6Address selectDefaultRouter(int& outIfID);
        /**
         *  RFC 2461: Section 6.3.5
         *  Whenever the invalidation timer expires for a Prefix List entry, that
         *  entry is discarded. No existing Destination Cache entries need be
         *  updated, however. Should a reachability problem arise with an
         *  existing Neighbor Cache entry, Neighbor Unreachability Detection will
         *  perform any needed recovery.
         */
        virtual void timeoutPrefixEntry(const IPv6Address& destPrefix, int prefixLength);
        /**
         *  RFC 2461: Section 6.3.5
         *  Whenever the Lifetime of an entry in the Default Router List expires,
         *  that entry is discarded. When removing a router from the Default
         *  Router list, the node MUST update the Destination Cache in such a way
         *  that all entries using the router perform next-hop determination
         *  again rather than continue sending traffic to the (deleted) router.
         */
        virtual void timeoutDefaultRouter(const IPv6Address& addr, int interfaceID);
        /**
         *  This method attempts to resolve the given neighbour's link-layer address.
         *  The source address of the packet prompting address resolution is also
         *  given in order to decide the source address of the NS to be sent.
         *  nceKey stores 2 pieces of information (Neighbour address and Interface ID)
         *  which is needed for addr resolution and access to the corresponding
         *  nce.
         */
        virtual void initiateAddressResolution(const IPv6Address& dgSrcAddr,
            Neighbour *nce);
        /**
         *  Resends a NS packet to the address intended for address resolution.
         *  TODO: Not implemented yet!
         */
        virtual void processARTimeout(omnetpp::cMessage *arTimeoutMsg);
        /**
         *  Drops specific queued packets for a specific NCE AR-timeout.
         *  TODO: Not implemented yet!
         */
        virtual void dropQueuedPacketsAwaitingAR(Neighbour *nce);
        /**
         *  Create control info and assigns it to a msg. Returns a copy of the
         *  msg with the control info.
         */
        virtual void sendPacketToIPv6Module(omnetpp::cMessage *msg, const IPv6Address& destAddr,
            const IPv6Address& srcAddr, int interfaceId);

        /**
         *  Send off any queued packets within the Neighbour Discovery module
         *  awaiting address resolution.
         */
        virtual void sendQueuedPacketsToIPv6Module(Neighbour *nce);

        /**
         *  Initiating DAD means to send off a Neighbour Solicitation with its
         *  target address set as this node's tentative link-local address.
         */
        virtual void initiateDAD(const IPv6Address& tentativeAddr, InterfaceEntry *ie);

        /**
         *  Sends a scheduled DAD NS packet. If number of sends is equals or more
         *  than dupAddrDetectTransmits, then permantly assign target link local
         *  address as permanent address for given interface entry.
         */
        virtual void processDADTimeout(omnetpp::cMessage *msg);

        /************Address Autoconfiguration Stuff***************************/
        /**
         *  as it is not possbile to explicitly define RFC 2462. ND is the next
         *  best place to do this.
         *
         *  RFC 2462-IPv6 Stateless Address Autoconfiguration: Section 1
         *  The autoconfiguration process specified in this document applies only
         *  to hosts and not routers. Since host autoconfiguration uses
         *  information advertised by routers, routers will need to be configured
         *  by some other means. However, it is expected that routers will
         *  generate link-local addresses using the mechanism described in this
         *  document. In addition, routers are expected to successfully pass the
         *  Duplicate Address Detection procedure described in this document on
         *  all addresses prior to assigning them to an interface.
         */
        virtual void assignLinkLocalAddress(omnetpp::cMessage *timerMsg);

        /************End Of Address Autoconfiguration Stuff********************/

        /************Router Solicitation Stuff*********************************/
        virtual inet::IPv6RouterSolicitation *createAndSendRSPacket(InterfaceEntry *ie);
        virtual void initiateRouterDiscovery(omnetpp::cMessage *msg);
        /**
         *  RFC 2461: Section 6.3.7 4th paragraph
         *  Once the host sends a Router Solicitation, and receives a valid
         *  Router Advertisement with a non-zero Router Lifetime, the host MUST
         *  desist from sending additional solicitations on that interface,
         *
         *  Cancel Router Discovery on the Interface where a RA was received with
         *  the given Interface Entry.
         */
        virtual void cancelRouterDiscovery(InterfaceEntry *ie);
        virtual void processRDTimeout(omnetpp::cMessage *msg);
        virtual void processRSPacket(inet::IPv6RouterSolicitation *rs, IPv6ControlInfo *rsCtrlInfo);
        virtual bool validateRSPacket(inet::IPv6RouterSolicitation *rs, IPv6ControlInfo *rsCtrlInfo);
        /************End of Router Solicitation Stuff**************************/

        /************Router Advertisment Stuff*********************************/
        virtual inet::IPv6RouterAdvertisement *createAndSendRAPacket(const IPv6Address& destAddr,
            InterfaceEntry *ie);
        virtual void processRAPacket(inet::IPv6RouterAdvertisement *ra, IPv6ControlInfo *raCtrlInfo);
        virtual void processRAForRouterUpdates(inet::IPv6RouterAdvertisement *ra,
            IPv6ControlInfo *raCtrlInfo);
        //RFC 2461: Section 6.3.4
        /*Note: Implementations can choose to process the on-link aspects of the
        prefixes separately from the address autoconfiguration aspects of the
        prefixes by, e.g., passing a copy of each valid Router Advertisement message
        to both an "on-link" and an "addrconf" function. Each function can then
        operate independently on the prefixes that have the appropriate flag set.*/
        virtual void processRAPrefixInfo(inet::IPv6RouterAdvertisement *ra, InterfaceEntry *ie);
        virtual void processRAPrefixInfoForAddrAutoConf(inet::IPv6NDPrefixInformation& prefixInfo,
            InterfaceEntry *ie,  bool hFlag = false); // overloaded method - 3.9.07 CB
	/**
	* An overloaded funciton whihc is called only if the node is a MN. Because the adress auto-configured
	* in the MN has to be tagged as either being a HoA or a CoA by taking into account the status of the
	* H-FLag in the RA.
	**/
	//void processRAPrefixInfoForAddrAutoConf(IPv6NDPrefixInformation& prefixInfo, InterfaceEntry *ie, bool hFlag); //overloaded function zarrar 20.07.07, removed 3.9.07 CB
        /**
         *  Create a timer for the given interface entry that sends periodic
         *  Router Advertisements
         */
        virtual void createRATimer(InterfaceEntry *ie);
        /**
         *  Reset the given interface entry's Router Advertisement timer. This is
         *  usually done when a router interface responds (by replying with a Router
         *  Advertisement sent to the All-Node multicast group)to a router solicitation
         *  Also see: RFC 2461, Section 6.2.6
         */
        virtual void resetRATimer(InterfaceEntry *ie);
        virtual void sendPeriodicRA(omnetpp::cMessage *msg);
        virtual void sendSolicitedRA(omnetpp::cMessage *msg);
        virtual bool validateRAPacket(inet::IPv6RouterAdvertisement *ra, IPv6ControlInfo *raCtrlInfo);
        /************End of Router Advertisement Stuff*************************/

        /************Neighbour Solicitaton Stuff*******************************/
        virtual inet::IPv6NeighbourSolicitation *createAndSendNSPacket(
            const IPv6Address& nsTargetAddr, const IPv6Address& dgDestAddr,
            const IPv6Address& dgSrcAddr, InterfaceEntry *ie);
        virtual void processNSPacket(inet::IPv6NeighbourSolicitation *ns, IPv6ControlInfo *naCtrlInfo);
        virtual bool validateNSPacket(inet::IPv6NeighbourSolicitation *ns, IPv6ControlInfo *nsCtrlInfo);
        virtual void processNSForTentativeAddress(inet::IPv6NeighbourSolicitation *ns,
            IPv6ControlInfo *ctrlInfo);
        virtual void processNSForNonTentativeAddress(inet::IPv6NeighbourSolicitation *ns,
            IPv6ControlInfo *ctrlInfo, InterfaceEntry *ie);
        virtual void processNSWithSpecifiedSrcAddr(inet::IPv6NeighbourSolicitation *ns,
            IPv6ControlInfo *ctrlInfo, InterfaceEntry *ie);
        /************End Of Neighbour Solicitation Stuff***********************/

        /************Neighbour Advertisment Stuff)*****************************/
        inet::IPv6NeighbourAdvertisement *createAndSendNAPacket(inet::IPv6NeighbourSolicitation *ns,
            const IPv6Address& nsSrcAddr, const IPv6Address& nsDestAddr, InterfaceEntry *ie);
        virtual void sendSolicitedNA(inet::IPv6NeighbourSolicitation *ns,
            IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie);
public: // update 12.9.07 - CB
        virtual void sendUnsolicitedNA(InterfaceEntry *ie);
protected: // update 12.9.07 - CB
        virtual void processNAPacket(inet::IPv6NeighbourAdvertisement *na, IPv6ControlInfo *naCtrlInfo);
        virtual bool validateNAPacket(inet::IPv6NeighbourAdvertisement *na, IPv6ControlInfo *naCtrlInfo);
        virtual void processNAForIncompleteNCEState(inet::IPv6NeighbourAdvertisement *na,
            IPv6NeighbourCache::Neighbour *nce);
        virtual void processNAForOtherNCEStates(inet::IPv6NeighbourAdvertisement *na,
            IPv6NeighbourCache::Neighbour *nce);
        /************End Of Neighbour Advertisement Stuff**********************/

        /************Redirect Message Stuff************************************/
        virtual inet::IPv6Redirect *createAndSendRedirectPacket(InterfaceEntry *ie);
        virtual void processRedirectPacket(inet::IPv6Redirect *redirect, IPv6ControlInfo *ctrlInfo);
        /************End Of Redirect Message Stuff*****************************/

		/* To determine whether a Router's Ethernet Interface is connected to
		 * a WLAN AP or not (Zarrar Yousaf (23.09.07)
		 *
		 * Moved here from InterfaceEntry.h by BT.
		 */
		virtual bool isConnectedToWirelessAP(InterfaceEntry *ie);

        /**
         *  RFC2463 Section 3.1: Destination Unreachable Message
         *  Send an unreachable message to the IPv6 module.
         *  TODO: Relocate to ICMPv6 module
         */

        /*ICMPv6DestUnreachableMsg *createAndSendUnreachableMessage(const IPv6Address& destAddress, InterfaceEntry *ie);*/

	//double getMinRAInterval() const {return minRAInterval;} //zarrar yousaf 15.07.07
	//double getMaxRAInterval() const {return maxRAInterval;} //zarrar yousaf 15.07.07
	public:
		void invalidateNeigbourCache();

	protected:
		void routersUnreachabilityDetection(const InterfaceEntry* ie); // 3.9.07 - CB
//============= Adam 09-09-2011 =====================
        void setAP_InfoAndCreateMsg(int BSindex ,MACAddress Macaddr ,IPv6Address IPv6Addr ,IPv6Address prefix, int prefixLength);
        void CreateAndSendAssignAddressNotify();

        inet::cMessage* TimeoutAssignAddressNotify;  // timer aby powiadomic inne ARy o swoim global adresie WiMAX, czekam aby kazdy AR mial swoj adres globalny na eth
//============= Adam, end  09-09-2011==================

};
#endif //IPV6NEIGHBOURDISCOVERY_H
