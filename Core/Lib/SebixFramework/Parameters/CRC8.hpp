/*
 * CRC8.hpp
 *
 *  Created on: 20.02.2020
 *      Author: SHON
 */

#ifndef EEPROM_CRC8_HPP_
#define EEPROM_CRC8_HPP_

#include <stdio.h>

class CRC8{
public:
	static uint8_t generate(uint8_t *data, uint16_t len){
		uint8_t crc = 0xff;
		uint16_t i, j;
		for (i = 0; i < len; i++){
			crc ^= data[i];
			for (j = 0; j < 8; j++){
				if((crc & 0x80) != 0)
					crc = (uint8_t) ((crc << 1) ^ 0x31);
				else
					crc <<= 1;
			}
		}
		return crc;
	}

	static bool check(uint8_t *data, uint16_t len, uint8_t crc){
		uint8_t genCRC = generate(data, len);
		if(crc == genCRC){
			return true;
		}
		return false;
	}
};




#endif /* EEPROM_CRC8_HPP_ */
