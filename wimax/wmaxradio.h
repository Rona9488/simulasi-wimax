/**
 * @file   wmaxmac.h
 * @author Tomasz Mrugalski <thomson@klub.com.pl>
 * @date   2007-06-25 01:27:46+0200
 * 
 * @brief  WMax Radio connector (used to connect multiple SSes to one BS)
 * @licence GNU GPLv2
 * 
 */

#ifndef WMAXRADIO_H
#define WMAXRADIO_H

#include <omnetpp.h>
#include <vector>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\util\fsm.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"

using namespace std;
class WMaxRadio : public inet::cSimpleModule
{
public:
    void connect(inet::cModule * ss);
    void disconnect(inet::cModule * ss);
protected:
    virtual void initialize();
    virtual void handleMessage(inet::cMessage *msg);
};

#endif
