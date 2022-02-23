/*
 * MemoryManager.hpp
 *
 *  Created on: 22.12.2019
 *      Author: SHON
 */

#ifndef GENERIC_EEPROM_HPP_
#define GENERIC_EEPROM_HPP_

#include <stdio.h>


class EEPROM_GENERIC{

public:
	virtual ~EEPROM_GENERIC(){};

	virtual bool init()=0;
	virtual bool read(int startaddr, int len, uint8_t * data)=0;
	virtual bool write(int startaddr, int len, uint8_t * data)=0;
	virtual bool format(int startaddr, int len)=0;
	virtual bool formatAll()=0;

	virtual uint32_t getMemoryByteSize()=0;

private:


};


#endif /* LOWLEVEL_EEPROM_EEPROMMANAGER_HPP_ */
