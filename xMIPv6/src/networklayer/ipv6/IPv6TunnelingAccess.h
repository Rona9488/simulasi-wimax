//
// Copyright (C) 2005 Wei Yang, Ng
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
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//

#ifndef __IPv6_TUNNELING_ACCESS_H__
#define __IPv6_TUNNELING_ACCESS_H__

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\ModuleAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6Tunneling.h"


/**
 * Gives access to IPv6Tunneling
 */
class INET_API IPv6TunnelingAccess : public ModuleAccess<IPv6Tunneling>
{
    public:
        IPv6TunnelingAccess() : ModuleAccess<IPv6Tunneling>("iptunneling") {}
};

#endif


