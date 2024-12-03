/**
 * @file   wmaxmaccs.h
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-04-20 23:09:38+0100
 * 
 * @brief  WMax MAC convergence sublayer
 * @licence GNU GPLv2 or later
 * 
 */

#ifndef WMAXMACCS_H
#define WMAXMACCS_H

#include <omnetpp.h>
#include <string>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\util\Portable.h"
//#include "ipv6msg_m.h"	//Adam
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6Address.h"	//Adam
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\IPv6NeighbourDiscoveryAccess.h"	// Adam
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6Datagram_m.h"// Adam
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\RoutingTable6Access.h"// Adam
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\icmpv6\IPv6NeighbourCache.h"


using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/

typedef struct {
     uint16_t cid;
     //int gateIndex; 
     /// @todo IPv6 source and destination addr
     uint64_t macAddr;
     IPv6Address dstAddr;	//Adam
} WMaxMacCSRule;


/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/
uint64_t MacAddrFromLinkLocal(IPv6Address IN_addr);	    //============= Adam 14-09-2011 =====================

class WMaxMacCS : public inet::cSimpleModule {
public:
	IPv6NeighbourDiscovery* ipv6nd;	// Adam
protected:
    virtual void initialize();
    virtual void handleMessage(inet::cMessage *msg);
    virtual void handleUlMessage(inet::cMessage *msg);
    virtual void handleDlMessage(inet::cMessage *msg);
    virtual void updateLog();

    void dlMsgSend(inet::cMessage * msg, int cid);
    // IPv6Address DstAddrGet(cMessage *msg);	//Adam 
    list<WMaxMacCSRule> csTable;
    bool BS;
};

ostream & operator <<(ostream & s, WMaxMacCSRule &f);

#endif
