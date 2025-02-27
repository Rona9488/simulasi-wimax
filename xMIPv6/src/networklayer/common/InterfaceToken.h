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

#ifndef __INET_INTERFACETOKEN_H
#define __INET_INTERFACETOKEN_H

#include <vector>
#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"

/**
 * An "interface token" as defined in RFC 1971 (IPv6 Stateless Autoconfiguration).
 * This class supports tokens of length 1..64-bits. An interface token needs
 * to be provided by L2 modules in order to be able to form IPv6 link local
 * addresses.
 */
class INET_API InterfaceToken
{
  private:
    uint32_t _normal, _low;
    short _len; // in bits, 1..64
  public:
    InterfaceToken()  {_normal=_low=_len=0;}
    InterfaceToken(uint32_t low, uint32_t normal, int len)  {_normal=normal; _low=low; _len=len;}
    InterfaceToken(const InterfaceToken& t)  {operator=(t);}
    void operator=(const InterfaceToken& t)  {_normal=t._normal; _low=t._low; _len=t._len;}
    int length() const {return _len;}
    uint32_t low() const {return _low;}
    uint32_t normal() const {return _normal;}
};

#endif

