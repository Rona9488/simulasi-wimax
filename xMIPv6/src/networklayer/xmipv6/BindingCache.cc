/**
 * Copyright (C) 2007 
 * Faqir Zarrar Yousaf
 * Communication Networks Institute, University of Dortmund, Germany.
 * Christian Bauer
 * Institute of Communications and Navigation, German Aerospace Center (DLR)
 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


#include <algorithm>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\util\opp_utils.h"
#include "BindingCache.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6InterfaceData.h"


Define_Module(BindingCache);

std::ostream& operator<<(std::ostream& os, const BindingCache::BindingCacheEntry& bce)
{
    os << "CoA of MN:" << bce.careOfAddress << " BU Lifetime: " << bce.bindingLifetime <<" Home Registeration: "<<bce.isHomeRegisteration <<" BU_Sequence#: "<<bce.sequenceNumber<<"\n";
    return os;
}


BindingCache::BindingCache()
{
}


BindingCache::~BindingCache()
{
//     for (unsigned int i=0; i<bindingUpdateList.size(); i++)
//         delete bindingUpdateList[i];
}


void BindingCache::initialize(int stage)
{
    if (stage==1)
    {
    	WATCH_MAP(bindingCache); //added by Zarrar Yousaf
    }
}


void BindingCache::handleMessage(inet::cMessage *msg)
{
    throw inet::cException("This module doesn't process messages");
}




void BindingCache::addOrUpdateBC(const IPv6Address& hoa, const IPv6Address& coa, const uint lifetime, const uint seq, bool homeReg)
{
	std::cout<<"\n++++++++++++++++++++Binding Cache Being Updated in Routing Table6 ++++++++++++++\n";
	bindingCache[hoa].careOfAddress = coa;
	bindingCache[hoa].bindingLifetime = lifetime;
	bindingCache[hoa].sequenceNumber = seq;
	bindingCache[hoa].isHomeRegisteration = homeReg;
}


uint BindingCache::readBCSequenceNumber(const IPv6Address& HoA)
{
	//Reads the sequence number of the last received BU Message
	/*IPv6Address HoA = bu->getHomeAddressMN();
	uint seqNumber = bindingCache[HoA].sequenceNumber;
	return seqNumber;*/

	// update 10.09.07 - CB
	// the code from above creates a new (empty) entry if
	// the provided HoA does not yet exist.
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos == bindingCache.end() )
		return 0; // HoA not yet registered
	else
		return pos->second.sequenceNumber;
}


bool BindingCache::isInBindingCache(const IPv6Address& HoA, IPv6Address& CoA)
{
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos == bindingCache.end() )
		return false; // if HoA is not registered then there's obviously no valid entry in the BC

	return (pos->second.careOfAddress == CoA); // if CoA corresponds to HoA, everything is fine
}


bool BindingCache::isInBindingCache(const IPv6Address& HoA)
{
	return bindingCache.find(HoA) != bindingCache.end();
}


void BindingCache::deleteEntry(IPv6Address& HoA)
{
	BindingCache6::iterator pos = bindingCache.find(HoA);

	if ( pos != bindingCache.end() ) // update 11.9.07 - CB
		bindingCache.erase(pos);
}


bool BindingCache::getHomeRegistration(const IPv6Address& HoA)
{
	BindingCache6::iterator pos = bindingCache.find( HoA );

	if ( pos == bindingCache.end() )
		return false; // HoA not yet registered; should not occur anyway
	else
		return pos->second.isHomeRegisteration;
}


uint BindingCache::getLifetime(const IPv6Address& HoA)
{
	BindingCache6::iterator pos = bindingCache.find( HoA );

	if ( pos == bindingCache.end() )
		return 0; // HoA not yet registered; should not occur anyway
	else
		return pos->second.bindingLifetime;
}


int BindingCache::generateHomeToken(const IPv6Address& HoA, int nonce)
{
	return HO_TOKEN;
}


int BindingCache::generateCareOfToken(const IPv6Address& CoA, int nonce)
{
	return CO_TOKEN;
}

int BindingCache::generateKey(int homeToken, int careOfToken, const IPv6Address& CoA)
{
	// use a dummy value
	return homeToken+careOfToken;
}


