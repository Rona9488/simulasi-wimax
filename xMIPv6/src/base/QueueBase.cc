//
// Copyright (C) 2004 Andras Varga
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


#include "QueueBase.h"


void QueueBase::initialize()
{
    AbstractQueue::initialize();
    delay = par("procDelay");
}

void QueueBase::arrival(inet::cPacket *msg)
{
    queue.insert(msg);
}

inet::cPacket *QueueBase::arrivalWhenIdle(inet::cPacket *msg)
{
    return msg;
}

inet::simtime_t QueueBase::startService(inet::cPacket *msg)
{
    return delay;
}

