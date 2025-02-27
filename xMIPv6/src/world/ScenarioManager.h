//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H

#include <omnetpp.h>
#include <string>
#include <stdexcept>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\IScriptable.h"


/**
 * Scenario Manager (experimental) which executes a script specified in XML.
 * ScenarioManager has a few built-in commands such as \<set-param>,
 * \<set-channel-attr>, etc, and can pass commands to modules that implement
 * the IScriptable interface. The \<at> built-in command can be used to
 * group commands to be carried out at the same simulation time.
 *
 * See NED file for details.
 *
 * @see IScriptable
 * @author Andras Varga
 */
class INET_API ScenarioManager : public inet::cSimpleModule
{
  protected:
    // total number of changes, and number of changes already done
    int numChanges;
    int numDone;

  protected:
    // utilities
    const char *getRequiredAttribute(inet::cXMLElement *node, const char *attr);
    virtual inet::cModule *getRequiredModule(inet::cXMLElement *node, const char *attr);
    virtual inet::cGate *getRequiredGate(inet::cXMLElement *node, const char *modattr, const char *gateattr);

    // dispatch to command processors
    virtual void processCommand(inet::cXMLElement *node);

    // command processors
    virtual void processAtCommand(inet::cXMLElement *node);
    virtual void processSetParamCommand(inet::cXMLElement *node);
    virtual void processSetChannelAttrCommand(inet::cXMLElement *node);
    virtual void processCreateModuleCommand(inet::cXMLElement *node);
    virtual void processDeleteModuleCommand(inet::cXMLElement *node);
    virtual void processConnectCommand(inet::cXMLElement *node);
    virtual void processDisconnectCommand(inet::cXMLElement *node);
    virtual void processModuleSpecificCommand(inet::cXMLElement *node);

  public:
    ScenarioManager() {}

  protected:
    virtual void initialize();
    virtual void handleMessage(inet::cMessage *msg);
    virtual void updateDisplayString();
};

#endif
