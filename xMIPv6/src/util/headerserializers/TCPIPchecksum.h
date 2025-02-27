//
// Copyright (C) 2005 Christian Dankbar, Irene Ruengeler, Michael Tuexen
//               2009 Thomas Reschka, Zoltan Bojthe
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __TCPIPCHECKSUM_H
#define __TCPIPCHECKSUM_H


#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\transport\tcp\TCPSegment.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\transport\tcp\TCPSegment_m.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPvXAddress.h"

#include "headers/defs.h"

#include "headers/tcp.h"

/**
 * Converts between TCPSegment and binary (network byte order) TCP header.
 */
class TCPIPchecksum
{
    public:
        TCPIPchecksum() {}

        /*
         * calculate the 16 bit one's complement of the one's
         * complement sum of all 16 bit words in the header and text.  If a
         * segment contains an odd number of header and text octets to be
         * checksummed, the last octet is padded on the right with zeros to
         * form a 16 bit word for checksum purposes
        */
        static uint16_t checksum(const void *addr, unsigned int count)
        {
            return ~ _checksum(addr, count);
        }

        static uint16_t _checksum(const void *addr, unsigned int count);
};

#endif
