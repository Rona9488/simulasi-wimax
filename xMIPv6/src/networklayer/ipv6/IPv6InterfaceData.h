#ifndef __IPv6INTERFACEDATA_H
#define __IPv6INTERFACEDATA_H


#include <vector>
#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6Address.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceEntry.h"
/**
* Including the RouitngTable6Access.h and RoutingTable6.h as node information, whether it is a MN, HA,
* router or CN, is needed in the Ipv6InterfaceData::info(). The interface information displayed for the MN is
* different, as the address gets tagged to be either of type HoA or CoA, from HA, router and CN, where info
* regarding type of address is not required (Zarrar Yousaf 20.07.07)
**/
#include "RoutingTable6Access.h" //Zarrar Yousaf 20.07.07
#include "RoutingTable6.h"	//Zarrar Yousaf 20.07.07
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\IPv6NeighbourDiscovery.h" // CB 4.9.07

#define IPv6_DEFAULT_DUPADDRDETECTTRANSMITS 1   // send NS once (RFC2462:Section 5.1)

#define IPv6_MIN_MTU                        1280// octets
#define IPv6_DEFAULT_ADVCURHOPLIMIT         30

#define IPv6_DEFAULT_MAX_RTR_ADV_INT        600 //seconds-decrease to enable more periodic RAs
#define IPv6_DEFAULT_ADV_REACHABLE_TIME     3600// seconds
#define IPv6_DEFAULT_ADV_RETRANS_TIMER      1   // seconds
#define IPv6__INET_DEFAULT_ROUTER_HOPLIMIT        64

/**************RFC 2461: Section 10 Protocol Constants*************************/
//Router Constants
#define IPv6_MAX_INITIAL_RTR_ADVERT_INTERVAL 16  // seconds
#define IPv6_MAX_INITIAL_RTR_ADVERTISEMENTS   3  // transmissions
#define IPv6_MAX_FINAL_RTR_ADVERTISEMENTS     3  // transmissions
#define IPv6_MIN_DELAY_BETWEEN_RAS            3  // seconds
#define IPv6_MAX_RA_DELAY_TIME               .5  // seconds

//Host Constants
#define IPv6_MAX_RTR_SOLICITATION_DELAY       1  // seconds
#define IPv6_RTR_SOLICITATION_INTERVAL        4  // seconds
#define IPv6_MAX_RTR_SOLICITATIONS            3  // transmissions

//Node Constants
#define IPv6_MAX_MULTICAST_SOLICIT            3  // transmissions
#define IPv6_MAX_UNICAST_SOLICIT              3  // transmissions
#define IPv6_MAX_ANYCAST_DELAY_TIME           1  // seconds
#define IPv6_MAX_NEIGHBOUR_ADVERTISEMENT      3  // transmissions
#define IPv6_REACHABLE_TIME                  30  // seconds
#define IPv6_RETRANS_TIMER                    1  // seconds
#define IPv6_DELAY_FIRST_PROBE_TIME           5  // seconds
#define IPv6_MIN_RANDOM_FACTOR              0.5
#define IPv6_MAX_RANDOM_FACTOR              1.5
/***************END of RFC 2461 Protocol Constants*****************************/
/***************RFC 3775: Section 12 Protocol Constants************************/
#define MIPv6_DHAAD_RETRIES			4 // retransmissions
#define MIPv6_INITIAL_BINDACK_TIMEOUT		1 // second
#define MIPv6_INITIAL_DHAAD_TIMEOUT		3 // seconds
#define MIPv6_INITIAL_SOLICIT_TIMER		3 // seconds
#define MIPv6_MAX_BINDACK_TIMEOUT 	       32 // seconds
#define MIPv6_MAX_NONCE_LIFETIME              240 // seconds
#define MIPv6_MAX_TOKEN_LIFETIME              210 // 210 // seconds
#define MIPv6_MAX_UPDATE_RATE                   3 // times
#define MIPv6_PREFIX_ADV_RETRIES                3 // retransmissions
#define MIPv6_PREFIX_ADV_TIMEOUT                3 // seconds
// update 12.9.07 - CB
#define MIPv6_INITIAL_BINDACK_TIMEOUT_FIRST		1 // seconds
#define MIPv6_MAX_RR_BINDING_LIFETIME			420 // 420 // seconds
#define MIPv6_MAX_HA_BINDING_LIFETIME			60 * 60 // 1 hour
/***************END of RFC 3775 Protocol Constants*****************************/



/**
 * IPv6-specific data for InterfaceEntry. Most of this comes from
 * section 6.2.1 of RFC 2461 (IPv6 Neighbor Discovery, Router Configuration
 * Variables).
 */
class INET_API IPv6InterfaceData : public InterfaceProtocolData
{
  public:
    /**
     * For routers: advertised prefix configuration.
     *
     * advValidLifetime, advPreferredLifetime:
     *     - >0 value means absolute expiry time
     *     - <0 means lifetime (delta)
     *     - 0 means infinite lifetime
     */
    struct AdvPrefix
    {
        short prefixLength;
        bool advOnLinkFlag; 	//L-flag
        bool advAutonomousFlag; //A-flag
        bool advRtrAddr; 	//R-flag (Zarrar Yousaf 09.07.07)
        inet::simtime_t advValidLifetime; // see comment above
        inet::simtime_t advPreferredLifetime; // see comment above
        IPv6Address prefix;	//default in RA's
        IPv6Address rtrAddress; //global scope, present when advRtrAddr is true (Zarrar Yousaf 09.07.07)
    };

    /*************RFC 2461: Section 10 Protocol Constants**********************/
    struct RouterConstants
    {
        inet::simtime_t maxInitialRtrAdvertInterval;
        uint maxInitialRtrAdvertisements;
        uint maxFinalRtrAdvertisements;
        inet::simtime_t minDelayBetweenRAs;
        inet::simtime_t maxRADelayTime;
    };
    RouterConstants routerConstants;

    struct HostConstants
    {
        inet::simtime_t maxRtrSolicitationDelay;
        inet::simtime_t rtrSolicitationInterval;
        int maxRtrSolicitations;
	    uint initialBindAckTimeout;//MIPv6: added by Zarrar Yousaf @ CNI UniDo 17.06.07
	    uint maxBindAckTimeout;//MIPv6: added by Zarrar Yousaf @ CNI UniDo 17.06.07
	    float initialBindAckTimeoutFirst; //MIPv6: 12.9.07 - CB // TODO: datatype float or double
	    uint maxRRBindingLifeTime; // 14.9.07 - CB
	    uint maxHABindingLifeTime; // 14.9.07 - CB
	    uint maxTokenLifeTime; // 10.07.08 - CB
    };
    HostConstants hostConstants;

    struct NodeConstants
    {
        uint maxMulticastSolicit;
        uint maxUnicastSolicit;
        inet::simtime_t maxAnycastDelayTime;
        uint maxNeighbourAdvertisement;
        inet::simtime_t reachableTime;
        inet::simtime_t retransTimer;
        inet::simtime_t delayFirstProbeTime;
        double minRandomFactor;
        double maxRandomFactor;
    };
    NodeConstants nodeConstants;
    /***************END of RFC 2461 Protocol Constants*************************/

/**
* The enum AddressType defined below and the new member of the struct AddressData {AddressType addrType} is
* relevant for MN(s) only as the address(es) configured on the MN interface needs to be tagged as either HoA
* or CoA, based upon the status of the H-Flag recieved in the RA. This is
**/
    enum AddressType {HoA, CoA}; // to tag a MN's address as Home-Address or Care-of-Address. Zarrar Yousaf 20.07.07
  private:
    /**
	 * Zarrar 03.09.07: Home Network Information maintains home network information like the MN's home address
	 * (HoA) and the HA's address and its prefix. The information from this list will be used by the MN in
	 * sending BU towards HA for home registration while in visit network. This data will be updated as soon as
	 * the MN processes the prefix information recieved in the RA from the HA and when it auto-configures its
	 * global scope address. This home network info is defined in the IPv6InterfaceData in order to support MN(s)
	 * with multiple interfaces, where there could be a possibility that multiple interfaces in a single MN may
	 * belong to different home networks. Therefore it is necessary to maintain home network info on a per
	 * interface basis
	 */
	struct HomeNetworkInfo
	{
		IPv6Address HoA; // Home Address of the MN, configured while in the home network
		IPv6Address homeAgentAddr;
		//IPv6NDPrefixInformation prefix;
		IPv6Address prefix;
	};
	friend std::ostream& operator<<(std::ostream& os, const HomeNetworkInfo& homeNetInfo);
	HomeNetworkInfo homeInfo;

	bool dadInProgress;
  public:
	bool isDADInProgress() {return dadInProgress;};
	void setDADInProgress(bool val) {dadInProgress = val;};

  private:
    // addresses
    struct AddressData
    {
        IPv6Address address;  // address itself
        bool tentative;       // true if currently undergoing Duplicate Address Detection
        inet::simtime_t expiryTime; // end of valid lifetime; 0 means infinity
        inet::simtime_t prefExpiryTime; // end of preferred lifetime; 0 means infinity
        AddressType addrType; //HoA or CoA: Zarrar 20.07.07
    };
    typedef std::vector<AddressData> AddressDataVector;
    // TBD should be std::map, so that isLocalAddress() is faster?

    AddressDataVector addresses;   // interface addresses
    IPv6Address preferredAddr; // cached result of preferred address selection
    inet::simtime_t preferredAddrExpiryTime;

    /***************RFC 2462: Section 5.1 Node Configuration Variables*********/
    struct NodeVariables
    {
        /**
         *  The number of consecutive Neighbor Solicitation messages sent while
         *  performing Duplicate Address Detection on a tentative address. A
         *  value of zero indicates that Duplicate Address Detection is not performed
         *  on tentative addresses. A value of one indicates a single transmission
         *  with no follow up retransmissions.
         *
         *  Default: 1, but may be overridden by a link-type specific value in
         *  the document that covers issues related to the transmission of IP
         *  over a particular link type (e.g., [IPv6-ETHER]).
         *
         *  Autoconfiguration also assumes the presence of the variable RetransTimer
         *  as defined in [DISCOVERY]. For autoconfiguration purposes, RetransTimer
         *  specifies the delay between consecutive Neighbor Solicitation transmissions
         *  performed during Duplicate Address Detection (if DupAddrDetectTransmits
         *  is greater than 1), as well as the time a node waits after sending
         *  the last Neighbor Solicitation before ending the Duplicate Address
         *  Detection process.
         */
        int dupAddrDetectTransmits;
    };
    NodeVariables nodeVars;
    /***************END of RFC 2461 Node Configuration Variables***************/

    /***************RFC 2461: Section 6.3.2 Host Variables*********************/
    struct HostVariables
    {
        /**
         *  The MTU of the link.
         *  Default: The valued defined in the specific document that describes
         *           how IPv6 operates over the particular link layer (e.g., [IPv6-ETHER]).
         */
        uint linkMTU;
        /**
         *  The default hop limit to be used when sending (unicast) IP packets.
         *  Default: The value specified in the "Assigned Numbers" RFC [ASSIGNED]
         *           that was in effect at the time of implementation.
         */
        short curHopLimit;
        /**
         *  A base value used for computing the random ReachableTime value.
         *  Default: REACHABLE_TIME milliseconds. > protocol constants
         */
        uint baseReachableTime;
        /**
         *  The time a neighbor is considered reachable after receiving a
         *  reachability confirmation.
         *  reachableTime =
         *      uniform(MIN_RANDOM_FACTOR, MAX_RANDOM_FACTOR) * baseReachableTime
         *  New value should be calculated when baseReachableTime changes or at
         *  least every few hours even if no Router Advertisements are received.
         */
        inet::simtime_t reachableTime;
        /**
         *  The time between retransmissions of Neighbor Solicitation messages
         *  to a neighbor when resolving the address or when probing the
         *  reachability of a neighbor.
         *  Default: RETRANS_TIMER milliseconds
         */
        uint retransTimer;
    };
    HostVariables hostVars;
    /***************END of RFC 2461 Host Variables*****************************/

    /***************RFC 2461: Section 6.2.1 Router Configuration Variables*****/
    typedef std::vector<AdvPrefix> AdvPrefixList;
    struct RouterVariables
    {
        /**
         *  A flag indicating whether or not the router sends periodic Router
         *  Advertisements and responds to Router Solicitations.
         *
         *  Default: FALSE
         */
        bool advSendAdvertisements;
        /**
         *  The maximum time allowed between sending unsolicited multicast
         *  Router Advertisements from the interface, in seconds.  MUST be no
         *  less than 4 seconds and no greater than 1800 seconds.
         *
         *  Default: 600 seconds
         */
        inet::simtime_t maxRtrAdvInterval;
        /**
         *  The minimum time allowed between sending unsolicited multicast Router
         *  Advertisements from the interface, in seconds.  MUST be no less than
         *  3 seconds and no greater than .75 * maxRtrAdvInterval
         *
         *  Default: 0.33 * MaxRtrAdvInterval
         */
        inet::simtime_t minRtrAdvInterval;
        /**
         *  The TRUE/FALSE value to be placed in the "Managed address configuration"
         *  flag field in the Router Advertisement.  See [ADDRCONF].
         *
         *  Default: FALSE
         */
        bool advManagedFlag;
        /**
         *  The TRUE/FALSE value to be placed in the "Other stateful configuration"
         *  flag field in the Router Advertisement.  See [ADDRCONF].
         *
         *  Default: FALSE
         */
        bool advOtherConfigFlag;// also false as not disseminating other config info from routers

	/**
         *  The TRUE/FALSE value to be placed in the "Home Agent"
         *  flag field in the Router Advertisement.  See [ADDRCONF].
         *
         *  Default: FALSE
         */
        bool advHomeAgentFlag;// also false as not disseminating other config info from routers


        /**
         *  The value to be placed in MTU options sent by the router. A value of
         *  zero indicates that no MTU options are sent.
         *
         *  Default: 0
         */
        int advLinkMTU;
        /**
         *  The value to be placed in the Reachable Time field in the Router
         *  Advertisement messages sent by the router.  The value zero means
         *  unspecified (by this router).  MUST be no greater than 3,600,000
         *  milliseconds (1 hour).
         *
         *  Default: 0
         */
        int advReachableTime; // host BaseReachableTime?
        /**
         *  The value to be placed in the Retrans Timer field in the Router
         *  Advertisement messages sent by the router.  The value zero means
         *  unspecified (by this router).
         *
         *  Default: 0
         */
        int advRetransTimer; // host RetransTimer?
        /**
         *  The default value to be placed in the Cur Hop Limit field in the
         *  Router Advertisement messages sent by the router. The value should be
         *  set to that current diameter of the Internet.  The value zero means
         *  unspecified (by this router).
         *
         *  Default:  The value specified in the "Assigned Numbers" RFC [ASSIGNED]
         *  that was in effect at the time of implementation.
         */
        short advCurHopLimit; // host CurHopLimit
        /**
         *  The value to be placed in the Router Lifetime field of Router
         *  Advertisements sent from the interface, in seconds.  MUST be either
         *  zero or between MaxRtrAdvInterval and 9000 seconds.  A value of zero
         *  indicates that the router is not to be used as a default router.
         *
         *  Default: 3 * MaxRtrAdvInterval
         */
        inet::simtime_t advDefaultLifetime; // integer seconds in ND rfc but for MIPv6 really need better granularity
        //bool fastRA;
        //uint maxFastRAS;
        //mutable uint fastRACounter;

        // These are either learned from routers or configured manually(router)
        AdvPrefixList advPrefixList;
    };
    RouterVariables rtrVars;
    /***************END of RFC 2461 Host Variables*****************************/

  protected:
    int findAddress(const IPv6Address& addr) const;
    void choosePreferredAddress();
    void changed1() {changed(NF_INTERFACE_IPv6CONFIG_CHANGED);}

    static bool addrLess(const AddressData& a, const AddressData& b);

  public:
    IPv6InterfaceData();
    virtual ~IPv6InterfaceData() {}
    std::string info() const;
    std::string detailedInfo() const;

    /** @name Addresses */
    //@{
    /**
     * Assigns the given address to the interface.
     */
    // Removed as replaced by overloaded version, 3.9.07 - CB
    /*virtual void assignAddress(const IPv6Address& addr, bool tentative,
                               simtime_t expiryTime, simtime_t prefExpiryTime);
     */
    /**
     * Update expiry times of addresses. Expiry times possibly come from
     * prefixes (with on-link flag set to either zero or one)
     * in Router Advertisements. Zero expiry time means infinity.
     */
    virtual void updateMatchingAddressExpiryTimes(const IPv6Address& prefix, int length,
            inet::simtime_t expiryTime=0, inet::simtime_t prefExpiryTime=0);

    /**
     * Returns the number of addresses the interface has.
     */
    int getNumAddresses() const {return addresses.size();}

    /**
     * Returns ith address of the interface.
     */
    const IPv6Address& getAddress(int i) const;

    /**
     * Returns true if the ith address of the interface is tentative.
     */
    bool isTentativeAddress(int i) const;

    /**
      * Returns the address type (HoA, CoA) of the ith address of the interface.
      * 4.9.07 - CB
      */
    AddressType getAddressType(int i) const;

    /**
      * Returns the address type (HoA, CoA) of the provided address of the interface.
      * 27.9.07 - CB
      */
    AddressType getAddressType(const IPv6Address& addr) const;



// FIXME address validity check missing. introduce hasValidAddress(addr, now) which would compare lifetimes too?

    /**
     * Returns true if the given address is one of the addresses assigned,
     * regardless whether it is tentative or not.
     */
    bool hasAddress(const IPv6Address& addr) const;

    /**
     * Returns true if the interface has an address matching the given
     * solicited-node multicast addresses.
     */
    bool matchesSolicitedNodeMulticastAddress(const IPv6Address& solNodeAddr) const;

    /**
     * Returns true if the interface has the given address and it is tentative.
     */
    bool isTentativeAddress(const IPv6Address& addr) const;

    /**
     * Clears the "tentative" flag of an existing interface address.
     */
    void permanentlyAssign(const IPv6Address& addr);

    /**
     * Sets the "tentative" flag of of the ith address of the interface.
     * 28.09.07 - CB
     */
    void tentativelyAssign(int i);


    /**
     * Chooses a preferred address for the interface and returns it.
     * This is the address that should be used as source address for outgoing
     * datagrams, if one is not explicitly specified.
     *
     * Selection is based on scope (globally routable addresses are preferred),
     * then on lifetime (the one that expires last is chosen). See private
     * choosePreferredAddress() function.
     *
     * FIXME turn into preferredGLOBALAddress()!
     */
    const IPv6Address& getPreferredAddress() const {return preferredAddr;}  // FIXME TBD check expiry time!

    /**
     * Returns the first valid link-local address of the interface,
     * or UNSPECIFIED_ADDRESS if there's none.
     */
    const IPv6Address& getLinkLocalAddress() const;

    /**
     * Removes the address. Called when the valid lifetime expires.
     */
    virtual void removeAddress(const IPv6Address& address);

    /**
     *  Getters/Setters for all variables and constants defined in RFC 2461/2462
     *  can be found here. Operations responsible for protocol constants are marked
     *  with a "_" prefix. Constants in this class are stored as instance variables.
     *  Default values for certain variables are defined at the top of this file,
     *  while certain variables have to be generated. Protocol constants are subject
     *  to change as specified in RFC2461:section 10 depending on different link
     *  layer operation. Getters and setters have been implemented for protocol
     *  constants so that a wireless interface may be set to a different set of
     *  constant values. (ie. changed by the FlatNetworkConfigurator) Such a design
     *  allows both wired and wireless networks to co-exist within a simulation run.
     */
    /************Getters for Router Protocol Constants*************************/
    inet::simtime_t _getMaxInitialRtrAdvertInterval() {return routerConstants.maxInitialRtrAdvertInterval;}
    uint _getMaxInitialRtrAdvertisements() {return routerConstants.maxInitialRtrAdvertisements;}
    uint _getMaxFinalRtrAdvertisements() {return routerConstants.maxFinalRtrAdvertisements;}
    inet::simtime_t _getMinDelayBetweenRAs() {return routerConstants.minDelayBetweenRAs;}
    inet::simtime_t _getMaxRADelayTime() {return routerConstants.maxRADelayTime;}
    /************Setters for Router Protocol Constants*************************/
    virtual void _setMaxInitialRtrAdvertInterval(inet::simtime_t d) {routerConstants.maxInitialRtrAdvertInterval = d;}
    virtual void _setMaxInitialRtrAdvertisements(uint d) {routerConstants.maxInitialRtrAdvertisements = d;}
    virtual void _setMaxFinalRtrAdvertisements(uint d) {routerConstants.maxFinalRtrAdvertisements = d;}
    virtual void _setMinDelayBetweenRAs(inet::simtime_t d) {routerConstants.minDelayBetweenRAs = d;}
    virtual void _setMaxRADelayTime(inet::simtime_t d) {routerConstants.maxRADelayTime = d;}
    /************End of Router Protocol Constant getters and setters***********/

    /************Getters for Host Protocol Constants***************************/
    inet::simtime_t _getMaxRtrSolicitationDelay() {return hostConstants.maxRtrSolicitationDelay;}
    inet::simtime_t _getRtrSolicitationInterval() {return hostConstants.rtrSolicitationInterval;}
    uint _getMaxRtrSolicitations() {return hostConstants.maxRtrSolicitations;}
    inet::simtime_t _initialBindAckTimeout(){return hostConstants.initialBindAckTimeout;}//MIPv6: added by Zarrar Yousaf @ CNI UniDo 17.06.07
    inet::simtime_t _maxBindAckTimeout(){return hostConstants.maxBindAckTimeout;}//MIPv6: added by Zarrar Yousaf @ CNI UniDo 17.06.07
    inet::simtime_t _initialBindAckTimeoutFirst(){return hostConstants.initialBindAckTimeoutFirst;} //MIPv6, 12.9.07 - CB
    uint _maxRRBindingLifeTime(){return hostConstants.maxRRBindingLifeTime;} //MIPv6, 14.9.07 - CB
    uint _maxHABindingLifeTime(){return hostConstants.maxHABindingLifeTime;} //MIPv6, 14.9.07 - CB
    uint _maxTokenLifeTime(){return hostConstants.maxTokenLifeTime;} //MIPv6, 10.07.08 - CB

    /************Setters for Host Protocol Constants***************************/
    virtual void _setMaxRtrSolicitationDelay(inet::simtime_t d) {hostConstants.maxRtrSolicitationDelay = d;}
    virtual void _setRtrSolicitationInterval(inet::simtime_t d) {hostConstants.rtrSolicitationInterval = d;}
    virtual void _setMaxRtrSolicitations(uint d) {hostConstants.maxRtrSolicitations = d;}
    /************End of Host Protocol Constant getters and setters*************/

    /************Getters for Node Protocol Constants***************************/
    uint _getMaxMulticastSolicit() {return nodeConstants.maxMulticastSolicit;}
    uint _getMaxUnicastSolicit() {return nodeConstants.maxUnicastSolicit;}
    inet::simtime_t _getMaxAnycastDelayTime() {return nodeConstants.maxAnycastDelayTime;}
    uint _getMaxNeighbourAdvertisement() {return nodeConstants.maxNeighbourAdvertisement;}
    inet::simtime_t _getReachableTime() {return nodeConstants.reachableTime;}
    inet::simtime_t _getRetransTimer() {return nodeConstants.retransTimer;}
    inet::simtime_t _getDelayFirstProbeTime() {return nodeConstants.delayFirstProbeTime;}
    double _getMinRandomFactor() {return nodeConstants.minRandomFactor;}
    double _getMaxRandomFactor() {return nodeConstants.maxRandomFactor;}
    /************Setters for Node Protocol Constants***************************/
    virtual void _setMaxMulticastSolicit(uint d) {nodeConstants.maxMulticastSolicit = d;}
    virtual void _setMaxUnicastSolicit(uint d) {nodeConstants.maxUnicastSolicit = d;}
    virtual void _setMaxAnycastDelayTime(inet::simtime_t d) {nodeConstants.maxAnycastDelayTime = d;}
    virtual void _setMaxNeighbourAdvertisement(uint d) {nodeConstants.maxNeighbourAdvertisement = d;}
    virtual void _setReachableTime(inet::simtime_t d) {nodeConstants.reachableTime = d;}
    virtual void _setRetransTimer(inet::simtime_t d) {nodeConstants.retransTimer = d;}
    virtual void _setDelayFirstProbeTime(inet::simtime_t d) {nodeConstants.delayFirstProbeTime = d;}
    virtual void _setMinRandomFactor(double d) {nodeConstants.minRandomFactor = d;}
    virtual void _setMaxRandomFactor(double d) {nodeConstants.maxRandomFactor = d;}
    /************End of Node Protocol Constant getters and setters*************/

    /************Getters for Node Variables************************************/
    int dupAddrDetectTransmits() {return nodeVars.dupAddrDetectTransmits;}
    /************Setters for Node Variables************************************/
    virtual void setDupAddrDetectTransmits(int d) {nodeVars.dupAddrDetectTransmits = d;}
    /************End of Node Variables getters and setters*********************/

    /************Getters for Host Variables************************************/
    uint getLinkMTU() {return hostVars.linkMTU;}
    short getCurHopLimit() {return hostVars.curHopLimit;}
    uint getBaseReachableTime() {return hostVars.baseReachableTime;}
    inet::simtime_t getReachableTime() {return hostVars.reachableTime;}
    uint getRetransTimer() {return hostVars.retransTimer;}
    /************Setters for Host Variables************************************/
    virtual void setLinkMTU(uint d) {hostVars.linkMTU = d;}
    virtual void setCurHopLimit(short d) {hostVars.curHopLimit = d;}
    virtual void setBaseReachableTime(uint d) {hostVars.baseReachableTime = d;}
    virtual void setReachableTime(inet::simtime_t d) {hostVars.reachableTime = d;}
    virtual void setRetransTimer(uint d) {hostVars.retransTimer = d;}
    /************End of Host Variables getters and setters*********************/

    /************Getters for Router Configuration Variables********************/
    bool getAdvSendAdvertisements() {return rtrVars.advSendAdvertisements;}
    inet::simtime_t getMaxRtrAdvInterval() {return rtrVars.maxRtrAdvInterval;}
    inet::simtime_t getMinRtrAdvInterval() {return rtrVars.minRtrAdvInterval;}
    bool getAdvManagedFlag() {return rtrVars.advManagedFlag;}
    bool getAdvOtherConfigFlag() {return rtrVars.advOtherConfigFlag;}
    bool getAdvHomeAgentFlag() {return rtrVars.advHomeAgentFlag;}
    int getAdvLinkMTU() {return rtrVars.advLinkMTU;}
    int getAdvReachableTime() {return rtrVars.advReachableTime;}
    int getAdvRetransTimer() {return rtrVars.advRetransTimer;}
    short getAdvCurHopLimit() {return rtrVars.advCurHopLimit;}
    inet::simtime_t getAdvDefaultLifetime()  {return rtrVars.advDefaultLifetime;}
    /************Setters for Router Configuration Variables********************/
    virtual void setAdvSendAdvertisements(bool d) {rtrVars.advSendAdvertisements = d;}
    virtual void setMaxRtrAdvInterval(inet::simtime_t d) {rtrVars.maxRtrAdvInterval = d;}
    virtual void setMinRtrAdvInterval(inet::simtime_t d) {rtrVars.minRtrAdvInterval = d;}
    virtual void setAdvManagedFlag(bool d) {rtrVars.advManagedFlag = d;}
    virtual void setAdvOtherConfigFlag(bool d) {rtrVars.advOtherConfigFlag = d;}
    virtual void setAdvHomeAgentFlag(bool d) {rtrVars.advHomeAgentFlag = d;}
    virtual void setAdvLinkMTU(int d) {rtrVars.advLinkMTU = d;}
    virtual void setAdvReachableTime(int d) {rtrVars.advReachableTime = d;}
    virtual void setAdvRetransTimer(int d) {rtrVars.advRetransTimer = d;}
    virtual void setAdvCurHopLimit(short d) {rtrVars.advCurHopLimit = d;}
    virtual void setAdvDefaultLifetime(inet::simtime_t d) {rtrVars.advDefaultLifetime = d;}
    /************End of Router Configuration Variables getters and setters*****/

    /** @name Router advertised prefixes */
    //@{
    /**
     * Adds the given advertised prefix to the interface.
     */
    virtual void addAdvPrefix(const AdvPrefix& advPrefix);

    /**
     * Returns the number of advertised prefixes on the interface.
     */
    int getNumAdvPrefixes() const {return rtrVars.advPrefixList.size();}

    /**
     * Returns the ith advertised prefix on the interface.
     */
    const AdvPrefix& getAdvPrefix(int i) const;

    /**
     * Changes the configuration of the ith advertised prefix on the
     * interface. The prefix itself should stay the same.
     */
    virtual void setAdvPrefix(int i, const AdvPrefix& advPrefix);

    /**
     * Remove the ith advertised prefix on the interface. Prefixes
     * at larger indices will shift down.
     */
    virtual void removeAdvPrefix(int i);

    /**
     *  This method randomly generates a reachableTime given the MIN_RANDOM_FACTOR
     *  MAX_RANDOM_FACTOR and baseReachableTime. Refer to RFC 2461: Section 6.3.2
     */
    virtual inet::simtime_t generateReachableTime(double MIN_RANDOM_FACTOR, double MAX_RANDOM_FACTOR,
                                            uint baseReachableTime);

    /**
     * Arg-less version.
     */
    virtual inet::simtime_t generateReachableTime();

//############## Additional Function defined by Zarrar YOusaf @ CNI, Uni Dortmund  #########
     /**
     * Returns the first valid global address of the interface,
     * or UNSPECIFIED_ADDRESS if there's none.
     */
    const IPv6Address& getGlobalAddress(AddressType type = HoA) const; // 24.9.07 - CB
    /**
     * This function autoconfigures a global scope address for the router only,
     * if and only the prefix is provided via some exernal method, For instance
     * FlatNetworkConfigurator6 assigning prefixes to routers interfaces during
     *initialization.
     */
    const IPv6Address autoConfRouterGlobalScopeAddress(int i); // // removed return-by-reference - CB
    void autoConfRouterGlobalScopeAddress(AdvPrefix &p);

    void deduceAdvPrefix();

    /**
	 * Overloaded function, which also takes into account the status of the H-Flag in the recieved RA. Called from
	 * IPv6NeighbourDiscovery::processRAPrefixInfoForAddrAutoConf(IPv6NDPrefixInformation& prefixInfo, InterfaceEntry* ie, bool hFlag).
	 * relevant only when MIPv6 is supported. (Zarrar Yousaf 20.07.07)
	 **/
    void assignAddress(const IPv6Address& addr, bool tentative, inet::simtime_t expiryTime, inet::simtime_t prefExpiryTime, bool hFlag = false); //overloaded by Zarrar 20.07.07, update 3.9.07 - CB

	/**
	 * 03.09.07
	 * This updates the struct HomeNetwork Info with the MN's Home Address(HoA), the global
	 * scope address of the MNs Home Agent (HA) and the home network prefix.
	 */
	void updateHomeNetworkInfo(const IPv6Address& hoa, const IPv6Address& ha, const IPv6Address& prefix, const int prefixLength);

	const IPv6Address& getHomeAgentAddress() {return homeInfo.homeAgentAddr;} // Zarrar 03.09.07
	const IPv6Address& getMNHomeAddress() {return homeInfo.HoA;} // Zarrar 03.09.07
	const IPv6Address& getMNPrefix() {return homeInfo.prefix/*.prefix()*/;} // Zarrar 03.09.07

	/**
	 * Removes a CoA address from the interface if one exists.
	 */
	IPv6Address removeAddress(IPv6InterfaceData::AddressType type); // update 06.08.08 - CB

protected:
	RoutingTable6* rt6; // A pointer variable, specifically used to access the type of node (MN, HA, Router, CN). Used in info(). (Zarrar Yousaf 20.07.07)
  };

#endif

