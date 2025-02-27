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

 
#ifndef __WMAX_CTRLSS_ACCESS_H__
#define __WMAX_CTRLSS_ACCESS_H__

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\ModuleAccess.h"
#include "wmaxctrl.h"


/**
 * Gives access to WMaxCtrlSS. 
 */
class INET_API WMaxCtrlSSAccess : public ModuleAccess<WMaxCtrlSS>
{
    public:
        WMaxCtrlSSAccess() : ModuleAccess<WMaxCtrlSS>("WMaxCtrlSS0") {}
};

#endif


