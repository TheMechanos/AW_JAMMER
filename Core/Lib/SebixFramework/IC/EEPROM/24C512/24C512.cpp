/*
 * MemoryManager.cpp
 *
 *  Created on: 22.12.2019
 *      Author: SHON
 */
#include "24C512.hpp"

IC_24C512::IC_24C512(I2C * i2c, uint8_t eepromI2CAddress){
	this->eepromI2CAddress = eepromI2CAddress;
	this->i2cInterface = i2c;
	this->lastMemoryOperation=0;
}

bool IC_24C512::init(){

	return true;
}
uint32_t IC_24C512::getMemoryByteSize(){
	return MEMORYSIZE;
}

bool IC_24C512::read(int startaddr, int len, uint8_t * data){
	/*int endaddr = startaddr + len; //koniec danych
	int startpage = startaddr / 128; //strona startowa
	int endpage = endaddr / 128; //strona koncowa

	int startpos = startaddr % 128;
	int endpos = endaddr % 128;

	int page = startpage;

	HAL_StatusTypeDef status;

	if(startpage == endpage){
		status = memReadWithTiming(eepromI2CAddress + 1, (startpage << 7) + startpos, 2, (uint8_t*) data, len, IC_24C512::I2CTIMEOUT);
		return status;
	}

	status = memReadWithTiming(eepromI2CAddress + 1, (startpage << 7) + startpos, 2, (uint8_t*) data, 128 - startpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return status;
	data += 128 - startpos;
	page++;

	while(page < endpage){
		status = memReadWithTiming(eepromI2CAddress + 1, (page << 7), 2, (uint8_t*) data, 128, IC_24C512::I2CTIMEOUT);
		if(status != HAL_OK)
			return status;

		data += 128;
		page++;
	}

	status = i2cInterface->memRead(eepromI2CAddress + 1, (page << 7), 2, (uint8_t*) data, endpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return status;

	return HAL_OK;
	*/

	return HAL_OK == memReadWithTiming(eepromI2CAddress + 1, startaddr, 2, (uint8_t*) data, len, IC_24C512::I2CTIMEOUT);
}

bool IC_24C512::write(int startaddr, int len, uint8_t * data){
	int endaddr = startaddr + len; //koniec danych
	int startpage = startaddr / 128; //strona startowa
	int endpage = endaddr / 128; //strona koncowa

	int startpos = startaddr % 128;
	int endpos = endaddr % 128;

	int page = startpage;

	HAL_StatusTypeDef status;

	if(startpage == endpage){
		status = memWriteWithTiming(eepromI2CAddress, (startpage << 7) + startpos, 2, (uint8_t*) data, len, IC_24C512::I2CTIMEOUT);
		return status == HAL_OK;
	}

	status = memWriteWithTiming(eepromI2CAddress, (startpage << 7) + startpos, 2, (uint8_t*) data, 128 - startpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return false;
	data += 128 - startpos;
	page++;

	while(page < endpage){
		status = memWriteWithTiming(eepromI2CAddress, (page << 7), 2, (uint8_t*) data, 128, IC_24C512::I2CTIMEOUT);
		if(status != HAL_OK)
			return false;
		data += 128;
		page++;
	}

	status = memWriteWithTiming(eepromI2CAddress, (page << 7), 2, (uint8_t*) data, endpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return false;

	return true;
}

bool IC_24C512::format(int startaddr, int len){
	int endaddr = startaddr + len; //koniec danych
	int startpage = startaddr / 128; //strona startowa
	int endpage = endaddr / 128; //strona koncowa

	int startpos = startaddr % 128;
	int endpos = endaddr % 128;

	int page = startpage;

	uint8_t zeros[128];
	for(uint8_t q = 0; q < 128; q++)
		zeros[q] = 0;

	HAL_StatusTypeDef status;

	if(startpage == endpage){
		status = memWriteWithTiming(eepromI2CAddress, (startpage << 7) + startpos, 2, zeros, len, IC_24C512::I2CTIMEOUT);
		return status == HAL_OK;
	}

	status = memWriteWithTiming(eepromI2CAddress, (startpage << 7) + startpos, 2, zeros, 128 - startpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return false;
	page++;

	while(page < endpage){
		status = memWriteWithTiming(eepromI2CAddress, (page << 7), 2, zeros, 128, IC_24C512::I2CTIMEOUT);
		if(status != HAL_OK)
			return false;
		page++;
	}

	status = memWriteWithTiming(eepromI2CAddress, (page << 7), 2, zeros, endpos, IC_24C512::I2CTIMEOUT);
	if(status != HAL_OK)
		return false;

	return true;
}

bool IC_24C512::formatAll(){
	uint8_t emptytab[128];
	for(uint8_t w = 0; w < 128; w++)
		emptytab[w] = 0;

	for(int q = 0; q < 512; q++){
		if(memWriteWithTiming(eepromI2CAddress, (q << 7), 2, (uint8_t*) emptytab, 128, IC_24C512::I2CTIMEOUT) != HAL_OK)
			return false;
	}
	return true;
}


HAL_StatusTypeDef IC_24C512::memWriteWithTiming(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout){

	//CHECK REPEATWRITE
	uint8_t data[128];
	memReadWithTiming(DevAddress, MemAddress, MemAddSize, data, Size, Timeout);

	bool forbidSave = true;
	for(uint8_t q=0; q<Size; q++){
		if(data[q] != pData[q]){
			forbidSave = false;
		}
	}
	if(forbidSave)return HAL_OK;
	//END CHECK REPEATWRITE

	uint32_t diff = HAL_GetTick() - lastMemoryOperation;
	if(diff < I2CWRITETIME){
		HAL_Delay(I2CWRITETIME-diff);
	}
	HAL_StatusTypeDef a = i2cInterface->memWrite(DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
	lastMemoryOperation = HAL_GetTick();
	return a;
}

HAL_StatusTypeDef IC_24C512::memReadWithTiming(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout){

	uint32_t diff = HAL_GetTick() - lastMemoryOperation;
	if(diff < I2CWRITETIME){
		HAL_Delay(I2CWRITETIME-diff);
	}
	HAL_StatusTypeDef a = i2cInterface->memRead(DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
	//lastMemoryOperation = HAL_GetTick();
	return a;
}

