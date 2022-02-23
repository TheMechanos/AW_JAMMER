/*
 * ParameterString.hpp
 *
 *  Created on: May 24, 2021
 *      Author: SHON
 */

#ifndef PARAMETERS_PARAMETERSTRING_HPP_
#define PARAMETERS_PARAMETERSTRING_HPP_

#include <Generic/GenericEEPROM.hpp>
#include "CRC8.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


template<uint16_t capacity>
class ParameterString{
public:
	ParameterString()=default;
	virtual ~ParameterString() = default;

	ParameterString(const char* def){
		set(def);
	}

	void set(char* data) {
		strcpy(this->data, data);
	};
	char* get(){
		return data;
	}

	void clear(){
		for(uint16_t q=0; q<capacity;q++)
			data[q]=0;
	}


protected:
	char data[capacity];

};


template<uint16_t capacity>
class ParameterStringEEPROM : public ParameterString<capacity>{
public:
	ParameterStringEEPROM(){
		eepromDevice=0;
		eepromDataAddress=0;
		clear();
	}
	ParameterStringEEPROM(EEPROM_GENERIC * eepromDevice, uint16_t eepromDataAddress){
		this->eepromDevice=eepromDevice;
		this->eepromDataAddress=eepromDataAddress;
		clear();

	}
	ParameterStringEEPROM(const char *def, EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress){
		this->eepromDevice = eepromDevice;
		this->eepromDataAddress = eepromDataAddress;
		set(def);
	}

	void save(){
		if(EepromDevice){
			uint8_t tempData[capacity + 1];
			tempData[0] = CRC8::generate((uint8_t*) (&data), capacity);
			memcpy(&tempData[1], (uint8_t*) (&data), capacity);

			EepromDevice->write(EepromDataAddress, capacity + 1, tempData);
		}
	}
	void load(){
		if(EepromDevice){
			uint8_t readen[capacity + 1];

			EepromDevice->read(EepromDataAddress, capacity + 1, readen);

			if(CRC8::check(&readen[1], capacity, readen[0])){
				memcpy((uint8_t*) (&data), &readen[1], capacity);
			}
		}
	}

	void setAndSave(char* data){
		set(data);
		save();
	}
	char* getAndLoad(){
		load();
		return get();
	}

private:
	EEPROM_GENERIC * eepromDevice;
	uint16_t eepromDataAddress;



};



#endif /* PARAMETERS_PARAMETERSTRING_HPP_ */
