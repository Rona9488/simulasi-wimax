//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 Andras Varga
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


#ifndef __INET_INTERFACETABLEACCESS_H
#define __INET_INTERFACETABLEACCESS_H

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\ModuleAccess.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\IInterfaceTable.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTable.h"


/**
 * Gives access to IInterfaceTable.
 */
class INET_API InterfaceTableAccess : public ModuleAccess<IInterfaceTable>
{
    public:
        InterfaceTableAccess() : ModuleAccess<IInterfaceTable>("interfaceTable") {}
};

/**
 * Gives access to InterfaceTable.
 */
class INET_API InterfaceTableAccess2 : public ModuleAccess<InterfaceTable>
{
    public:
        InterfaceTableAccess2() : ModuleAccess<InterfaceTable>("interfaceTable") {}
};

#endif

