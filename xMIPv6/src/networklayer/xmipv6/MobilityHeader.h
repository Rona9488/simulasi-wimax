/**
 * Copyright (C) 2007
 * Faqir Zarrar Yousaf
 * Communication Networks Institute, Dortmund University of Technology (TU Dortmund), Germany.
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


#ifndef _IPv6MOBILITYHEADERS_H_
#define _IPv6MOBILITYHEADERS_H_

#include <list>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"
#include "MobilityHeader_m.h"


/**
 * Represents an IPv6 Home Address Option. More info in the IPv6Datagram.msg
 * file (and the documentation generated from it).
 */
class INET_API HomeAddressOption : public HomeAddressOption_Base
{
  public:
	  HomeAddressOption() {};
	  HomeAddressOption(const HomeAddressOption& other) : HomeAddressOption_Base() {operator=(other);}
	  //HomeAddressOption& operator=(const HomeAddressOption& other);
	  HomeAddressOption& operator=(const HomeAddressOption& other) {HomeAddressOption_Base::operator=(other); return *this;}

	  virtual HomeAddressOption *dup() const {return new HomeAddressOption(*this);}
};

#endif
