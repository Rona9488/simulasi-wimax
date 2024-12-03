/**
 * @file   wmaxphy.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   Sat Nov 18 18:42:04 2006
 * 
 * @brief  WMax PHY layer definitions
 * 
 * Published under GNU GPLv2 or later 
 */

#include <omnetpp.h>
#include "wmaxmsg_m.h"

/**
 * general abstract class representing WiMax PHY interface.
 * 
 */
class WMaxPhy : public inet::cSimpleModule
{
public:

protected:
    virtual void initialize() = 0;
    virtual void handleMessage(inet::cMessage *msg) = 0;
    inet::cQueue  SendQueue;
    // @todo ReceiveQueue (fragmentation, ARQ, HARQ)
    
    int FrameNum; // frame number
};

class WMaxPhyBS : public WMaxPhy
{
 public:
       
    WMaxPhyBS();
    ~WMaxPhyBS();
 protected:
    virtual void initialize();
    virtual void handleMessage(inet::cMessage *msg);
    void beginFrame();
    //void checkConnect();
    //int checkGate(int);
    WMaxMsgDlMapMsg * DlMap;
    WMaxMsgUlMapMsg * UlMap;
    int       FrameCnt;
};

class WMaxPhySS : public WMaxPhy//@}
{
 public:
    WMaxPhySS();
    ~WMaxPhySS();
 protected:
    virtual void initialize();
    virtual void handleMessage(inet::cMessage *msg);
    void beginFrame();
};

