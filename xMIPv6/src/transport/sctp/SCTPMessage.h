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
//
//#ifndef _SCTPMESSAGE_H_
//#define _SCTPMESSAGE_H_
//
//#include <list>
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\networklayer\queue\DropTailQoSQueue.h"
//#include "C:\Users\ronaa\Downloads\numbat-master (2)\numbat-master\numbat-master\xMIPv6\src\transport\sctp\SCTPMessage_m.h"
//
///**
// * Represents a SCTP Message. More info in the SCTPMessage.msg file
// * (and the documentation generated from it).
// */
//class SCTPMessage : public SCTPMessage_Base
//{
//	protected:
//		std::list<inet::cPacket*> chunkList;
//
//	public:
//		SCTPMessage(const char *name=NULL, int32_t kind=0) : SCTPMessage_Base(name,kind) {}
//		SCTPMessage(const SCTPMessage& other) : SCTPMessage_Base(other.getName()) {operator=(other);}
//		~SCTPMessage();
//		SCTPMessage& operator=(const SCTPMessage& other);
//		virtual SCTPMessage *dup() const {return new SCTPMessage(*this);}
//		/** Generated but unused method, should not be called. */
//		virtual void setChunksArraySize(uint32_t size);
//		/** Generated but unused method, should not be called. */
//		virtual void setChunks(uint32_t k, const cPacketPtr& chunks_var);
//		/**
//		* Returns the number of chunks in this SCTP packet
//		*/
//		virtual uint32_t getChunksArraySize() const;
//
//		/**
//		* Returns the kth chunk in this SCTP packet
//		*/
//		virtual cPacketPtr& getChunks(uint32_t k);
//		/**
//		* Adds a message object to the SCTP packet. The packet length will be adjusted
//		*/
//		virtual void addChunk(inet::cPacket* msg);
//
//		/**
//		* Removes and returns the first message object in this SCTP packet.
//		*/
//		virtual inet::cPacket *removeChunk();
//		virtual inet::cPacket *removeLastChunk();
//		virtual inet::cPacket *peekFirstChunk();
//		virtual inet::cPacket *peekLastChunk();
//		/**
//		 * Serializes SCTP packet for transmission on the wire,
//		 * writes source port into from structure and
//		 * returns length of sctp data written into buffer
//		 */
//
//
//};
//
//
//class SCTPErrorChunk : public SCTPErrorChunk_Base
//{
//	protected:
//		std::list<inet::cPacket*> parameterList;
//
//	public:
//	    	SCTPErrorChunk(const char *name=NULL, int32_t kind=0) : SCTPErrorChunk_Base(name, kind) {};
//    		SCTPErrorChunk(const SCTPErrorChunk& other) : SCTPErrorChunk_Base(other.getName()) {operator=(other);};
//		SCTPErrorChunk& operator=(const SCTPErrorChunk& other);
//
//		virtual SCTPErrorChunk *dup() const {return new SCTPErrorChunk(*this);}
//		virtual void setParametersArraySize(uint32_t size);
//    		virtual uint32_t getParametersArraySize() const;
//				/** Generated but unused method, should not be called. */
//		virtual void setParameters(uint32_t k, const cPacketPtr& parameters_var);
//
//				/**
//		* Returns the kth parameter in this SCTP Reset Chunk
//		*/
//		virtual cPacketPtr& getParameters(uint32_t k);
//	/**
//		* Adds a message object to the SCTP packet. The packet length will be adjusted
//		*/
//		virtual void addParameters(inet::cPacket* msg);
//
//		/**
//		* Removes and returns the first message object in this SCTP packet.
//		*/
//		virtual inet::cPacket *removeParameter();
//};
//#endif
//
//
