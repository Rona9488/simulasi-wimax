/***************************************************************************
                          sdes.h  -  description
                             -------------------
    begin                : Tue Oct 23 2001
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

/** \file sdes.h
 * This file declares the source description classes SDESItem and SDESChunk.
 */

#ifndef __INET_SDES_H
#define __INET_SDES_H

#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\base\INETDefs.h"

/**
 * The class SDESItem is used for storing a source description item
 * (type of description, description string) for an rtp end system.
 */
class INET_API SDESItem : public inet::cObject
{

    public:
        /**
         * This enumeration holds the types of source description items
         * as defined in the rfc. In this implementation only SDES_UNDEF
         * and SDES_CNAME are usable.
         */
        enum SDES_ITEM_TYPE {
            SDES_UNDEF = 0,
            SDES_CNAME = 1,
            SDES_NAME = 2,
            SDES_EMAIL = 3,
            SDES_PHONE = 4,
            SDES_LOC = 5,
            SDES_TOOL = 6,
            SDES_NOTE = 7,
            SDES_PRIV = 8
        };

        /**
         * Default constructor.
         */
        SDESItem();

        /**
         * Constructor which sets the entry.
         */
        SDESItem(SDES_ITEM_TYPE type, const char *content);

        /**
         * Copy constructor.
         */
        SDESItem(const SDESItem& sdesItem);

        /**
         * Destructor.
         */
        virtual ~SDESItem();

        /**
         * Assignment operator.
         */
        SDESItem& operator=(const SDESItem& sdesItem);

        /**
         * Duplicates theis SDESItem by calling the copy constructor.
         */
        virtual SDESItem *dup() const;

        /**
         * Writes a short info about this SDESItem into the given string.
         */
        virtual std::string info();

        /**
         * Writes an info about this SDESItem into the give output stream.
         */
        virtual void dump(std::ostream& os);

        /**
         * Returns the type of this sdes item.
         */
        virtual SDES_ITEM_TYPE getType();

        /**
         * Returns the stored sdes string.
         */
        virtual const char *getContent();

        /**
         * This method returns the size of this SDESItem in bytes as it
         * would be in the real world.
         */
        virtual int getLength();

    protected:

        /**
         * The type of this SDESItem.
         */
        SDES_ITEM_TYPE _type;

        /**
         * The length of this SDESItem.
         */
        int _length;

        /**
         * The sdes string.
         */
        const char *_content;
};


/**
 * The class SDESChunk is used for storing SDESItem objects
 * for one rtp end system.
 */
class INET_API SDESChunk : public inet::cArray
{

    public:
        /**
         * Default constructor.
         */
        SDESChunk(const char *name = NULL, uint32_t ssrc = 0);

        /**
         * Copy constructor.
         */
        SDESChunk(const SDESChunk& sdesChunk);

        /**
         * Destructor.
         */
        virtual ~SDESChunk();

        /**
         * Operator equal.
         */
        SDESChunk& operator=(const SDESChunk& sdesChunk);

        /**
         * Duplicates this SDESChunk by calling the copy constructor.
         */
        virtual SDESChunk *dup() const;

        /**
         * Writes a short info about this SDESChunk into the given string.
         */
        virtual std::string info();

        /**
         * Writes a longer info about this SDESChunk into the given stream.
         */
        virtual void dump(std::ostream& os);

        /**
         * Adds an SDESItem to this SDESChunk. If there is already an SDESItem
         * of the same type in this SDESChunk it is replaced by the new one.
         */
        virtual void addSDESItem(SDESItem *item);

        /**
         * Returns the ssrc identifier this SDESChunk is for.
         */
        virtual uint32_t getSSRC();

        /**
         * Sets the ssrc identifier this SDESChunk is for.
         */
        virtual void setSSRC(uint32_t ssrc);

        /**
         * Returns the length in bytes of this SDESChunk.
         */
        virtual int getLength();

    protected:

        /**
         * The ssrc identifier this SDESChunk is for.
         */
        uint32_t _ssrc;

        /**
         * The length in bytes of this SDESChunk.
         */
        int _length;
};

#endif

