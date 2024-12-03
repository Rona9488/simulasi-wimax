////
//// Copyright (C) 2008 Irene Ruengeler
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU General Public License
//// as published by the Free Software Foundation; either version 2
//// of the License, or (at your option) any later version.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with this program; if not, see <http://www.gnu.org/licenses/>.
////
//
//#ifndef __SCTP_H
//#define __SCTP_H
//
//#ifdef _MSC_VER
//#pragma warning(disable : 4786)
//#endif
//
//#include <omnetpp.h>
//#include <map>
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPvXAddress.h"
//
//
//class SCTPAssociation;
//class SCTPMessage;
//
//
//#define sctpEV3 (!SCTP::testing==true)?std::cerr:std::cerr
//
//
//
///**
// * Implements the SCTP protocol. This section describes the internal
// * architecture of the SCTP model.
// *
// *  You may want to check the SCTPSocket
// * class which makes it easier to use SCTP from applications.
// *
// * The SCTP protocol implementation is composed of several classes (discussion
// * follows below):
// *  - SCTP: the module class
// *  - SCTPAssociation: manages a connection
// *  - SCTPSendQueue, SCTPReceiveQueue: abstract base classes for various types
// *    of send and receive queues
// *  - SCTPAlgorithm: abstract base class for SCTP algorithms
// *
// * SCTP subclassed from cSimpleModule. It manages socketpair-to-connection
// * mapping, and dispatches segments and user commands to the appropriate
// * SCTPAssociation object.
// *
// * SCTPAssociation manages the connection, with the help of other objects.
// * SCTPAssociation itself implements the basic SCTP "machinery": takes care
// * of the state machine, stores the state variables (TCB), sends/receives
// *  etc.
// *
// * SCTPAssociation internally relies on 3 objects. The first two are subclassed
// * from SCTPSendQueue and SCTPReceiveQueue. They manage the actual data stream,
// * so SCTPAssociation itself only works with sequence number variables.
// * This makes it possible to easily accomodate need for various types of
// * simulated data transfer: real byte stream, "virtual" bytes (byte counts
// * only), and sequence of cMessage objects (where every message object is
// * mapped to a SCTP sequence number range).
// *
// * Currently implemented send queue and receive queue classes are
// * SCTPVirtualDataSendQueue and SCTPVirtualDataRcvQueue which implement
// * queues with "virtual" bytes (byte counts only).
// *
// * The third object is subclassed from SCTPAlgorithm. Control over
// * retransmissions, congestion control and ACK sending are "outsourced"
// * from SCTPAssociation into SCTPAlgorithm: delayed acks, slow start, fast rexmit,
// * etc. are all implemented in SCTPAlgorithm subclasses.
// *
// * The concrete SCTPAlgorithm class to use can be chosen per connection (in OPEN)
// * or in a module parameter.
// */
//class SCTP : public inet::cSimpleModule
//{
//	public:
//		struct AppConnKey
//		{
//			int32_t appGateIndex;
//			int32_t assocId;
//
//			inline bool operator<(const AppConnKey& b) const
//			{
//				if (appGateIndex!=b.appGateIndex)
//					return appGateIndex<b.appGateIndex;
//				else
//					return assocId<b.assocId;
//			}
//
//		};
//		struct SockPair
//		{
//			IPvXAddress localAddr;
//			IPvXAddress remoteAddr;
//			uint16_t localPort;
//			uint16_t remotePort;
//
//			inline bool operator<(const SockPair& b) const
//			{
//				if (remoteAddr!=b.remoteAddr)
//					return remoteAddr<b.remoteAddr;
//				else if (localAddr!=b.localAddr)
//					return localAddr<b.localAddr;
//				else if (remotePort!=b.remotePort)
//					return remotePort<b.remotePort;
//				else
//					return localPort<b.localPort;
//			}
//		};
//		struct VTagPair
//		{
//			uint32_t peerVTag;
//			uint16_t localPort;
//			uint16_t remotePort;
//
//			inline bool operator<(const VTagPair& b) const
//			{
//				if (peerVTag!=b.peerVTag)
//					return peerVTag<b.peerVTag;
//				else if (remotePort!=b.remotePort)
//					return remotePort<b.remotePort;
//				else
//					return localPort<b.localPort;
//			}
//		};
//		typedef struct
//		{
//			int32_t assocId;
//			inet::simtime_t start;
//			inet::simtime_t stop;
//			u_int64 rcvdBytes;
//			u_int64 sentBytes;
//			u_int64 transmittedBytes;
//			u_int64 ackedBytes;
//			uint32_t numFastRtx;
//			uint32_t numT3Rtx;
//			uint32_t numPathFailures;
//			uint32_t numForwardTsn;
//			double throughput;
//			inet::simtime_t lifeTime;
//		}AssocStat;
//
//		typedef std::map<int32_t,AssocStat> AssocStatMap;
//		AssocStatMap assocStatMap;
//		typedef std::map<VTagPair,int32_t> SctpVTagMap;
//		SctpVTagMap sctpVTagMap;
//
//	protected:
//		typedef std::map<AppConnKey,SCTPAssociation*> SctpAppConnMap;
//		typedef std::map<SockPair,SCTPAssociation*> SctpConnMap;
//
//
//		SctpAppConnMap sctpAppConnMap;
//		SctpConnMap sctpConnMap;
//
//		int32_t sizeConnMap;
//		static int32_t nextConnId;
//
//		uint16_t nextEphemeralPort;
//
//		SCTPAssociation *findAssocForMessage(IPvXAddress srcAddr, IPvXAddress destAddr, uint32_t srcPort, uint32_t destPort, bool findListen);
//		SCTPAssociation *findAssocForApp(int32_t appGateIndex, int32_t assocId);
//		void sendAbortFromMain(SCTPMessage* sctpmsg, IPvXAddress srcAddr, IPvXAddress destAddr);
//		void sendShutdownCompleteFromMain(SCTPMessage* sctpmsg, IPvXAddress srcAddr, IPvXAddress destAddr);
//		void updateDisplayString();
//
//	public:
//		static bool testing;    // switches between sctpEV and testingEV
//		static bool logverbose; // if !testing, turns on more verbose logging
//		void printInfoConnMap();
//
//		void removeAssociation(SCTPAssociation *assoc);
//		inet::simtime_t testTimeout;
//		uint32_t numGapReports;
//		uint32_t numPacketsReceived;
//		uint32_t numPacketsDropped;
//
//		virtual ~SCTP();
//		virtual void initialize();
//		virtual void handleMessage(inet::cMessage *msg);
//		virtual void finish();
//
//		/**
//		* To be called from SCTPAssociation when socket pair  changes
//		*/
//		void updateSockPair(SCTPAssociation *assoc, IPvXAddress localAddr, IPvXAddress remoteAddr, int32_t localPort, int32_t remotePort);
//		void addLocalAddress(SCTPAssociation *conn, IPvXAddress address);
//		void addLocalAddressToAllRemoteAddresses(SCTPAssociation *conn, IPvXAddress address, std::vector<IPvXAddress> remAddresses);
//		void addRemoteAddress(SCTPAssociation *conn, IPvXAddress localAddress, IPvXAddress remoteAddress);
//		void removeLocalAddressFromAllRemoteAddresses(SCTPAssociation *conn, IPvXAddress address, std::vector<IPvXAddress> remAddresses);
//		void removeRemoteAddressFromAllConnections(SCTPAssociation *conn, IPvXAddress address, std::vector<IPvXAddress> locAddresses);
//		/**
//		* Update assocs socket pair, and register newAssoc (which'll keep LISTENing).
//		* Also, assoc will get a new assocId (and newAssoc will live on with its old assocId).
//		*/
//		void addForkedAssociation(SCTPAssociation *assoc, SCTPAssociation *newAssoc, IPvXAddress localAddr, IPvXAddress remoteAddr, int32_t localPort, int32_t remotePort);
//
//		/**
//		* To be called from SCTPAssociation: reserves an ephemeral port for the connection.
//		*/
//		int16_t getEphemeralPort();
//
//		/**
//		* Generates a new integer, to be used as assocId. (assocId is part of the key
//		* which associates connections with their apps).
//		*/
//		static int32_t getNewConnId() {return ++nextConnId;}
//
//		SCTPAssociation* getAssoc(int32_t assocId);
//		SCTPAssociation *findAssocWithVTag(uint32_t peerVTag, uint32_t remotePort, uint32_t localPort);
//		SctpVTagMap getVTagMap() {return sctpVTagMap;};
//};
//
//#endif
//
//
//
