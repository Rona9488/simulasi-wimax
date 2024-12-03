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
//cplusplus {{
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPvXAddress.h"
//}}
//
//
//
//cplusplus {{
//typedef inet::cPacket *cPacketPtr;
//}}
//
//
//struct cPacketPtr;
//
//
//class noncobject IPvXAddress;
//
//message SCTPSimpleMessage extends cPacket
//{
//    uint32_t dataLen;
//    char data[];		//cd
//    simtime_t creationTime = 0;
//    bool encaps = false;
//}
//
//message SCTPMessage extends cPacket
//{
//    @customize(true);
//    // Source Port
//    uint16_t srcPort;
//    // Destination Port
//    uint16_t destPort;
//    // Verification Tag
//    uint32_t tag;
//    bool checksumOk;
//    abstract cPacketPtr chunks[];
//}
//
//
//message SCTPChunk extends cPacket
//{
//    @customize(false);
//    // Chunk Type
//    uint8 chunkType;
//}
//
//message SCTPInitChunk extends SCTPChunk
//{
//    // Initiate Tag
//    uint32_t initTag;
//    // Advertised Receiver Window
//    uint32_t a_rwnd;
//    // Number of Outbound Streams
//    uint16_t noOutStreams;
//    // Number of Inbound Streams
//    uint16_t noInStreams;
//    // Initial TSN
//    uint32_t initTSN;
//    bool forwardTsn;
//    IPvXAddress addresses[];
//    uint8 unrecognizedParameters[]; //Will be filled by the Parser, if unrecognized Parameters arrive.
//}
//
//message SCTPInitAckChunk extends SCTPChunk
//{
//    // Initiate Tag
//    uint32_t initTag;
//    // Advertised Receiver Window
//    uint32_t a_rwnd;
//    // Number of Outbound Streams
//    uint16_t noOutStreams;
//    // Number of Inbound Streams
//    uint16_t noInStreams;
//    // Initial TSN
//    uint32_t initTSN;
//    bool forwardTsn;
//    IPvXAddress addresses[];
//    char cookie[];
//    uint8 unrecognizedParameters[];
//    cPacketPtr stateCookie;
//}
//
//
//
//message SCTPCookieEchoChunk extends SCTPChunk
//{
//    char cookie[];
//    cPacketPtr stateCookie;
//    uint8 unrecognizedParameters[]; //for the serializer to send an Error chunk bundled with a Cookie-Echo
//}
//
//message SCTPCookie extends cPacket
//{
//    simtime_t creationTime;
//    uint32_t localTag;
//    uint32_t peerTag;
//    uint8 localTieTag[];
//    uint8 peerTieTag[];
//}
//
//message SCTPCookieAckChunk extends SCTPChunk
//{
//}
//
//message SCTPDataMsg extends cPacket
//{
//    simtime_t enqueuingTime;
//    simtime_t expiryTime;
//    uint32_t ppid;
//    IPvXAddress initialDestination;
//    uint32_t msgNum;
//    uint16_t sid;
//    bool ordered;
//    uint32_t booksize;
//    uint32_t rtx;
//}
//
//message SCTPDataChunk extends SCTPChunk
//{
//	// Chunk Flags
//	bool eBit = 0;
//	bool bBit = 0;
//	bool uBit = 0;
//	// Transmission Sequence Number
//	uint32_t tsn;
//	// Stream identifier
//	uint16_t sid;
//	// Stream Sequence Number
//	uint16_t ssn;
//	// Payload Protocol Identifier
//	uint32_t ppid;
//	simtime_t enqueuingTime;
//}
//message SCTPForwardTsnChunk extends SCTPChunk
//{
//    uint32_t newCumTsn;
//    uint16_t sid[];
//    short ssn[]; // set -1 in case of unordered delivery
//}
//
//message SCTPSackChunk extends SCTPChunk
//{
//	// Cumulative TSN Ack
//	uint32_t cumTsnAck;
//	// Advertised Receiver Window Credit
//	uint32_t a_rwnd;
//	// Number of Gap Ack Blocks
//	uint16_t numGaps;
//	// Number of Duplicate TSNs
//	uint16_t numDupTsns;
//	// Start and End of Gap Ack Blocks
//	uint32_t gapStart[];
//	uint32_t gapStop[];
//	uint32_t dupTsns[];
//}
//
//message SCTPAbortChunk extends SCTPChunk
//{
//    // Chunk Flags
//    bool T_Bit = 0;
//}
//
//message SCTPHeartbeatChunk extends SCTPChunk
//{
//    IPvXAddress remoteAddr;
//    simtime_t timeField;
//    char info[];
//}
//
//message SCTPHeartbeatAckChunk extends SCTPChunk
//{
//    IPvXAddress remoteAddr;
//    simtime_t timeField;
//    char info[];
//}
//
//message SCTPShutdownChunk extends SCTPChunk
//{
//    uint32_t cumTsnAck;
//}
//
//message SCTPShutdownAckChunk extends SCTPChunk
//{
//}
//
//message SCTPShutdownCompleteChunk extends SCTPChunk
//{
//    bool TBit = 0;
//}
//
//message SCTPErrorChunk extends SCTPChunk
//{
//    @customize(true);
//    abstract cPacketPtr parameters[];
//}
//
//message SCTPParameter extends cPacket
//{
//    uint16_t parameterType;
//}
//
