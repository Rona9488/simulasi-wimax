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


#include "ModuleAccess.h"

static inet::cModule *findSubmodRecursive(inet::cModule *curmod, const char *name)
{
    for (inet::cModule::SubmoduleIterator i(curmod); !i.end(); i++)
    {
        inet::cModule *submod = i();
        if (!strcmp(submod->getFullName(), name))
            return submod;
        inet::cModule *foundmod = findSubmodRecursive(submod, name);
        if (foundmod)
            return foundmod;
    }
    return NULL;
}

inet::cModule *findModuleWherever(const char *name, inet::cModule *from)
{
    inet::cModule *mod = NULL;
    for (inet::cModule *curmod=from; !mod && curmod; curmod=curmod->getParentModule())
        mod = findSubmodRecursive(curmod, name);
    return mod;
}

inet::cModule *findModuleWhereverInNode(const char *name, inet::cModule *from)
{
    inet::cModule *mod = NULL;
    for (inet::cModule *curmod=from; curmod; curmod=curmod->getParentModule())
    {
        mod = findSubmodRecursive(curmod, name);
        if (mod || isNode(curmod))
            break;
    }
    return mod;
}

inet::cModule *findModuleSomewhereUp(const char *name, inet::cModule *from)
{
    inet::cModule *mod = NULL;
    for (inet::cModule *curmod=from; !mod && curmod; curmod=curmod->getParentModule())
        mod = curmod->getSubmodule(name);
    return mod;
}

inet::cModule *findContainingNode(inet::cModule *from)
{
    for (inet::cModule *curmod=from; curmod; curmod=curmod->getParentModule())
    {
        if (isNode(curmod))
        	return curmod;
    }
    return NULL;
}
