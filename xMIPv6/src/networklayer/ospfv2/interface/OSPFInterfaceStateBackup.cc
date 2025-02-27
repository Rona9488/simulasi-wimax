////
//// Copyright (C) 2006 Andras Babos and Andras Varga
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU Lesser General Public License for more details.
////
//// You should have received a copy of the GNU Lesser General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#include "OSPFInterfaceStateBackup.h"
//#include "OSPFInterfaceStateDown.h"
//#include "OSPFInterfaceStateLoopback.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ospfv2\router\OSPFArea.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ospfv2\router\OSPFRouter.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ospfv2\messagehandler\MessageHandler.h"
//
//void OSPF::InterfaceStateBackup::ProcessEvent(OSPF::Interface* intf, OSPF::Interface::InterfaceEventType event)
//{
//    if (event == OSPF::Interface::NeighborChange) {
//        CalculateDesignatedRouter(intf);
//    }
//    if (event == OSPF::Interface::InterfaceDown) {
//        intf->Reset();
//        ChangeState(intf, new OSPF::InterfaceStateDown, this);
//    }
//    if (event == OSPF::Interface::LoopIndication) {
//        intf->Reset();
//        ChangeState(intf, new OSPF::InterfaceStateLoopback, this);
//    }
//    if (event == OSPF::Interface::HelloTimer) {
//        if (intf->GetType() == OSPF::Interface::Broadcast) {
//            intf->SendHelloPacket(OSPF::AllSPFRouters);
//        } else {    // OSPF::Interface::NBMA
//            unsigned long neighborCount = intf->GetNeighborCount();
//            int           ttl           = (intf->GetType() == OSPF::Interface::Virtual) ? VIRTUAL_LINK_TTL : 1;
//            for (unsigned long i = 0; i < neighborCount; i++) {
//                intf->SendHelloPacket(intf->GetNeighbor(i)->GetAddress(), ttl);
//            }
//        }
//        intf->GetArea()->GetRouter()->GetMessageHandler()->StartTimer(intf->GetHelloTimer(), intf->GetHelloInterval());
//    }
//    if (event == OSPF::Interface::AcknowledgementTimer) {
//        intf->SendDelayedAcknowledgements();
//    }
//}
//
