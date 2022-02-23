/*
 * Packet.hpp
 *
 *  Created on: 15 gru 2021
 *      Author: user
 */

#ifndef SRC_SX1262_PACKET_HPP_
#define SRC_SX1262_PACKET_HPP_

#include <System.hpp>
#include "RawPacket.hpp"
#include <stdio.h>
#include <string.h>


class SKMPacketStatus{
public:
	SKMPacketStatus(){
		id=0;
		status = Status::None;
	}
	SKMPacketStatus(uint16_t id){
		this->id = id;
		status = Status::None;
	}

	enum class Status{
		None, InTxQueue,Transmitting, Transmitted, Acknowledged, Timeouted, TxFail
	};
	Status status;

	uint16_t id;

	uint32_t sendedTime;
};

class SKMPacket : public SKMRawPacket {
public:

	void setDataSize(uint8_t dataSize){
		this->size = dataSize + SizeHeader;
	}
	void setTotalSize(uint8_t size){
		this->size = size;
	}

	void clear(){
		memset(idx, 0x00, getPacketMaxLength());
	}

	uint8_t getPacketMaxLength(){
		return SizeHeader + SizeDataMax;
	}
	uint8_t getTotalSize(){
		return size;
	}
	uint8_t getDataSize(){
		return size - SizeHeader;
	}

	uint8_t& operator[](size_t el){
		return dataIdx[el];
	}
	const uint8_t& operator[](size_t el) const{
		return dataIdx[el];
	}



private:
	uint8_t size;

};



#endif /* SRC_SX1262_PACKET_HPP_ */
