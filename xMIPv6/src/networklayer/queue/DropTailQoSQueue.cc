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
#include "DropTailQoSQueue.h"


Define_Module(DropTailQoSQueue);

DropTailQoSQueue::DropTailQoSQueue()
{
    queues = NULL;
    numQueues = NULL;
}

DropTailQoSQueue::~DropTailQoSQueue()
{
    for (int i=0; i<numQueues; i++)
        delete queues[i];
    delete [] queues;
}

void DropTailQoSQueue::initialize()
{
    PassiveQueueBase::initialize();

    // configuration
    frameCapacity = par("frameCapacity");

    const char *classifierClass = par("classifierClass");
    classifier = check_and_cast<IQoSClassifier *>(inet::createOne(classifierClass));

    outGate = gate("out");

    numQueues = classifier->getNumQueues();
    queues = new inet::cQueue *[numQueues];
    for (int i=0; i<numQueues; i++)
    {
        char buf[32];
        sprintf(buf, "queue-%d", i);
        queues[i] = new inet::cQueue(buf);
    }
}

bool DropTailQoSQueue::enqueue(inet::cMessage *msg)
{
    int queueIndex = classifier->classifyPacket(msg);
    inet::cQueue *queue = queues[queueIndex];

    if (frameCapacity && queue->length() >= frameCapacity)
    {
        std::cout << "Queue " << queueIndex << " full, dropping packet.\n";
        delete msg;
        return true;
    }
    else
    {
        queue->insert(msg);
        return false;
    }
}

inet::cMessage *DropTailQoSQueue::dequeue()
{
    // queue 0 is highest priority
    for (int i=0; i<numQueues; i++)
        if (!queues[i]->empty())
            return (inet::cMessage *)queues[i]->pop();
    return NULL;
}

void DropTailQoSQueue::sendOut(inet::cMessage *msg)
{
    send(msg, outGate);
}


