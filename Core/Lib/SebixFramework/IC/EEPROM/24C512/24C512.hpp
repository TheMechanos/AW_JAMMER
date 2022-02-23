/*
 * MemoryManager.hpp
 *
 *  Created on: 22.12.2019
 *      Author: SHON
 */

#ifndef IC_24C512_HPP_
#define IC_24C512_HPP_

#include <Generic/GenericEEPROM.hpp>
#include <Interfaces/I2C/I2C.hpp>
#include <stdio.h>
#include <string.h>



class IC_24C512: public EEPROM_GENERIC{
public:
	IC_24C512()=default;
	IC_24C512(I2C * i2c, uint8_t eepromI2CAddress);


	bool init();
	bool read(int startaddr, int len, uint8_t * data);
	bool write(int startaddr, int len, uint8_t * data);
	bool format(int startaddr, int len);
	bool formatAll();
	uint32_t getMemoryByteSize();




private:

	uint8_t eepromI2CAddress;
	I2C * i2cInterface;

	uint32_t lastMemoryOperation;

	HAL_StatusTypeDef memWriteWithTiming(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	HAL_StatusTypeDef memReadWithTiming(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

	static const uint32_t MEMORYSIZE=64000;
	static const uint16_t MEMORYPAGESIEZE=128;
	static const uint16_t I2CTIMEOUT = 10;
	static const uint16_t I2CWRITETIME = 12;

};


#endif /* LOWLEVEL_EEPROM_EEPROMMANAGER_HPP_ */
