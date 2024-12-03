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


#include <omnetpp.h>
#include "DropTailQueue.h"


Define_Module(DropTailQueue);

void DropTailQueue::initialize()
{
    PassiveQueueBase::initialize();
    queue.setName("l2queue");

    qlenVec.setName("queue length");
    dropVec.setName("drops");

    outGate = gate("out");

    // configuration
    frameCapacity = par("frameCapacity");
}

bool DropTailQueue::enqueue(inet::cMessage *msg)
{
    if (frameCapacity && queue.length() >= frameCapacity)
    {
        std::cout << "Queue full, dropping packet.\n";
        delete msg;
        dropVec.record(1);
        return true;
    }
    else
    {
        queue.insert(msg);
        qlenVec.record(queue.length());
        return false;
    }
}

inet::cMessage *DropTailQueue::dequeue()
{
    if (queue.empty())
        return NULL;

   inet::cMessage *pk = (inet::cMessage *)queue.pop();

    // statistics
    qlenVec.record(queue.length());

    return pk;
}

void DropTailQueue::sendOut(inet::cMessage *msg)
{
    send(msg, outGate);
}


