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

#ifndef __INET_MODULEACCESS_H
#define __INET_MODULEACCESS_H

#include <omnetpp.h>
#include "INETDefs.h"

#ifndef INET_API
#define INET_API
#endif
/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy, and searches
 * recursively among all submodules at every level.
 */
INET_API inet::cModule *findModuleWherever(const char *name, inet::cModule *from);

/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy up to the @node
 * module, and searches recursively among all submodules at every level.
 */
INET_API inet::cModule *findModuleWhereverInNode(const char *name, inet::cModule *from);

/**
 * Find a module with given name, and "closest" to module "from".
 *
 * Operation: gradually rises in the module hierarchy, and looks for a submodule
 * of the given name.
 */
INET_API inet::cModule *findModuleSomewhereUp(const char *name, inet::cModule *from);

/**
 * Checks if the module is node, i.e. it has a @node attribute.
 */
inline bool isNode(inet::cModule *mod)
{
	if (mod)
	{
		inet::cProperties *props = mod->getProperties();
		return props && props->getAsBool("node");
	}
	return false;
}

/**
 * Find the node containing the given module.
 * Returns NULL, if no containing node.
 */
INET_API inet::cModule *findContainingNode(inet::cModule *from);


/**
 * Finds and returns the pointer to a module of type T and name N.
 * Uses findModuleWherever(). See usage e.g. at RoutingTableAccess.
 */
template<typename T>
class ModuleAccess
{
     // Note: MSVC 6.0 doesn't like const char *N as template parameter,
     // so we have to pass it via the ctor...
  private:
    const char *name;
    T *p;
  public:
    ModuleAccess(const char *n) {name = n; p=NULL;}
    virtual ~ModuleAccess() {}

    virtual T *get()
    {
        if (!p)
        {
            inet::cSimulation *simulation = inet::cSimulation::getActiveSimulation();
            inet::cModule *m = findModuleWhereverInNode(name, simulation->getContextModule());
            if (!m) throw inet::cException("Module (%s)%s not found", inet::opp_typename(typeid(T)), name);
            p = check_and_cast<T*>(m);
        }
        return p;
    }
    virtual T *getIfExists()
    {
        if (!p)
        {
            inet::cSimulation *simulation = inet::cSimulation::getActiveSimulation();
            inet::cModule *m = findModuleWhereverInNode(name, simulation->getContextModule());
            p = dynamic_cast<T*>(m);
        }
        return p;
    }
};

#endif

