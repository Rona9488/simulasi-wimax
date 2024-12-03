#ifndef __INET_RSVPPACKET_H
#define __INET_RSVPPACKET_H

#include "RSVPPacket_m.h"

#define RSVP_TRAFFIC        2

/**
 * RSVP message common part.
 *
 * This class adds convenience get() and set() methods to the generated
 * base class, but no extra data.
 */
class RSVPPacket : public RSVPPacket_Base
{
  public:
    // Menambahkan variabel rsvpKind_var
    short rsvpKind_var; // Menyimpan jenis RSVP

    // Konstruktor
    RSVPPacket(const char *name=NULL, short kind=0) : RSVPPacket_Base(name, RSVP_TRAFFIC) {
        this->rsvpKind_var = kind;  // Set nilai jenis RSVP
    }

    RSVPPacket(const RSVPPacket& other) : RSVPPacket_Base(other.getName()) {
        operator=(other);
    }

    RSVPPacket& operator=(const RSVPPacket& other) {
        RSVPPacket_Base::operator=(other);
        this->rsvpKind_var = other.rsvpKind_var; // Menyalin nilai rsvpKind_var
        return *this;
    }

    virtual RSVPPacket *dup() const { return new RSVPPacket(*this); }

    inline IPAddress getDestAddress() { return getSession().DestAddress; }
    inline int getTunnelId() { return getSession().Tunnel_Id; }
    inline int getExTunnelId() { return getSession().Extended_Tunnel_Id; }
    inline int getSetupPri() { return getSession().setupPri; }
    inline int getHoldingPri() { return getSession().holdingPri; }
    inline bool isInSession(SessionObj_t* s) {
        return getSession().DestAddress == s->DestAddress &&
               getSession().Tunnel_Id == s->Tunnel_Id &&
               getSession().Extended_Tunnel_Id == s->Extended_Tunnel_Id;
    }
};

#endif
