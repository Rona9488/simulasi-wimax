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
//#ifndef __SCTPASSOCIATION_H
//#define __SCTPASSOCIATION_H
//
//#include <omnetpp.h>
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\queue\DropTailQoSQueue.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPvXAddress.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddress.h"
//#include "SCTP.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\RoutingTable.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\RoutingTableAccess.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTable.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\common\InterfaceTableAccess.h"
//#include "SCTPSendStream.h"
//#include "SCTPReceiveStream.h"
//#include "SCTPMessage.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPControlInfo.h"
//#include <list>
//#include <iostream>
//#include <errno.h>
//#include <math.h>
////#include <platdep/intxtypes.h>
//
//class SCTPMessage;
//class SCTPCommand;
//class SCTPOpenCommand;
//class SCTPQueue;
//class SCTPReceiveStream;
//class SCTPSendStream;
//class SCTPAlgorithm;
//class SCTP;
//
//typedef std::vector<IPvXAddress> AddressVector;
//
//enum SctpState
//{
//	SCTP_S_CLOSED            = 0,
//	SCTP_S_COOKIE_WAIT       = FSM_Steady(1),
//	SCTP_S_COOKIE_ECHOED     = FSM_Steady(2),
//	SCTP_S_ESTABLISHED       = FSM_Steady(3),
//	SCTP_S_SHUTDOWN_PENDING  = FSM_Steady(4),
//	SCTP_S_SHUTDOWN_SENT     = FSM_Steady(5),
//	SCTP_S_SHUTDOWN_RECEIVED = FSM_Steady(6),
//	SCTP_S_SHUTDOWN_ACK_SENT = FSM_Steady(7)
//};
//
//
////
//// Event, strictly for the FSM state transition purposes.
//// DO NOT USE outside performStateTransition()!
////
//enum SCTPEventCode
//{
//	SCTP_E_ASSOCIATE,
//	SCTP_E_OPEN_PASSIVE,
//	SCTP_E_ABORT,
//	SCTP_E_SHUTDOWN,
//	SCTP_E_CLOSE,
//	SCTP_E_SEND,
//	SCTP_E_RCV_INIT,
//	SCTP_E_RCV_ABORT,
//	SCTP_E_RCV_VALID_COOKIE_ECHO,
//	SCTP_E_RCV_INIT_ACK,
//	SCTP_E_RCV_COOKIE_ACK,
//	SCTP_E_RCV_SHUTDOWN,
//	SCTP_E_RCV_SHUTDOWN_ACK,
//	SCTP_E_RCV_SHUTDOWN_COMPLETE,
//	SCTP_E_NO_MORE_OUTSTANDING,
//	SCTP_E_TIMEOUT_INIT_TIMER,
//	SCTP_E_TIMEOUT_SHUTDOWN_TIMER,
//	SCTP_E_TIMEOUT_RTX_TIMER,
//	SCTP_E_TIMEOUT_HEARTBEAT_TIMER,
//	SCTP_E_IGNORE,
//	SCTP_E_RECEIVE,
//	SCTP_E_DUP_RECEIVED,
//	SCTP_E_PRIMARY,
//	SCTP_E_DELIVERED,
//	SCTP_E_QUEUE,
//	SCTP_E_SEND_SHUTDOWN_ACK,
//	SCTP_E_STOP_SENDING
//};
//
//enum SCTPChunkTypes
//{
//	DATA			= 0,
//	INIT			= 1,
//	INIT_ACK		= 2,
//	SACK			= 3,
//	HEARTBEAT		= 4,
//	HEARTBEAT_ACK		= 5,
//	ABORT			= 6,
//	SHUTDOWN		= 7,
//	SHUTDOWN_ACK		= 8,
//	ERRORTYPE		= 9,
//	COOKIE_ECHO		= 10,
//	COOKIE_ACK		= 11,
//	SHUTDOWN_COMPLETE	= 14,
//
//};
//
//
//enum SCTPFlags
//{
//	COMPLETE_MESG_UNORDERED	= 1,
//	COMPLETE_MESG_ORDERED	= 0
//};
//
//
//enum SCTPParameterTypes
//{
//	UNRECOGNIZED_PARAMETER			= 8,
//	SUPPORTED_ADDRESS_TYPES			= 12,
//};
//
//
//
//
//enum SCTPCCModules
//{
//	RFC4960					= 0
//};
//
//enum SCTPStreamSchedulers
//{
//	ROUND_ROBIN				= 0
//};
//
//
//#define SCTP_COMMON_HEADER  				12    // without options
//#define SCTP_INIT_CHUNK_LENGTH				20
//#define SCTP_DATA_CHUNK_LENGTH  			16
//#define SCTP_SACK_CHUNK_LENGTH				16
//#define SCTP_HEARTBEAT_CHUNK_LENGTH			4
//#define SCTP_ABORT_CHUNK_LENGTH				4
//#define SCTP_COOKIE_ACK_LENGTH				4
//#define SCTP_FORWARD_TSN_CHUNK_LENGTH			8
//#define SCTP_SHUTDOWN_CHUNK_LENGTH			8
//#define SCTP_SHUTDOWN_ACK_LENGTH			4
//#define SCTP_ERROR_CHUNK_LENGTH				4    // without parameters
//
//#define SCTP_DEFAULT_ARWND 				(1<<16)
//#define SCTP_DEFAULT_INBOUND_STREAMS 			10 //17
//#define SCTP_DEFAULT_OUTBOUND_STREAMS 			5 //17
//#define VALID_COOKIE_LIFE_TIME  			10
//#define SCTP_COOKIE_LENGTH				76
//#define HB_INTERVAL					30
//#define PATH_MAX_RETRANS				5
//
//#define SCTP_TIMEOUT_INIT_REXMIT     			3    // initially 3 seconds
//#define SCTP_TIMEOUT_INIT_REXMIT_MAX 			240  // 4 mins
//#define SACK_DELAY              			0.2
//#define RTO_BETA					0.25
//#define RTO_ALPHA					0.125
//#define RTO_INITIAL					3
//#define IPTOS_DEFAULT           			0x10    /* IPTOS_LOWDELAY */
//
//#define DEFAULT_MAX_SENDQUEUE   			0       /* unlimited send queue */
//#define DEFAULT_MAX_RECVQUEUE   			0       /* unlimited recv queue - unused really */
//
//#define MAX_ASSOCS					10
//
//#define SCTP_MAX_PAYLOAD				1488 // 12 bytes for common header
//
//#define MAX_GAP_COUNT					360
//#define MAX_GAP_REPORTS					4
//#define ADD_PADDING(x)					((((x) + 3) >> 2) << 2)
//
////#define RFC						0
//#define DEBUG						1
//
//#define SHUTDOWN_GUARD_TIMEOUT				180
//
///**
// * Returns the minimum of a and b.
// */
//inline double min(double a, double b) {return a<b ? a : b;}
//
///**
// * Returns the maximum of a and b.
// */
//inline double max(double a, double b) {return a<b ? b : a;}
//
//
//class SCTPDataVariables : public inet::cObject
//{
//	public:
//		SCTPDataVariables();
//		~SCTPDataVariables();
//		inet::cPacket* userData;
//		bool ordered;
//		uint16_t len;
//		uint32_t tsn;
//		uint16_t sid;
//		uint16_t ssn;
//		uint32_t ppid;
//		uint32_t gapReports;
//		inet::simtime_t enqueuingTime;
//		inet::simtime_t sendTime;
//		inet::simtime_t ackTime;
//		inet::simtime_t expiryTime;
//		bool hasBeenAcked;
//		bool hasBeenRemoved; //chunk has been removed from receiveStream
//		bool hasBeenAbandoned;
//		bool hasBeenFastRetransmitted;
//		bool countsAsOutstanding;
//		IPvXAddress lastDestination;
//		IPvXAddress initialDestination;
//		IPvXAddress nextDestination;
//		uint32_t numberOfTransmissions;
//		uint32_t numberOfRetransmissions;
//		uint32_t allowedNoRetransmissions;
//		uint32_t booksize;
//};
//
//
//
//class SCTPPathVariables : public inet::cObject
//{
//	public:
//		SCTPPathVariables(IPvXAddress addr, SCTPAssociation* assoc);
//		~SCTPPathVariables();
//		SCTPAssociation* association;
//		IPvXAddress remoteAddress;
//		bool activePath;
//		bool confirmed;
//		bool requiresRtx;
//		bool hbWasAcked;
//		bool primaryPathCandidate;
//		bool forceHb;
//		uint32_t pathErrorCount;
//		uint32_t pathErrorThreshold;
//		uint32_t pmtu;
//		uint32_t cwnd;
//		uint32_t ssthresh;
//		uint32_t partialBytesAcked;
//		uint32_t outstandingBytes;
//		inet::simtime_t heartbeatTimeout;
//		inet::simtime_t heartbeatIntervalTimeout;
//		inet::simtime_t rtxTimeout;
//		inet::simtime_t cwndTimeout;
//		inet::simtime_t updateTime;
//		inet::simtime_t lastAckTime;
//		inet::simtime_t cwndAdjustmentTime;
//		inet::simtime_t pathRto;  //double
//		inet::simtime_t srtt;
//		inet::simtime_t rttvar;
//		inet::cMessage *HeartbeatTimer;
//		inet::cMessage *HeartbeatIntervalTimer;
//		inet::cMessage *CwndTimer;
//		inet::cMessage *T3_RtxTimer;
//		inet::cOutVector *pathSsthresh;
//		inet::cOutVector *pathCwnd;
//		inet::cOutVector *pathTSN;
//		inet::cOutVector *pathRcvdTSN;
//		inet::cOutVector *pathRTO;
//		inet::cOutVector *pathRTT;
//};
//
//
//
//
//class SCTPStateVariables : public inet::cObject
//{
//	public:
//		SCTPStateVariables();
//		~SCTPStateVariables();
//	public:
//		bool active;
//		bool fork;
//		bool ackPointAdvanced;
//		bool dataChunkReceived;
//		bool initReceived;
//		bool cookieEchoReceived;
//		bool newChunkReceived;
//		bool firstChunkReceived;
//		bool swsAvoidanceInvoked;
//		bool probingIsAllowed;
//		bool zeroWindowProbing;
//		bool alwaysBundleSack;
//		bool fastRecoveryActive;
//		bool fastRecoverySupported;
//		bool nagleEnabled;
//		bool sackAllowed;
//		bool reactivatePrimaryPath;
//		bool fragment;
//		bool resetPending;
//		bool stopReceiving; // incoming data will be discarded
//		bool stopOldData;	  // data with TSN<peerTsnAfterReset will be discarded
//		bool queueUpdate;
//		bool firstDataSent;
//		bool peerWindowFull;
//		bool zeroWindow;
//		bool stopSending;   //will be called when SCTP_E_SHUTDOWN arrived
//		bool inOut;
//		bool noMoreOutstanding;
//		IPvXAddress primaryPathIndex;
//		IPvXAddress initialPrimaryPath;
//		IPvXAddress lastUsedDataPath;
//		IPvXAddress lastDataSourceAddress;
//		IPvXAddress nextDest;
//		AddressVector localAddresses;
//		std::list<uint32_t> dupList;
//		uint32_t errorCount;  // overall error counter
//		u_int64 peerRwnd;
//		u_int64 initialPeerRwnd;
//		u_int64 localRwnd;
//		uint32_t nextTSN; // TSN to be sent
//		uint32_t lastTsnAck; //stored at the sender side; cumTSNAck announced in a SACK
//		uint32_t cTsnAck; // will be put in the SACK chunk
//		uint32_t highestTsnReceived; // will be set when DATA chunk arrived
//		uint32_t highestTsnAcked;
//		uint32_t highestTsnStored; //used to compare Tsns in makeRoomForTsn
//		uint32_t lastTsnReceived; //SACK
//		uint32_t lastTSN; // my very last TSN to be sent
//		uint32_t ackState; // number of packets to be acknowledged
//		uint32_t numGaps;
//		uint32_t gapStartList[MAX_GAP_COUNT];
//		uint32_t gapStopList[MAX_GAP_COUNT];
//		u_int64 queuedBytes;
//		u_int64 queuedRcvBytes;	//number of messages in receive queues
//		uint32_t fastRecoveryExitPoint;
//		uint32_t lastStreamScheduled;
//		uint32_t assocPmtu; //smallest overall path mtu
//		uint32_t msgNum; //indicates the sequence number of the message
//		u_int64 bytesRcvd;
//		uint32_t numRequests;
//		uint32_t messagesToPush;
//		int32_t pushMessagesLeft;
//		uint32_t count;
//		uint localTieTag[32];
//		uint peerTieTag[32];
//		u_int64 queuedMessages;  // Messages buffered at the sender side
//		uint32_t messageAcceptLimit;
//		uint32_t queueLimit;
//		uint16_t header;
//		int32_t probingTimeout;
//		int32_t numMsgsReq[100];
//		int32_t cookieLifeTime;
//		/** Counter for init and cookie retransmissions */
//		int16_t initRetransCounter;
//		//int16_t numParam;
//		inet::simtime_t initRexmitTimeout;
//		/** pointer to the init chunk data structure (for retransmissions) */
//		SCTPInitChunk *initChunk;
//		/** pointer to the cookie chunk data structure (for retransmissions) */
//		SCTPCookieEchoChunk *cookieChunk;
//		/** pointer to the resetChunk (for retransmission) */
//		SCTPShutdownChunk* shutdownChunk;
//		SCTPShutdownAckChunk* shutdownAckChunk;
//		SCTPMessage* sctpmsg;
//		int32_t sendQueueLimit;
//		bool appSendAllowed;
//		uint32_t nextRSid;
//		uint32_t swsLimit;
//};
//
//
//
//class SCTPAssociation : public inet::cObject
//{
//	public:
//		// connection identification by apps: appgateIndex+assocId
//		int32_t appGateIndex; // application gate index
//		int32_t assocId;       // identifies connection within the app
//		IPvXAddress remoteAddr;
//		IPvXAddress localAddr;
//		uint16_t localPort;
//		uint16_t remotePort;
//		bool listen;
//		uint32_t localVTag;   // local verification tag
//		uint32_t peerVTag;    // remote verification tag
//
//		// timers
//		inet::cMessage *T1_InitTimer;
//		inet::cMessage *T2_ShutdownTimer;
//		inet::cMessage *T5_ShutdownGuardTimer;
//		inet::cMessage *SackTimer;
//		inet::cMessage *StartTesting;
//
//	protected:
//
//		AddressVector localAddressList;
//		AddressVector remoteAddressList;
//
//		int32_t	status;
//		uint32_t numberOfRemoteAddresses;
//
//		uint32_t initTsn; //DATA
//		uint32_t initPeerTsn;
//		uint32_t inboundStreams;
//		uint32_t outboundStreams;
//		uint32_t sackFrequency;
//		double sackPeriod;
//	// variables associated with the state of this Association
//		SCTPStateVariables *state;
//
//		inet::cOutVector *advRwnd;
//		inet::cOutVector *quBytes;
//		inet::cOutVector *cumTsnAck;
//		inet::cOutVector* sendQueue;
//
//		SCTP *sctpMain;  // SCTP module
//
//		// SCTP state machine
//		inet::cFSM* fsm;
//
//		// map for storing the path parameters
//		typedef std::map<IPvXAddress,SCTPPathVariables*> SCTPPathMap;
//		SCTPPathMap sctpPathMap;
//
//		//map for storing the queued bytes per path
//		typedef std::map<IPvXAddress, uint32_t> CounterMap;
//		typedef struct counter {
//			u_int64 roomSumSendStreams;
//			u_int64 bookedSumSendStreams;
//			u_int64 roomSumRcvStreams;
//			CounterMap roomTransQ;
//			CounterMap bookedTransQ;
//			CounterMap roomRetransQ;
//			} QueueCounter;
//		QueueCounter qCounter;
//		// SCTP queues
//		SCTPQueue *transmissionQ;
//		SCTPQueue *retransmissionQ;
//
//		typedef std::map<uint32_t, SCTPSendStream*> SCTPSendStreamMap;
//		SCTPSendStreamMap sendStreams;
//
//		typedef std::map<uint32_t, SCTPReceiveStream*> SCTPReceiveStreamMap;
//
//		SCTPReceiveStreamMap receiveStreams;
//		// SCTP behavior in data transfer state
//		SCTPAlgorithm *sctpAlgorithm;
//		typedef struct calcBytesToSend {
//			bool chunk;
//			bool packet;
//			uint32_t bytesToSend;
//		} BytesToBeSent;
//		BytesToBeSent bytes;
//
//
//		typedef struct congestionControlFunctions {
//			void (SCTPAssociation::*ccInitParams)(SCTPPathVariables* path);
//			void (SCTPAssociation::*ccUpdateAfterSack)(bool rtxNecessary, SCTPPathVariables* path);
//			void (SCTPAssociation::*ccUpdateAfterCwndTimeout)(SCTPPathVariables* path);
//			void (SCTPAssociation::*ccUpdateAfterRtxTimeout)(SCTPPathVariables* path);
//			void (SCTPAssociation::*ccUpdateMaxBurst)(SCTPPathVariables* path);
//			void (SCTPAssociation::*ccUpdateBytesAcked)(uint32_t ackedBytes, uint32_t osb, bool ctsnaAdvanced, IPvXAddress pathId, uint32_t pathOsb, uint32_t newOsb);
//		} CCFunctions;
//		CCFunctions ccFunctions;
//		uint16_t ccModule;
//	public:
//		/**
//		* Constructor.
//		*/
//		SCTPAssociation(SCTP *mod, int32_t appGateIndex, int32_t assocId);
//
//		/**
//		* Destructor.
//		*/
//		~SCTPAssociation();
//		/**
//		* Utility: Send data from sendQueue, at most maxNumBytes (-1 means no limit).
//		* If fullSegments is set, don't send segments smaller than MSS (needed for Nagle).
//		* Returns true if some data was actually sent.
//		*/
//
//		void sendAll(IPvXAddress pathId);
//
//		/** Utility: returns name of SCTP_I_xxx constants */
//		static const char *indicationName(int32_t code);
//
//		/* @name Various getters */
//		//@{
//		int32_t getFsmState() const {return fsm->getState();};
//		SCTPStateVariables *getState() {return state;};
//		SCTPQueue *getTransmissionQueue() {return transmissionQ;};
//		SCTPQueue *getRetransmissionQueue() {return retransmissionQ;};
//		SCTPAlgorithm *getSctpAlgorithm() {return sctpAlgorithm;};
//		SCTP *getSctpMain() {return sctpMain;};
//		inet::cFSM* getFsm() {return fsm;};
//
//		inet::cMessage *getInitTimer() {return T1_InitTimer;};
//		inet::cMessage *getShutdownTimer() {return T2_ShutdownTimer;};
//		inet::cMessage *getSackTimer() {return SackTimer;};
//
//		/** Utility: returns name of SCTP_S_xxx constants */
//		static const char *stateName(int32_t state);
//
//		uint32_t chunkToInt(char* type);
//
//
//		/* Process self-messages (timers).
//		* Normally returns true. A return value of false means that the
//		* connection structure must be deleted by the caller (SCTPMain).
//		*/
//		bool processTimer(inet::cMessage *msg);
//
//
//		/**
//		* Process incoming SCTP segment. Normally returns true. A return value
//		* of false means that the connection structure must be deleted by the
//		* caller (SCTP).
//		*/
//		bool processSCTPMessage(SCTPMessage *sctpmsg, IPvXAddress srcAddr, IPvXAddress destAddr);
//
//		/**
//		* Process commands from the application.
//		* Normally returns true. A return value of false means that the
//		* connection structure must be deleted by the caller (SCTP).
//		*/
//		bool processAppCommand(inet::cPacket *msg);
//
//		void removePath();
//		void removePath(IPvXAddress addr);
//		void removeLastPath(IPvXAddress addr);
//		void deleteStreams();
//		void stopTimer(inet::cMessage* timer);
//		void stopTimers();
//
//		SCTPPathVariables* getPath(IPvXAddress pid);
//		void printSctpPathMap();
//
//	protected:
//
//
//
//
//		/** @name FSM transitions: analysing events and executing state transitions */
//		//@{
//		/** Maps app command codes (msg kind of app command msgs) to SCTP_E_xxx event codes */
//		SCTPEventCode preanalyseAppCommandEvent(int32_t commandCode);
//		/** Implemements the pure SCTP state machine */
//		bool performStateTransition(const SCTPEventCode& event);
//		void stateEntered(int32_t state);
//		//@}
//
//		/** @name Processing app commands. Invoked from processAppCommand(). */
//		//@{
//		void process_ASSOCIATE(SCTPEventCode& event, SCTPCommand *sctpCommand, inet::cPacket *msg);
//		void process_OPEN_PASSIVE(SCTPEventCode& event, SCTPCommand *sctpCommand, inet::cPacket *msg);
//		void process_SEND(SCTPEventCode& event, SCTPCommand *sctpCommand, inet::cPacket *msg);
//		void process_CLOSE(SCTPEventCode& event);
//		void process_ABORT(SCTPEventCode& event);
//		void process_STATUS(SCTPEventCode& event, SCTPCommand *sctpCommand, inet::cPacket *msg);
//		void process_RECEIVE_REQUEST(SCTPEventCode& event, SCTPCommand *sctpCommand);
//		void process_PRIMARY(SCTPEventCode& event, SCTPCommand *sctpCommand);
//		//@}
//
//		/** @name Processing SCTP message arrivals. Invoked from processSCTPMessage(). */
//		//@{
//		bool process_RCV_Message(SCTPMessage *sctpseg, IPvXAddress src, IPvXAddress dest);
//		/**
//		* Process incoming SCTP packets. Invoked from process_RCV_Message
//		*/
//		bool processInitArrived(SCTPInitChunk* initChunk, int32_t sport, int32_t dport);
//		bool processInitAckArrived(SCTPInitAckChunk* initAckChunk);
//		bool processCookieEchoArrived(SCTPCookieEchoChunk* cookieEcho, IPvXAddress addr);
//		bool processCookieAckArrived();
//		SCTPEventCode processDataArrived(SCTPDataChunk *dataChunk, uint32_t count);
//		SCTPEventCode processSackArrived(SCTPSackChunk *sackChunk);
//		SCTPEventCode processHeartbeatAckArrived(SCTPHeartbeatAckChunk* heartbeatack, SCTPPathVariables* path);
//		//@}
//
//		/** @name Processing timeouts. Invoked from processTimer(). */
//		//@{
//		int32_t process_TIMEOUT_RTX(SCTPPathVariables* path);
//		void process_TIMEOUT_HEARTBEAT(SCTPPathVariables* path);
//		void process_TIMEOUT_HEARTBEAT_INTERVAL(SCTPPathVariables* path, bool force);
//		void process_TIMEOUT_INIT_REXMIT(SCTPEventCode& event);
//		void process_TIMEOUT_CWND(SCTPPathVariables* path);
//		void process_TIMEOUT_PROBING();
//		void process_TIMEOUT_SHUTDOWN(SCTPEventCode& event);
//		int32_t updateCounters(SCTPPathVariables* path);
//		//@}
//
//		void startTimer(inet::cMessage* timer, inet::simtime_t timeout);
//
//		/** Utility: clone a listening association. Used for forking. */
//		SCTPAssociation *cloneAssociation();
//
//		/** Utility: creates send/receive queues and sctpAlgorithm */
//		void initAssociation(SCTPOpenCommand *openCmd);
//
//		/** Methods dealing with the handling of TSNs  **/
//		bool tsnIsDuplicate(uint32_t tsn);
//		bool advanceCtsna();
//		bool updateGapList(uint32_t tsn);
//		void removeFromGapList(uint32_t removedTsn);
//		bool makeRoomForTsn(uint32_t tsn, uint32_t length, bool uBit);
//
//		/** Methods for creating and sending chunks */
//		void sendInit();
//		void sendInitAck(SCTPInitChunk* initchunk);
//		void sendCookieEcho(SCTPInitAckChunk* initackchunk);
//		void sendCookieAck(IPvXAddress dest);
//		void sendAbort();
//		void sendHeartbeat(SCTPPathVariables *path, bool local);
//		void sendHeartbeatAck(SCTPHeartbeatChunk *heartbeatChunk, IPvXAddress src, IPvXAddress dest);
//		void sendSack();
//		void sendShutdown();
//		void sendShutdownAck(IPvXAddress dest);
//		void sendShutdownComplete();
//		SCTPSackChunk* createSack();
//		/** Retransmitting chunks */
//		void retransmitInit();
//		void retransmitCookieEcho();
//		void retransmitShutdown();
//		void retransmitShutdownAck();
//
//
//		/** Utility: adds control info to message and sends it to IP */
//		//void sendToIP(SCTPMessage *sctpmsg);
//		//void sendToIP(SCTPMessage *sctpmsg);
//		void sendToIP(SCTPMessage *sctpmsg);
//		void sendToIP(SCTPMessage *sctpmsg, IPvXAddress dest);
//		void sendToIP(SCTPMessage *sctpmsg, IPvXAddress src, IPvXAddress dest);
//
//		void scheduleSack();
//		/** Utility: signal to user that connection timed out */
//		void signalConnectionTimeout();
//
//		/** Utility: start a timer */
//		void scheduleTimeout(inet::cMessage *msg, inet::simtime_t timeout)
//		{
//		    sctpMain->scheduleAt(inet::simTime() + timeout, msg);
//		}
//
//		/** Utility: cancel a timer */
//		inet::cMessage *cancelEvent(inet::cMessage *msg)  {return sctpMain->cancelEvent(msg);}
//
//		/** Utility: sends packet to application */
//		void sendToApp(inet::cPacket *msg);
//
//		/** Utility: sends status indication (SCTP_I_xxx) to application */
//		void sendIndicationToApp(int32_t code);
//
//		/** Utility: sends SCTP_I_ESTABLISHED indication with SCTPConnectInfo to application */
//		void sendEstabIndicationToApp();
//		void pushUlp();
//		void sendDataArrivedNotification(uint16_t sid);
//		void putInDeliveryQ(uint16_t sid);
//		/** Utility: prints local/remote addr/port and app gate index/assocId */
//		void printConnBrief();
//		/** Utility: prints important header fields */
//		static void printSegmentBrief(SCTPMessage *sctpmsg);
//
//
//
//		/** Utility: returns name of SCTP_E_xxx constants */
//		static const char *eventName(int32_t event);
//
//		void addPath(IPvXAddress addr);
//		IPvXAddress getNextDestination(SCTPDataVariables* chk);
//		IPvXAddress getNextAddress(IPvXAddress dpi);
//
//		void bytesAllowedToSend(IPvXAddress dpi);
//
//		void pathStatusIndication(IPvXAddress pid, bool status);
//
//		bool allPathsInactive(void);
//		uint32_t getLevel(IPvXAddress addr);
//
//		/**
//		* Manipulating chunks
//		*/
//		SCTPDataChunk* transformDataChunk(SCTPDataVariables* datVar);
//		SCTPDataVariables* makeVarFromMsg(SCTPDataChunk* datachunk);
//
//		/**
//		*Dealing with streams
//		*/
//
//		int32_t streamScheduler(bool peek);
//		void initStreams(uint32_t inStreams, uint32_t outStreams);
//		int32_t numUsableStreams(void);
//
//		typedef struct streamSchedulingFunctions {
//			void (SCTPAssociation::*ssInitStreams)(uint32_t inStreams, uint32_t outStreams);
//			int32_t (SCTPAssociation::*ssGetNextSid)(bool peek);
//			int32_t (SCTPAssociation::*ssUsableStreams)(void);
//		} SSFunctions;
//		SSFunctions ssFunctions;
//		uint16_t ssModule;
//
//		/**
//		*	Queue Management
//		*/
//		int32_t getQueuedBytes(void);
//		int32_t getOutstandingBytes(void);
//		int32_t dequeueAckedChunks(uint32_t tsna, IPvXAddress pathId, inet::simtime_t* rttEstimation);
//		uint32_t getOutstandingBytesOnPath(IPvXAddress pathId);
//		SCTPDataVariables* peekOutboundDataChunk(IPvXAddress pid);
//		SCTPDataMsg* peekOutboundDataMsg(void);
//		SCTPDataVariables* peekAbandonedChunk(IPvXAddress pid);
//		SCTPDataVariables* getOutboundDataChunk(IPvXAddress pid, int32_t bytes);
//		SCTPDataMsg* dequeueOutboundDataMsg(int32_t bytes);
//		void process_QUEUE(SCTPCommand *sctpCommand);
//		/**
//		* Flow control
//		*/
//		void pmDataIsSentOn(IPvXAddress pathId);
//		void pmStartPathManagement(void);
//		void pmClearPathCounter(IPvXAddress pid);
//		void pmRttMeasurement(IPvXAddress pathId, inet::simtime_t rttEstimate, int32_t acknowledgedBytes);
//		void fcAdjustCounters(uint32_t ackedBytes, uint32_t osb, bool ctsnaAdvanced, IPvXAddress pathId, uint32_t pathOsb, uint32_t newOsb);
//
//		/**
//		* Compare TSNs
//		*/
//		int32_t tsnLt (uint32_t tsn1, uint32_t tsn2) { return ((int32_t)(tsn1-tsn2)<0); }
//		int32_t tsnLe (uint32_t tsn1, uint32_t tsn2) { return ((int32_t)(tsn1-tsn2)<=0); }
//		int32_t tsnGe (uint32_t tsn1, uint32_t tsn2) { return ((int32_t)(tsn1-tsn2)>=0); }
//		int32_t tsnGt (uint32_t tsn1, uint32_t tsn2) { return ((int32_t)(tsn1-tsn2)>0); }
//		int32_t tsnBetween (uint32_t tsn1, uint32_t midtsn, uint32_t tsn2) { return ((tsn2-tsn1)>=(midtsn-tsn1)); }
//
//		int16_t ssnGt (uint16_t ssn1, uint16_t ssn2) { return ((int16_t)(ssn1-ssn2)>0); }
//
//		uint32_t subBytes(uint32_t osb, uint32_t bytes) {return (((int32_t)(osb-bytes)>0)?osb-bytes:0);}
//
//		void disposeOf(SCTPMessage* sctpmsg);
//		void printOutstandingTsns();
//
//		/** SCTPCCFunctions  **/
//		void initCCParameters(SCTPPathVariables* path);
//
//		void cwndUpdateAfterSack(bool rtxNecessary, SCTPPathVariables* path);
//
//		void cwndUpdateAfterCwndTimeout(SCTPPathVariables* path);
//
//		void cwndUpdateAfterRtxTimeout(SCTPPathVariables* path);
//
//		void cwndUpdateMaxBurst(SCTPPathVariables* path);
//
//		void cwndUpdateBytesAcked(uint32_t ackedBytes, uint32_t osb, bool ctsnaAdvanced, IPvXAddress pathId, uint32_t pathOsb, uint32_t newOsb);
//};
//
//#endif
//
//
