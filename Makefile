#
# OMNeT++/OMNEST Makefile for numbat-git
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -Xdoc -Xobsolete -Xresults -Xscripts -XxMIPv6/obsolete -XxMIPv6/tests
#

# Name of target to be created (-o option)
TARGET_DIR = .
TARGET_NAME = numbat-git$(D)
TARGET = $(TARGET_NAME)$(EXE_SUFFIX)
TARGET_IMPLIB = $(TARGET_NAME)$(IMPLIB_SUFFIX)
TARGET_IMPDEF = $(TARGET_NAME)$(IMPDEF_SUFFIX)
TARGET_FILES = $(TARGET_DIR)/$(TARGET)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH =

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/util/addrpack.o \
    $O/util/fsm.o \
    $O/util/ipv6.o \
    $O/util/logger.o \
    $O/util/ssinfo.o \
    $O/wimax/wmaxctrl.o \
    $O/wimax/wmaxmac.o \
    $O/wimax/wmaxmaccs.o \
    $O/wimax/wmaxphy.o \
    $O/wimax/wmaxradio.o \
    $O/xMIPv6/src/applications/ethernet/EtherAppCli.o \
    $O/xMIPv6/src/applications/ethernet/EtherAppSrv.o \
    $O/xMIPv6/src/applications/generic/IPTrafGen.o \
    $O/xMIPv6/src/applications/pingapp/PingApp.o \
    $O/xMIPv6/src/applications/rtpapp/RTPApplication.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPClient.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPPeer.o \
    $O/xMIPv6/src/applications/sctpapp/SCTPServer.o \
    $O/xMIPv6/src/applications/tcpapp/TCPBasicClientApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPEchoApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericCliAppBase.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericSrvApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPGenericSrvThread.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSessionApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSinkApp.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSpoof.o \
    $O/xMIPv6/src/applications/tcpapp/TCPSrvHostApp.o \
    $O/xMIPv6/src/applications/tcpapp/TelnetApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPAppBase.o \
    $O/xMIPv6/src/applications/udpapp/UDPBasicApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPEchoApp.o \
    $O/xMIPv6/src/applications/udpapp/UDPSink.o \
    $O/xMIPv6/src/applications/udpapp/UDPVideoStreamCli.o \
    $O/xMIPv6/src/applications/udpapp/UDPVideoStreamSvr.o \
    $O/xMIPv6/src/base/AbstractQueue.o \
    $O/xMIPv6/src/base/BasicModule.o \
    $O/xMIPv6/src/base/Blackboard.o \
    $O/xMIPv6/src/base/ByteArrayMessage.o \
    $O/xMIPv6/src/base/Join.o \
    $O/xMIPv6/src/base/ModuleAccess.o \
    $O/xMIPv6/src/base/NotificationBoard.o \
    $O/xMIPv6/src/base/NotifierConsts.o \
    $O/xMIPv6/src/base/PassiveQueueBase.o \
    $O/xMIPv6/src/base/ProtocolMap.o \
    $O/xMIPv6/src/base/QueueBase.o \
    $O/xMIPv6/src/base/QueueWithQoS.o \
    $O/xMIPv6/src/base/ReassemblyBuffer.o \
    $O/xMIPv6/src/base/Sink.o \
    $O/xMIPv6/src/linklayer/contract/MACAddress.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherBus.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherEncap.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherHub.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherLLC.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMAC.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMAC2.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherMACBase.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitBase.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitNP.o \
    $O/xMIPv6/src/linklayer/etherswitch/MACRelayUnitPP.o \
    $O/xMIPv6/src/linklayer/ext/cSocketRTScheduler.o \
    $O/xMIPv6/src/linklayer/ext/ExtInterface.o \
    $O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Mac.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211AgentSTA.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAdhoc.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAP.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPBase.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtAPSimplified.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtBase.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTA.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtSTASimplified.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/CSMAMacLayer.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/Decider80211.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/ErrAndCollDecider.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/decider/SnrDecider.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/GilbertElliotSnr.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval.o \
    $O/xMIPv6/src/linklayer/mf80211/phyLayer/snrEval/SnrEval80211.o \
    $O/xMIPv6/src/linklayer/mfcore/BasicDecider.o \
    $O/xMIPv6/src/linklayer/mfcore/BasicSnrEval.o \
    $O/xMIPv6/src/linklayer/mfcore/WirelessMacBase.o \
    $O/xMIPv6/src/linklayer/ppp/DropsGenerator.o \
    $O/xMIPv6/src/linklayer/ppp/DuplicatesGenerator.o \
    $O/xMIPv6/src/linklayer/ppp/PPP.o \
    $O/xMIPv6/src/linklayer/ppp/ThruputMeter.o \
    $O/xMIPv6/src/linklayer/radio/AbstractRadio.o \
    $O/xMIPv6/src/linklayer/radio/GenericRadio.o \
    $O/xMIPv6/src/linklayer/radio/GenericRadioModel.o \
    $O/xMIPv6/src/linklayer/radio/Ieee80211Radio.o \
    $O/xMIPv6/src/linklayer/radio/Ieee80211RadioModel.o \
    $O/xMIPv6/src/linklayer/radio/Modulation.o \
    $O/xMIPv6/src/linklayer/radio/PathLossReceptionModel.o \
    $O/xMIPv6/src/mobility/ANSimMobility.o \
    $O/xMIPv6/src/mobility/BasicMobility.o \
    $O/xMIPv6/src/mobility/BonnMotionFileCache.o \
    $O/xMIPv6/src/mobility/BonnMotionMobility.o \
    $O/xMIPv6/src/mobility/CircleMobility.o \
    $O/xMIPv6/src/mobility/ConstSpeedMobility.o \
    $O/xMIPv6/src/mobility/LinearMobility.o \
    $O/xMIPv6/src/mobility/LineSegmentsMobilityBase.o \
    $O/xMIPv6/src/mobility/MassMobility.o \
    $O/xMIPv6/src/mobility/NullMobility.o \
    $O/xMIPv6/src/mobility/RandomWPMobility.o \
    $O/xMIPv6/src/mobility/RectangleMobility.o \
    $O/xMIPv6/src/mobility/TurtleMobility.o \
    $O/xMIPv6/src/networklayer/arp/ARP.o \
    $O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator.o \
    $O/xMIPv6/src/networklayer/autorouting/FlatNetworkConfigurator6.o \
    $O/xMIPv6/src/networklayer/autorouting/NetworkConfigurator.o \
    $O/xMIPv6/src/networklayer/common/InterfaceEntry.o \
    $O/xMIPv6/src/networklayer/common/InterfaceTable.o \
    $O/xMIPv6/src/networklayer/contract/IPAddress.o \
    $O/xMIPv6/src/networklayer/contract/IPAddressResolver.o \
    $O/xMIPv6/src/networklayer/contract/IPControlInfo.o \
    $O/xMIPv6/src/networklayer/contract/IPv6Address.o \
    $O/xMIPv6/src/networklayer/contract/IPv6ControlInfo.o \
    $O/xMIPv6/src/networklayer/contract/IPvXAddress.o \
    $O/xMIPv6/src/networklayer/extras/Dummy.o \
    $O/xMIPv6/src/networklayer/extras/FailureManager.o \
    $O/xMIPv6/src/networklayer/extras/NetworkInfo.o \
    $O/xMIPv6/src/networklayer/icmpv6/ICMPv6.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourCache.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NeighbourDiscovery.o \
    $O/xMIPv6/src/networklayer/ipv4/ErrorHandling.o \
    $O/xMIPv6/src/networklayer/ipv4/ICMP.o \
    $O/xMIPv6/src/networklayer/ipv4/IP.o \
    $O/xMIPv6/src/networklayer/ipv4/IPFragBuf.o \
    $O/xMIPv6/src/networklayer/ipv4/IPRoute.o \
    $O/xMIPv6/src/networklayer/ipv4/IPv4InterfaceData.o \
    $O/xMIPv6/src/networklayer/ipv4/RoutingTable.o \
    $O/xMIPv6/src/networklayer/ipv4/RoutingTableParser.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Datagram.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ErrorHandling.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6FragBuf.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6InterfaceData.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Tunneling.o \
    $O/xMIPv6/src/networklayer/ipv6/RoutingTable6.o \
    $O/xMIPv6/src/networklayer/ldp/LDP.o \
    $O/xMIPv6/src/networklayer/mpls/LIBTable.o \
    $O/xMIPv6/src/networklayer/mpls/MPLS.o \
    $O/xMIPv6/src/networklayer/mpls/MPLSPacket.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFRouting.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterface.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceState.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateBackup.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDesignatedRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateDown.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateLoopback.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateNotDesignatedRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStatePointToPoint.o \
    $O/xMIPv6/src/networklayer/ospfv2/interface/OSPFInterfaceStateWaiting.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/DatabaseDescriptionHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/HelloHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateAcknowledgementHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateRequestHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/LinkStateUpdateHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/messagehandler/MessageHandler.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighbor.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborState.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateAttempt.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateDown.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchange.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateExchangeStart.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateFull.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateInit.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateLoading.o \
    $O/xMIPv6/src/networklayer/ospfv2/neighbor/OSPFNeighborStateTwoWay.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/ASExternalLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/NetworkLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/OSPFArea.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/OSPFRouter.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/RouterLSA.o \
    $O/xMIPv6/src/networklayer/ospfv2/router/SummaryLSA.o \
    $O/xMIPv6/src/networklayer/queue/BasicDSCPClassifier.o \
    $O/xMIPv6/src/networklayer/queue/DropTailQoSQueue.o \
    $O/xMIPv6/src/networklayer/queue/DropTailQueue.o \
    $O/xMIPv6/src/networklayer/queue/REDQueue.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVP.o \
    $O/xMIPv6/src/networklayer/rsvp_te/SimpleClassifier.o \
    $O/xMIPv6/src/networklayer/rsvp_te/Utils.o \
    $O/xMIPv6/src/networklayer/ted/LinkStateRouting.o \
    $O/xMIPv6/src/networklayer/ted/TED.o \
    $O/xMIPv6/src/networklayer/xmipv6/BindingCache.o \
    $O/xMIPv6/src/networklayer/xmipv6/BindingUpdateList.o \
    $O/xMIPv6/src/networklayer/xmipv6/MobilityHeader.o \
    $O/xMIPv6/src/networklayer/xmipv6/xMIPv6.o \
    $O/xMIPv6/src/transport/contract/SCTPSocket.o \
    $O/xMIPv6/src/transport/contract/TCPSocket.o \
    $O/xMIPv6/src/transport/contract/TCPSocketMap.o \
    $O/xMIPv6/src/transport/contract/UDPSocket.o \
    $O/xMIPv6/src/transport/rtp/reports.o \
    $O/xMIPv6/src/transport/rtp/RTCP.o \
    $O/xMIPv6/src/transport/rtp/RTCPPacket.o \
    $O/xMIPv6/src/transport/rtp/RTP.o \
    $O/xMIPv6/src/transport/rtp/RTPInnerPacket.o \
    $O/xMIPv6/src/transport/rtp/RTPInterfacePacket.o \
    $O/xMIPv6/src/transport/rtp/RTPPacket.o \
    $O/xMIPv6/src/transport/rtp/RTPParticipantInfo.o \
    $O/xMIPv6/src/transport/rtp/RTPPayloadReceiver.o \
    $O/xMIPv6/src/transport/rtp/RTPPayloadSender.o \
    $O/xMIPv6/src/transport/rtp/RTPProfile.o \
    $O/xMIPv6/src/transport/rtp/RTPReceiverInfo.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderInfo.o \
    $O/xMIPv6/src/transport/rtp/sdes.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfile.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Receiver.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPAVProfilePayload32Sender.o \
    $O/xMIPv6/src/transport/sctp/SCTP.o \
    $O/xMIPv6/src/transport/sctp/SCTPAlg.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationBase.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationEventProc.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationRcvMessage.o \
    $O/xMIPv6/src/transport/sctp/SCTPAssociationUtil.o \
    $O/xMIPv6/src/transport/sctp/SCTPCCFunctions.o \
    $O/xMIPv6/src/transport/sctp/SCTPMessage.o \
    $O/xMIPv6/src/transport/sctp/SCTPQueue.o \
    $O/xMIPv6/src/transport/sctp/SCTPReceiveStream.o \
    $O/xMIPv6/src/transport/sctp/SCTPSendStream.o \
    $O/xMIPv6/src/transport/sctp/SCTPSSFunctions.o \
    $O/xMIPv6/src/transport/tcp/TCP.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionBase.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionEventProc.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionRcvSegment.o \
    $O/xMIPv6/src/transport/tcp/TCPConnectionUtil.o \
    $O/xMIPv6/src/transport/tcp/TCPSACKRexmitQueue.o \
    $O/xMIPv6/src/transport/tcp/TCPSegment.o \
    $O/xMIPv6/src/transport/tcp/flavours/DumbTCP.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPBaseAlg.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPNewReno.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPNoCongestionControl.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPReno.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPTahoe.o \
    $O/xMIPv6/src/transport/tcp/flavours/TCPTahoeRenoFamily.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedRcvQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPMsgBasedSendQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataRcvQueue.o \
    $O/xMIPv6/src/transport/tcp/queues/TCPVirtualDataSendQueue.o \
    $O/xMIPv6/src/transport/tcp_nsc/TCP_NSC.o \
    $O/xMIPv6/src/transport/tcp_nsc/TCP_NSC_Connection.o \
    $O/xMIPv6/src/transport/tcp_nsc/queues/TCP_NSC_VirtualDataQueues.o \
    $O/xMIPv6/src/transport/tcp_old/TCP.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionBase.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionEventProc.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionRcvSegment.o \
    $O/xMIPv6/src/transport/tcp_old/TCPConnectionUtil.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/DumbTCP.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPBaseAlg.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPNoCongestionControl.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPReno.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoe.o \
    $O/xMIPv6/src/transport/tcp_old/flavours/TCPTahoeRenoFamily.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedRcvQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPMsgBasedSendQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataRcvQueue.o \
    $O/xMIPv6/src/transport/tcp_old/queues/TCPVirtualDataSendQueue.o \
    $O/xMIPv6/src/transport/udp/UDP.o \
    $O/xMIPv6/src/util/common.o \
    $O/xMIPv6/src/util/NAMTraceWriter.o \
    $O/xMIPv6/src/util/opp_utils.o \
    $O/xMIPv6/src/util/TCPDump.o \
    $O/xMIPv6/src/util/ThruputMeteringChannel.o \
    $O/xMIPv6/src/util/XMLUtils.o \
    $O/xMIPv6/src/util/headerserializers/ICMPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/IPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/SCTPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/TCPIPchecksum.o \
    $O/xMIPv6/src/util/headerserializers/TCPSerializer.o \
    $O/xMIPv6/src/util/headerserializers/UDPSerializer.o \
    $O/xMIPv6/src/world/ChannelAccess.o \
    $O/xMIPv6/src/world/ChannelControl.o \
    $O/xMIPv6/src/world/ChannelInstaller.o \
    $O/xMIPv6/src/world/NAMTrace.o \
    $O/xMIPv6/src/world/ScenarioManager.o \
    $O/util/mih_m.o \
    $O/wimax/wmaxmsg_m.o \
    $O/xMIPv6/src/applications/ethernet/EtherApp_m.o \
    $O/xMIPv6/src/applications/pingapp/PingPayload_m.o \
    $O/xMIPv6/src/applications/tcpapp/GenericAppMsg_m.o \
    $O/xMIPv6/src/applications/udpapp/UDPEchoAppMsg_m.o \
    $O/xMIPv6/src/base/ByteArrayMessage_m.o \
    $O/xMIPv6/src/linklayer/contract/Ieee802Ctrl_m.o \
    $O/xMIPv6/src/linklayer/contract/PhyControlInfo_m.o \
    $O/xMIPv6/src/linklayer/ethernet/EtherFrame_m.o \
    $O/xMIPv6/src/linklayer/ext/ExtFrame_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames_m.o \
    $O/xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives_m.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt_m.o \
    $O/xMIPv6/src/linklayer/mf80211/macLayer/MacPkt_m.o \
    $O/xMIPv6/src/linklayer/mfcore/AirFrame_m.o \
    $O/xMIPv6/src/linklayer/mfcore/SnrControlInfo_m.o \
    $O/xMIPv6/src/linklayer/mfcore/TransmComplete_m.o \
    $O/xMIPv6/src/linklayer/ppp/PPPFrame_m.o \
    $O/xMIPv6/src/networklayer/arp/ARPPacket_m.o \
    $O/xMIPv6/src/networklayer/contract/IPControlInfo_m.o \
    $O/xMIPv6/src/networklayer/contract/IPProtocolId_m.o \
    $O/xMIPv6/src/networklayer/contract/IPv6ControlInfo_m.o \
    $O/xMIPv6/src/networklayer/icmpv6/ICMPv6Message_m.o \
    $O/xMIPv6/src/networklayer/icmpv6/IPv6NDMessage_m.o \
    $O/xMIPv6/src/networklayer/ipv4/ControlManetRouting_m.o \
    $O/xMIPv6/src/networklayer/ipv4/ICMPMessage_m.o \
    $O/xMIPv6/src/networklayer/ipv4/IPDatagram_m.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6Datagram_m.o \
    $O/xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders_m.o \
    $O/xMIPv6/src/networklayer/ldp/LDPPacket_m.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFPacket_m.o \
    $O/xMIPv6/src/networklayer/ospfv2/OSPFTimer_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/IntServ_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPHello_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPPacket_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg_m.o \
    $O/xMIPv6/src/networklayer/rsvp_te/SignallingMsg_m.o \
    $O/xMIPv6/src/networklayer/ted/LinkStatePacket_m.o \
    $O/xMIPv6/src/networklayer/ted/TED_m.o \
    $O/xMIPv6/src/networklayer/xmipv6/MobilityHeader_m.o \
    $O/xMIPv6/src/transport/contract/SCTPCommand_m.o \
    $O/xMIPv6/src/transport/contract/TCPCommand_m.o \
    $O/xMIPv6/src/transport/contract/UDPControlInfo_m.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderControlMessage_m.o \
    $O/xMIPv6/src/transport/rtp/RTPSenderStatusMessage_m.o \
    $O/xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket_m.o \
    $O/xMIPv6/src/transport/sctp/SCTPMessage_m.o \
    $O/xMIPv6/src/transport/tcp/TCPSegment_m.o \
    $O/xMIPv6/src/transport/udp/UDPPacket_m.o

# Message files
MSGFILES = \
    util/mih.msg \
    wimax/wmaxmsg.msg \
    xMIPv6/src/applications/ethernet/EtherApp.msg \
    xMIPv6/src/applications/pingapp/PingPayload.msg \
    xMIPv6/src/applications/tcpapp/GenericAppMsg.msg \
    xMIPv6/src/applications/udpapp/UDPEchoAppMsg.msg \
    xMIPv6/src/base/ByteArrayMessage.msg \
    xMIPv6/src/linklayer/contract/Ieee802Ctrl.msg \
    xMIPv6/src/linklayer/contract/PhyControlInfo.msg \
    xMIPv6/src/linklayer/ethernet/EtherFrame.msg \
    xMIPv6/src/linklayer/ext/ExtFrame.msg \
    xMIPv6/src/linklayer/ieee80211/mac/Ieee80211Frame.msg \
    xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211MgmtFrames.msg \
    xMIPv6/src/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg \
    xMIPv6/src/linklayer/mf80211/macLayer/Mac80211Pkt.msg \
    xMIPv6/src/linklayer/mf80211/macLayer/MacPkt.msg \
    xMIPv6/src/linklayer/mfcore/AirFrame.msg \
    xMIPv6/src/linklayer/mfcore/SnrControlInfo.msg \
    xMIPv6/src/linklayer/mfcore/TransmComplete.msg \
    xMIPv6/src/linklayer/ppp/PPPFrame.msg \
    xMIPv6/src/networklayer/arp/ARPPacket.msg \
    xMIPv6/src/networklayer/contract/IPControlInfo.msg \
    xMIPv6/src/networklayer/contract/IPProtocolId.msg \
    xMIPv6/src/networklayer/contract/IPv6ControlInfo.msg \
    xMIPv6/src/networklayer/icmpv6/ICMPv6Message.msg \
    xMIPv6/src/networklayer/icmpv6/IPv6NDMessage.msg \
    xMIPv6/src/networklayer/ipv4/ControlManetRouting.msg \
    xMIPv6/src/networklayer/ipv4/ICMPMessage.msg \
    xMIPv6/src/networklayer/ipv4/IPDatagram.msg \
    xMIPv6/src/networklayer/ipv6/IPv6Datagram.msg \
    xMIPv6/src/networklayer/ipv6/IPv6ExtensionHeaders.msg \
    xMIPv6/src/networklayer/ldp/LDPPacket.msg \
    xMIPv6/src/networklayer/ospfv2/OSPFPacket.msg \
    xMIPv6/src/networklayer/ospfv2/OSPFTimer.msg \
    xMIPv6/src/networklayer/rsvp_te/IntServ.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPHello.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPPacket.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPPathMsg.msg \
    xMIPv6/src/networklayer/rsvp_te/RSVPResvMsg.msg \
    xMIPv6/src/networklayer/rsvp_te/SignallingMsg.msg \
    xMIPv6/src/networklayer/ted/LinkStatePacket.msg \
    xMIPv6/src/networklayer/ted/TED.msg \
    xMIPv6/src/networklayer/xmipv6/MobilityHeader.msg \
    xMIPv6/src/transport/contract/SCTPCommand.msg \
    xMIPv6/src/transport/contract/TCPCommand.msg \
    xMIPv6/src/transport/contract/UDPControlInfo.msg \
    xMIPv6/src/transport/rtp/RTPSenderControlMessage.msg \
    xMIPv6/src/transport/rtp/RTPSenderStatusMessage.msg \
    xMIPv6/src/transport/rtp/profiles/avprofile/RTPMpegPacket.msg \
    xMIPv6/src/transport/sctp/SCTPMessage.msg \
    xMIPv6/src/transport/tcp/TCPSegment.msg \
    xMIPv6/src/transport/udp/UDPPacket.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
CONFIGFILE = $(shell opp_configfilepath)
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = $(OPPMAIN_LIB) $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) $(IMPORT_DEFINES)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE (if COPTS has changed since last build)
# and make the object files depend on it
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
  $(shell $(MKPATH) "$O")
  $(file >$(COPTS_FILE),$(COPTS))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
-include makefrag

#------------------------------------------------------------------------------

# Main target
all: $(TARGET_FILES)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clang-msabi)
	-$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib) 2>/dev/null
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)echo >.tmp$$$$ $(OBJS) $(EXTRA_OBJS) && $(AR) .tmplib$$$$ @.tmp$$$$ && $(CXX) -o $O/$(TARGET) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) .tmplib$$$$ $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS) && rm .tmp$$$$ && rm .tmplib$$$$

.PHONY: all clean cleanall depend msgheaders smheaders

# disabling all implicit rules
.SUFFIXES :
.PRECIOUS : %_m.h %_m.cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_FILES)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(CLEANALL_COMMAND)
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

help:
	@echo "$$HELP_SYNOPSYS"
	@echo "$$HELP_TARGETS"
	@echo "$$HELP_VARIABLES"
	@echo "$$HELP_EXAMPLES"

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
