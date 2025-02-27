//
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
#pragma once

#ifndef __INET_INTERFACETABLE_H
#define __INET_INTERFACETABLE_H

#include <vector>
#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\IInterfaceTable.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceEntry.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\NotificationBoard.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPv6Address.h"

/**
 * Represents the interface table. This object has one instance per host
 * or router. It has methods to manage the interface table,
 * so one can access functionality similar to the "ifconfig" command.
 *
 * See the NED documentation for general overview.
 *
 * This is a simple module without gates, it requires function calls to it
 * (message handling does nothing). Methods are provided for reading and
 * updating the interface table.
 *
 * Interfaces are dynamically registered: at the start of the simulation,
 * every L2 module adds its own InterfaceEntry to the table; after that,
 * IPv4's IRoutingTable and IPv6's RoutingTable6 (an possibly, further
 * L3 protocols) add protocol-specific data on each InterfaceEntry
 * (see IPv4InterfaceData, IPv6InterfaceData, and InterfaceEntry::setIPv4Data(),
 * InterfaceEntry::setIPv6Data())
 *
 * Interfaces are represented by InterfaceEntry objects.
 *
 * When interfaces need to be reliably and efficiently identified from other
 * modules, interfaceIds should be used. They are better suited than pointers
 * because when an interface gets removed (see deleteInterface()), it is
 * often impossible/impractical to invalidate all pointers to it, and also
 * because pointers are not necessarily unique (a new InterfaceEntry may get
 * allocated exactly at the address of a previously deleted one).
 * Interface Ids are unique (Ids of removed interfaces are not issued again),
 * stale Ids can be detected, and they are also invariant to insertion/deletion.
 *
 * Clients can get notified about interface changes by subscribing to
 * the following notifications in NotificationBoard: NF_INTERFACE_CREATED,
 * NF_INTERFACE_DELETED, NF_INTERFACE_STATE_CHANGED, NF_INTERFACE_CONFIG_CHANGED.
 * State change gets fired for up/down events; all other changes fire as
 * config change.
 *
 * @see InterfaceEntry
 */
//===== Adam =======================================================
struct AP_Info{
    int    AP_ID;
    MACAddress     L2_Addr;
    IPv6Address    L3_Addr;
    IPv6Address    Prefix;
    int            PrefixLength; 
};
//===== Adam end ===================================================
 
class INET_API InterfaceTable : public omnetpp::cSimpleModule, public IInterfaceTable, protected INotifiable
{
  protected:
    //============= Adam 09-09-2011 =====================
    AP_Info BS_Info[3];     // info o BSach jak L2 adres L3 adres prefix, potrzebne do Fast Handover
    IPv6Address Handover_NCoA; // NCoA tworzony z PrRtAdv z AR, potrzebne do Fast Handover
    //============= Adam, end  09-09-2011==================
    NotificationBoard *nb; // cached pointer
    // primary storage for interfaces: vector indexed by id; may contain NULLs;
    // slots are never reused to ensure id uniqueness
    typedef std::vector<InterfaceEntry *> InterfaceVector;
    InterfaceVector idToInterface;

    // fields to support getNumInterfaces() and getInterface(pos)
    int tmpNumInterfaces; // caches number of non-NULL elements of idToInterface; -1 if invalid
    InterfaceEntry **tmpInterfaceList; // caches non-NULL elements of idToInterface; NULL if invalid

  protected:
    // displays summary above the icon
    virtual void updateDisplayString();

    // discover and store which nwlayer/host gates connect to this interface
    virtual void discoverConnectingGates(InterfaceEntry *entry, omnetpp::cModule *ifmod);

    // called from InterfaceEntry
    virtual void interfaceChanged(InterfaceEntry *entry, int category);

    // internal
    virtual void invalidateTmpInterfaceList();

  public:
//===== Adam =======================================================
    virtual void setAP_Info( int AP_ID ,MACAddress L2_Addr ,IPv6Address L3_Addr ,IPv6Address Prefix ,int PrefixLength);
    MACAddress getL2_Addr(int AP_index);
    IPv6Address getL3_Addr(int AP_index);
    IPv6Address getPrefix(int AP_index);
    int getPrefixLength(int AP_index);
    void setHandover_NCoA(IPv6Address prefix, int prefixLength ,IPv6Address linkLocal);
    IPv6Address getHandover_NCoA();
//===== Adam end ===================================================
    InterfaceTable();
    virtual ~InterfaceTable();
    virtual std::string getFullPath() const {return omnetpp::cSimpleModule::getFullPath();}

  protected:
    virtual int numInitStages() const {return 2;}
    virtual void initialize(int stage);

    /**
     * Raises an error.
     */
    virtual void handleMessage(omnetpp::cMessage *);

  public:
    /**
     * Called by the NotificationBoard whenever a change of a category
     * occurs to which this client has subscribed.
     */
    virtual void receiveChangeNotification(int category, const omnetpp::cObject *details);

    /**
     * Adds an interface. The second argument should be a module which belongs
     * to the physical interface (e.g. PPP or EtherMac) -- it will be used
     * to discover and fill in getNetworkLayerGateIndex(), getNodeOutputGateId(),
     * and getNodeInputGateId() in InterfaceEntry. It should be NULL if this is
     * a virtual interface (e.g. loopback).
     */
    virtual void addInterface(InterfaceEntry *entry, omnetpp::cModule *ifmod);

    /**
     * Deletes the given interface from the table. Indices of existing
     * interfaces (see getInterface(int)) may change. It is an error if
     * the given interface is not in the table.
     */
    virtual void deleteInterface(InterfaceEntry *entry);

    /**
     * Returns the number of interfaces.
     */
    virtual int getNumInterfaces();

    /**
     * Returns the InterfaceEntry specified by an index 0..numInterfaces-1.
     * Throws an error if index is out of range.
     *
     * Note that this index is NOT the same as interfaceId! Indices are
     * not guaranteed to stay the same after interface addition/deletion,
     * so cannot be used to reliably identify the interface. Use interfaceId
     * to refer to interfaces from other modules or from messages/packets.
     */
    virtual InterfaceEntry *getInterface(int pos);

    /**
     * Returns an interface by its Id. Ids are guaranteed to be invariant
     * to interface deletions/additions. Returns NULL if there is no such
     * interface (This allows detecting stale IDs without raising an error.)
     */
    virtual InterfaceEntry *getInterfaceById(int id);

    /**
     * Returns an interface given by its getNodeOutputGateId().
     * Returns NULL if not found.
     */
    virtual InterfaceEntry *getInterfaceByNodeOutputGateId(int id);

    /**
     * Returns an interface given by its getNodeInputGateId().
     * Returns NULL if not found.
     */
    virtual InterfaceEntry *getInterfaceByNodeInputGateId(int id);

    /**
     * Returns an interface given by its getNetworkLayerGateIndex().
     * Returns NULL if not found.
     */
    virtual InterfaceEntry *getInterfaceByNetworkLayerGateIndex(int index);

    /**
     * Returns an interface given by its name. Returns NULL if not found.
     */
    virtual InterfaceEntry *getInterfaceByName(const char *name);

    /**
     * Returns the first interface with the isLoopback flag set.
     * (If there's no loopback, it returns NULL -- but this
     * should never happen because InterfaceTable itself registers a
     * loopback interface on startup.)
     */
    virtual InterfaceEntry *getFirstLoopbackInterface();
};

#endif

