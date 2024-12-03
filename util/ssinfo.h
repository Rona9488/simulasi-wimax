/**
 * @file   ssinfo.h
 * @author Maciej Jureko <maciek01@gmail.com>
 * @date   2007-06-30 21:01:52+0200
 * 
 * @brief  SS parameters
 * @licence GNU GPLv2
 * 
 */

#ifndef SSINFO_H
#define SSINFO_H

#include <omnetpp.h>
#include <string>
#include "Portable.h"
#include "hoinfo.h"

using namespace std;

/**************************************************************/
/*** STRUCTURES ***********************************************/
/**************************************************************/
typedef struct SSInfo_s {
    uint64_t macAddr;
    uint16_t basicCid;

    string getMac();

    // used on BS-side only
    struct {
      uint16_t cid;
    } sf[32];
    uint16_t sfCnt;

} SSInfo_t;

/**************************************************************/
/*** UTIL FUNTIONS ********************************************/
/**************************************************************/
string MacToString(uint64_t mac);

/**************************************************************/
/*** MODULE DEFINITIONS STRUCTURES ****************************/
/**************************************************************/

class ssInfo : public omnetpp::cSimpleModule {
public:
    SSInfo_t info;
    HoInfo_t hoInfo;
    void stringUpdate();

    void addEventListener(  omnetpp::cModule * module);
    void delEventListener(  omnetpp::cModule * module);
    void sendEvent(omnetpp::cMessage * msg);

protected:
    virtual void initialize();

private:
    list<cModule*> EventListenersLst;
    string getMsgName(omnetpp::cMessage * msg);

    /* stats */
    void updateStats(omnetpp::cMessage * msg);
    omnetpp::simtime_t  hoPrep;
    omnetpp::simtime_t  hoReentry;
    omnetpp::simtime_t  hoReconf;
    omnetpp::simtime_t  hoLackOfComm;

    omnetpp::cOutVector hoPrepVector;    /* HO (preparation phase) time */
    omnetpp::cOutVector hoReentryVector; /* HO (reentry L2 phase) time */
    omnetpp::cOutVector hoReconfVector;  /* HO (L3 reconfiguration) time */
    omnetpp::cOutVector hoLackOfCommVector; /* HO (lack of communication caps) time */
};

ostream & operator<<(ostream & strum, SSInfo_t &ss);

#endif
