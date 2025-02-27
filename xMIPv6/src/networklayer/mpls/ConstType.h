//
// (C) 2005 Vojtech Janota
// (C) 2003 Xuan Thang Nguyen
//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#ifndef __INET_CONSTANT_H
#define __INET_CONSTANT_H


#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"

enum messageKind
{
    MPLS_KIND,
    LDP_KIND,
    SIGNAL_KIND
};


namespace ConstType
{

const  char libDataMarker[]="In-lbl       In-intf     Out-lbl       Out-intf";
const  char prtDataMarker[]="Prefix            Pointer";

const char UnknownData[]="UNDEFINED";
const char NoLabel[] = "Nolabel";
const char wildcast[]="*";
const char empty[]="";

const int ldp_port = 646;

const int LDP_KIND =10;
const int HOW_KIND =50;

};

#endif


