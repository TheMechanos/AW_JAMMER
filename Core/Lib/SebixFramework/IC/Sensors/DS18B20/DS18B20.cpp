/*
 * DS18B20.cpp
 *
 *  Created on: 3 lis 2021
 *      Author: skocz
 */


#include "DS18B20.hpp"


DS18B20Rom::DS18B20Rom(){
	for(uint8_t q = 0; q < 8; q++){
		this->rom[q] = 0;
	}
}

DS18B20Rom::DS18B20Rom(uint8_t *rom){
	setRom(rom);
}

void DS18B20Rom::setRom(uint8_t *rom){
	for(uint8_t q = 0; q < 8; q++){
		this->rom[q] = *(rom++);
	}
}

uint8_t* DS18B20Rom::getRom(){
	return rom;
}




constexpr const uint16_t DS18B20::ResolutionConversionTime[4];
constexpr const uint16_t DS18B20::ResolutionDivider[4];
constexpr const uint16_t DS18B20::ResolutionMask[4];

DS18B20::DS18B20(OneWire *oneWire, uint32_t measureInterval, uint32_t transmisionErrorTolerance){
	this->oneWire = oneWire;
	this->measureInterval = measureInterval;
	this->transmisionErrorTolerance = transmisionErrorTolerance;

	this->status = Status::INVALID;

	this->transmisionError = 0;
	this->lastMeasure = 0;
	this->converting = false;

	conversionTime = 750;
	this->resolution = Resolution::B12;

	this->romDefined = false;

}

/*void DS18B20::defineResolution(Resolution res){
	this->resolution = res;
}*/

void DS18B20::init(){
	romDefined = false;

	if(measureInterval < conversionTime){
		measureInterval = conversionTime + 50;
	}

	lastMeasure = System::getTick() + 1000;
}

void DS18B20::init(DS18B20Rom rom){
	this->rom = rom;

	sendSetResolution();
	calculateConversionTime();
	init();

	romDefined = true;
}

void DS18B20::calculateConversionTime(){
	conversionTime = ResolutionConversionTime[(uint8_t)resolution];
}

void DS18B20::iterate(uint32_t TICK){
	if(!romDefined)return;

	if(TICK - lastMeasure - conversionTime > measureInterval && converting == false){
		startMeasure();
		converting = true;

	}else if(TICK - lastMeasure > measureInterval){
		converting = false;
		lastMeasure = TICK;
		bool valid = readMeasure();

		if(!valid){
			transmisionError++;
			if(transmisionError > transmisionErrorTolerance){
				temperature.set(0, 0);
				status = Status::ERROR;
			}else{
				status = Status::INVALID;
			}
		}else{
			transmisionError = 0;
			status = Status::OK;
		}
	}

}

void DS18B20::startMeasure(){
	oneWire->writeCommand(DS18B20_CONVERT_T, rom.getRom());
}

bool DS18B20::readMeasure(){
	uint8_t sp[DS18B20_SCRATCHPAD_SIZE];

	if(!readScratchPad(sp)){
		return false;
	}

	int32_t tempData=0;
	memcpy(&tempData, &sp[0], 2);

	bool negative = false;
	if(tempData & 0x8000){
		negative = true;
	}

	tempData &= ResolutionMask[(uint8_t)resolution];

	int32_t temp;
	if(negative){
		tempData ^= 0xFFFF;
		tempData++;
		temp = tempData * (-1);

	}else{
		temp = tempData;
	}

	int16_t w = (temp * 10) / ResolutionDivider[(uint8_t)resolution];

	if(negative){
		this->temperature.set(w/10, (w*(-1))%10);
	}else{
		this->temperature.set(w/10, w%10);
	}

	return true;
}

void DS18B20::sendSetResolution(){
	uint8_t sp[DS18B20_SCRATCHPAD_SIZE];
	readScratchPad(sp);

	sp[4] = (((uint8_t)resolution) << 5) | 0x1F;

	writeScratchPad(sp);
}

bool DS18B20::readScratchPad(uint8_t *sp){
	oneWire->writeCommand(DS18B20_READ_SCRATCHPAD, rom.getRom());
	oneWire->readBytes(sp, DS18B20_SCRATCHPAD_SIZE);

	if(wire_crc(sp, 8) != sp[8]){
		return false;
	}
	return true;
}

void DS18B20::writeScratchPad(uint8_t *sp){
	oneWire->writeCommand(DS18B20_WRITE_SCRATCHPAD, rom.getRom());
	oneWire->writeBytes(&sp[2], 3);
}

uint8_t DS18B20::wire_crc(const uint8_t *data, int len){
	int i;
	uint8_t crc = 0;

	for(i = 0; i < len; i++)
		crc = byte_crc(crc, data[i]);

	return crc;
}

uint8_t DS18B20::byte_crc(uint8_t crc, uint8_t byte){
	int i;
	for(i = 0; i < 8; i++){
		uint8_t b = crc ^ byte;
		crc >>= 1;
		if(b & 0x01)
			crc ^= 0x8c;
		byte >>= 1;
	}
	return crc;
}


uint8_t DS18B20Finder::searchSensors(DS18B20Rom *romTable, uint8_t maxSensors, OneWire *oneWire){
	uint8_t id[ONEWIRE_ROMCODE_SIZE];
	uint8_t diff, nSensors;

	nSensors = 0;

	for(diff = ONEWIRE_SEARCH_FIRST; diff != ONEWIRE_SEARCH_LAST && nSensors < maxSensors;){ //10 =MAX
		searchSensor(&diff, &id[0], oneWire);

		if(diff == OneWire::SEARCH_PRESENCE_ERROR){
			break;
		}

		if(diff == OneWire::SEARCH_DATA_ERROR){
			break;
		}

		romTable[nSensors].setRom(id);

		nSensors++;
	}

	return nSensors;
}

void DS18B20Finder::searchSensor(uint8_t *diff, uint8_t *id, OneWire *oneWire){
	for(;;){
		*diff = oneWire->romSearch(*diff, &id[0]);
		if(*diff == OneWire::SEARCH_PRESENCE_ERROR || *diff == OneWire::SEARCH_DATA_ERROR || *diff == ONEWIRE_SEARCH_LAST)
			return;
		if(id[0] == DS18B20_ID || id[0] == DS18S20_ID)
			return;
	}
}
