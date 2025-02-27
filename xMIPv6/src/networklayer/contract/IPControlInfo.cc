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

#include "IPControlInfo.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\IPDatagram.h"

IPControlInfo::~IPControlInfo()
{
    if (dgram)
    {
    	drop(dgram);
    	delete dgram;
    }
}

void IPControlInfo::setOrigDatagram(IPDatagram *d)
{
    if (dgram)
        throw inet::cException("IPControlInfo::setOrigDatagram(): a datagram is already attached");
    dgram = d;
    take(dgram);
}

IPDatagram *IPControlInfo::removeOrigDatagram()
{
    if (!dgram)
        throw inet::cException("IPControlInfo::removeOrigDatagram(): no datagram attached "
                  "(already removed, or maybe this IPControlInfo does not come "
                  "from the IP module?)");
    IPDatagram *ret = dgram;
    drop(dgram);
    dgram = NULL;
    return ret;
}


