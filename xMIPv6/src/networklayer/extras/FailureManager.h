////
//// Copyright (C) 2005 Vojtech Janota
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#ifndef FAILUREMANAGER_H
//#define FAILUREMANAGER_H
//
//#include <omnetpp.h>
//
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\IScriptable.h"
//
///**
// * TODO documentation
// */
//class INET_API FailureManager : public inet::cSimpleModule, public IScriptable
//{
//  protected:
//    virtual void initialize();
//    virtual void handleMessage(inet::cMessage *msg);
//
//    // IScriptable implementation
//    virtual void processCommand(const inet::cXMLElement& node);
//
//  protected:
//    virtual void replaceNode(inet::cModule *mod, const char *newNodeType);
//    virtual void reconnectNode(inet::cModule *old, inet::cModule *n);
//    virtual void reconnectAllGates(inet::cModule *old, inet::cModule *n);
//    virtual void reconnectGates(inet::cModule *old, inet::cModule *n, const char *gateName, int gateIndex=-1);
//    virtual void reconnectGate(inet::cGate *oldGate, inet::cGate *newGate);
//    virtual cModule* getTargetNode(const char *target);
//  private:
//    static inet::cChannel *copyChannel(inet::cChannel *channel);
//    static void copyParams(inet::cComponent *from, inet::cComponent *to);
//};
//
//#endif
