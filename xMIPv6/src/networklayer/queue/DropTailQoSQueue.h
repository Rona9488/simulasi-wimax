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


#ifndef __INET_DROPTAILQOSQUEUE_H
#define __INET_DROPTAILQOSQUEUE_H

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\PassiveQueueBase.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\queue\IQoSClassifier.h"
/**
 * Drop-front QoS queue. See NED for more info.
 */
class INET_API DropTailQoSQueue : public PassiveQueueBase
{
  protected:
    // configuration
    int frameCapacity;

    // state
    int numQueues;
    inet::cQueue **queues;
    IQoSClassifier *classifier;

    inet::cGate *outGate;

  public:
    DropTailQoSQueue();
    virtual ~DropTailQoSQueue();

  protected:
    virtual void initialize();

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual bool enqueue(inet::cMessage *msg);

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual inet::cMessage *dequeue();

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual void sendOut(inet::cMessage *msg);

};

#endif


