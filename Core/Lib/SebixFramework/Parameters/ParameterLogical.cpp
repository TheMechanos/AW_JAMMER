/*
 * EEPROMParameter.cpp
 *
 *  Created on: 20.02.2020
 *      Author: SHON
 */

#include <Parameters/ParameterLogical.hpp>



PARAMETER_LOGICAL_EEPROM::PARAMETER_LOGICAL_EEPROM():PARAMETER_LOGICAL(){
	EepromDataAddress=0;
	EepromDevice=0;
	loaded=false;
}

PARAMETER_LOGICAL_EEPROM::PARAMETER_LOGICAL_EEPROM(bool def, EEPROM_GENERIC * EepromDevice, uint16_t EepromDataAddress) :
	PARAMETER_LOGICAL(def) {

	this->EepromDataAddress=EepromDataAddress;
	this->EepromDevice=EepromDevice;
	loaded=false;
}

void PARAMETER_LOGICAL_EEPROM::save(){
	if(EepromDevice>0){
		uint8_t tempData = (data)? 0xAA : 0x55;

		EepromDevice->write(EepromDataAddress  , 1, &tempData);
	}
}

void PARAMETER_LOGICAL_EEPROM::load(){
	if(EepromDevice>0){
		uint8_t tempData;

		EepromDevice->read(EepromDataAddress  , 1, &tempData);

		if(tempData == 0xAA){
			data = true;
		}else if(tempData == 0x55){
			data = false;
		}else{
			setDef();
		}
	}
}

void PARAMETER_LOGICAL_EEPROM::setAndSave(bool dat){
	set(dat);
	save();
}

bool PARAMETER_LOGICAL_EEPROM::getAndLoad(){
	load();
	return PARAMETER_LOGICAL::get();
}

bool PARAMETER_LOGICAL_EEPROM::get(){
	if(!loaded)load();
	loaded=true;
	return PARAMETER_LOGICAL::get();
}




