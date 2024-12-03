//
// (C) 2005 Vojtech Janota
//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#ifndef __INET_SIMPLECLASSIFIER_H
#define __INET_SIMPLECLASSIFIER_H

#include <omnetpp.h>
#include <vector>
#include <string>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\mpls\ConstType.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddress.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\IPDatagram.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\IScriptable.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\rsvp_te\IRSVPClassifier.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\mpls\LIBTable.h"
#include "IntServ.h"

class RSVP;

/**
 * TODO documentation
 */
class INET_API SimpleClassifier: public inet::cSimpleModule, public IScriptable, public IRSVPClassifier
{
  public:
    struct FECEntry
    {
        int id;

        IPAddress src;
        IPAddress dest;

        SessionObj_t session;
        SenderTemplateObj_t sender;

        int inLabel;
    };

  protected:
    IPAddress routerId;
    int maxLabel;

    std::vector<FECEntry> bindings;
    LIBTable *lt;
    RSVP *rsvp;

  public:
    SimpleClassifier() {}

  protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const  {return 5;}
    virtual void handleMessage(inet::cMessage *msg);

    // IScriptable implementation
    virtual void processCommand(const inet::cXMLElement& node);

    // IRSVPClassifier implementation
    virtual bool lookupLabel(IPDatagram *ipdatagram, LabelOpVector& outLabel, std::string& outInterface, int& color);
    virtual void bind(const SessionObj_t& session, const SenderTemplateObj_t& sender, int inLabel);

  protected:
    virtual void readTableFromXML(const inet::cXMLElement *fectable);
    virtual void readItemFromXML(const inet::cXMLElement *fec);
    std::vector<FECEntry>::iterator findFEC(int fecid);
};

#endif

