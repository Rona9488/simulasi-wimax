//
// Copyright (C) 2005 Michael Tuexen
//               2008 Irene Ruengeler
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

#ifndef __TCPDUMP_H
#define __TCPDUMP_H

#include <omnetpp.h>
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\contract\IPAddress.h"
//#include "IPDatagram_m.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv4\IPDatagram.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\transport\sctp\SCTPMessage.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\transport\tcp\TCPSegment.h"
#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\ipv6\IPv6Datagram_m.h"

#define PCAP_MAGIC          0xa1b2c3d4

/* "libpcap" file header (minus magic number). */
struct pcap_hdr {
    uint32_t  magic;      /* magic */
    uint16_t  version_major;  /* major version number */
    uint16_t  version_minor;  /* minor version number */
    uint32_t  thiszone;   /* GMT to local correction */
    uint32_t  sigfigs;    /* accuracy of timestamps */
    uint32_t  snaplen;    /* max length of captured packets, in octets */
    uint32_t  network;    /* data link type */
};

/* "libpcap" record header. */
struct pcaprec_hdr {
    int32_t   ts_sec;     /* timestamp seconds */
    uint32_t  ts_usec;    /* timestamp microseconds */
    uint32_t  incl_len;   /* number of octets of packet saved in file */
    uint32_t  orig_len;   /* actual length of packet */
};

typedef struct {
    uint  dest_addr[6];
    uint  src_addr[6];
    uint16_t l3pid;
} hdr_ethernet_t;

static hdr_ethernet_t HDR_ETHERNET = {
    {0x02, 0x02, 0x02, 0x02, 0x02, 0x02},
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
    0};

/**
 * Dumps SCTP packets in tcpdump format.
 */
class TCPDumper
{
    protected:
        int32_t seq;
        std::ostream *outp;
    public:
        TCPDumper(std::ostream& o);
        ~TCPDumper();
        void ipDump(const char *label, IPDatagram *dgram, const char *comment=NULL);
//        void sctpDump(const char *label, SCTPMessage *sctpmsg, const std::string& srcAddr, const std::string& destAddr, const char *comment=NULL);
        void dump(const char *label, const char *msg);
        void tcpDump(bool l2r, const char *label, IPDatagram *dgram, const char *comment=NULL);
        void tcpDump(bool l2r, const char *label, TCPSegment *tcpseg, const std::string& srcAddr, const std::string& destAddr, const char *comment=NULL);
        void dumpIPv6(bool l2r, const char *label, IPv6Datagram_Base *dgram, const char *comment=NULL);//FIXME: Temporary hack
        void udpDump(bool l2r, const char *label, IPDatagram *dgram, const char *comment);
        const char *intToChunk(int32_t type);
        FILE *dumpfile;
};


/**
 * Dumps every packet using the TCPDumper class
 */
class TCPDump : public inet::cSimpleModule
{
    protected:
        TCPDumper tcpdump;
    public:
        TCPDump();
        ~TCPDump();
        TCPDump(const char *name, cModule *parent);
        virtual void handleMessage(inet::cMessage *msg);
        virtual void initialize();
        virtual void finish();
};

#endif


