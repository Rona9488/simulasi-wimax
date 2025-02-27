/***************************************************************************
                          RTPInnerPacket.cc  -  description
                             -------------------
    begin                : Sat Oct 20 2001
    copyright            : (C) 2001 by Matthias Oppitz
    email                : Matthias.Oppitz@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/** \file RTPInnerPacket.cc
 * This file contains the implementation of member functions
 * of RTPInnerPacket.
 */

#include "RTPInnerPacket.h"
#include "RTPPacket.h"

Register_Class(RTPInnerPacket);


RTPInnerPacket::RTPInnerPacket(const char *name) : inet::cPacket(name)
{
    _type = RTP_INP_UNDEF;
    _commonName = NULL;
    _mtu = 0;
    _bandwidth = 0;
    _rtcpPercentage = 0;
    _address = IPAddress::UNSPECIFIED_ADDRESS;
    _port = PORT_UNDEF;
    _ssrc = 0;
    _payloadType = 0;
    _fileName = NULL;
    _clockRate = 0;
    _timeStampBase = 0;
    _sequenceNumberBase = 0;
}


RTPInnerPacket::RTPInnerPacket(const RTPInnerPacket& rinp) : inet::cPacket()
{
    setName(rinp.getName());
    operator=(rinp);
}


RTPInnerPacket::~RTPInnerPacket()
{
    if (inet::opp_strcmp(_commonName, ""))
        delete _commonName;
    if (inet::opp_strcmp(_fileName, ""))
        delete _fileName;
}


RTPInnerPacket& RTPInnerPacket::operator=(const RTPInnerPacket& rinp)
{
    inet::cPacket::operator=(rinp);
    _type = rinp._type;
    _commonName = inet::opp_strdup(rinp._commonName);
    _mtu = rinp._mtu;
    _bandwidth = rinp._bandwidth;
    _rtcpPercentage = rinp._rtcpPercentage;
    _address = rinp._address;
    _port = rinp._port;
    _ssrc = rinp._ssrc;
    _payloadType = rinp._payloadType;
    _fileName = inet::opp_strdup(rinp._fileName);
    _clockRate = rinp._clockRate;
    _timeStampBase = rinp._timeStampBase;
    _sequenceNumberBase = rinp._sequenceNumberBase;
    return *this;
}


RTPInnerPacket *RTPInnerPacket::dup() const
{
    return new RTPInnerPacket(*this);
}


std::string RTPInnerPacket::info()
{
    std::stringstream out;
    out << "RTPInnerPacket: type=" << _type;
    return out.str();
}


void RTPInnerPacket::dump(std::ostream& os) const
{
    os << "RTPInnerPacket:" << std::endl;
    os << "  type = " << _type << std::endl;
    os << "  commonName = " << _commonName << std::endl;
    os << "  mtu = " << _mtu << std::endl;
    os << "  bandwidth = " << _bandwidth << std::endl;
    os << "  rtcpPercentage = " << _rtcpPercentage << std::endl;
    os << "  address = " << _address << std::endl;
    os << "  port = " << _port << std::endl;
    os << "  ssrc = " << _ssrc << std::endl;
    os << "  payloadType = " << _payloadType << std::endl;
    os << "  fileName = " << _fileName << std::endl;
    os << "  clockRate = " << _clockRate << std::endl;
    os << "  timeStampBase = " << _timeStampBase << std::endl;
    os << "  sequenceNumberBase = " << _sequenceNumberBase << std::endl;
}


void RTPInnerPacket::initializeProfile(int mtu)
{
    _type = RTP_INP_INITIALIZE_PROFILE;
    _mtu = mtu;
}


void RTPInnerPacket::profileInitialized(int rtcpPercentage, int port)
{
    _type = RTP_INP_PROFILE_INITIALIZED;
    _rtcpPercentage = rtcpPercentage;
    _port = port;
}


void RTPInnerPacket::initializeRTCP(const char *commonName, int mtu, int bandwidth, int rtcpPercentage, IPAddress address, int port)
{
    _type = RTP_INP_INITIALIZE_RTCP;
    _commonName = commonName;
    _mtu = mtu;
    _bandwidth = bandwidth;
    _rtcpPercentage = rtcpPercentage;
    _address = address;
    _port = port;
}


void RTPInnerPacket::rtcpInitialized(uint32_t ssrc)
{
    _type = RTP_INP_RTCP_INITIALIZED;
    _ssrc = ssrc;
}


void RTPInnerPacket::createSenderModule(uint32_t ssrc, int payloadType, const char *fileName)
{
    _type = RTP_INP_CREATE_SENDER_MODULE;
    _ssrc = ssrc;
    _payloadType = payloadType;
    _fileName = fileName;
}


void RTPInnerPacket::senderModuleCreated(uint32_t ssrc)
{
    _type = RTP_INP_SENDER_MODULE_CREATED;
    _ssrc = ssrc;
}


void RTPInnerPacket::deleteSenderModule(uint32_t ssrc)
{
    _type = RTP_INP_DELETE_SENDER_MODULE;
    _ssrc = ssrc;
}


void RTPInnerPacket::senderModuleDeleted(uint32_t ssrc)
{
    _type = RTP_INP_SENDER_MODULE_DELETED;
    _ssrc = ssrc;
}


void RTPInnerPacket::initializeSenderModule(uint32_t ssrc, const char *fileName, int mtu)
{
    _type = RTP_INP_INITIALIZE_SENDER_MODULE;
    _ssrc = ssrc;
    _fileName = fileName;
    _mtu = mtu;
}


void RTPInnerPacket::senderModuleInitialized(uint32_t ssrc, int payloadType, int clockRate, int timeStampBase, int sequenceNumberBase)
{
    _type = RTP_INP_SENDER_MODULE_INITIALIZED;
    _ssrc = ssrc;
    _payloadType = payloadType;
    _clockRate = clockRate;
    _timeStampBase = timeStampBase;
    _sequenceNumberBase = sequenceNumberBase;
}

void RTPInnerPacket::senderModuleControl(uint32_t ssrc, RTPSenderControlMessage *msg)
{
    _type = RTP_INP_SENDER_MODULE_CONTROL;
    _ssrc = ssrc;
    encapsulate(msg);
}


void RTPInnerPacket::senderModuleStatus(uint32_t ssrc, RTPSenderStatusMessage *msg)
{
    _type = RTP_INP_SENDER_MODULE_STATUS;
    _ssrc = ssrc;
    encapsulate(msg);
}


void RTPInnerPacket::leaveSession()
{
    _type = RTP_INP_LEAVE_SESSION;
}


void RTPInnerPacket::sessionLeft()
{
    _type = RTP_INP_SESSION_LEFT;
}


void RTPInnerPacket::dataOut(RTPPacket *packet)
{
    _type = RTP_INP_DATA_OUT;
    encapsulate(packet);
}


void RTPInnerPacket::dataIn(RTPPacket *packet, IPAddress address, int port)
{
    _type = RTP_INP_DATA_IN;
    _address = address;
    _port = port;
    encapsulate(packet);
}


RTPInnerPacket::RTP_INP_TYPE RTPInnerPacket::getType()
{
    return _type;
}


const char *RTPInnerPacket::getCommonName()
{
    return inet::opp_strdup(_commonName);
}


int RTPInnerPacket::getMTU()
{
    return _mtu;
}


int RTPInnerPacket::getBandwidth()
{
    return _bandwidth;
}


int RTPInnerPacket::getRtcpPercentage()
{
    return _rtcpPercentage;
}


IPAddress RTPInnerPacket::getAddress()
{
    return _address;
}


int RTPInnerPacket::getPort()
{
    return _port;
}


uint32_t RTPInnerPacket::getSSRC()
{
    return _ssrc;
}


const char *RTPInnerPacket::getFileName()
{
    return inet::opp_strdup(_fileName);
}


int RTPInnerPacket::getPayloadType()
{
    return _payloadType;
}


int RTPInnerPacket::getClockRate()
{
    return _clockRate;
}


int RTPInnerPacket::getTimeStampBase()
{
    return _timeStampBase;
}


int RTPInnerPacket::getSequenceNumberBase()
{
    return _sequenceNumberBase;
}
