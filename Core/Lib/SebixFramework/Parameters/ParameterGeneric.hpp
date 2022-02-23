/*
 * ParameterGeneric.hpp
 *
 *  Created on: 26 lis 2021
 *      Author: skocz
 */

#ifndef LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERGENERIC_HPP_
#define LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERGENERIC_HPP_


#include <Generic/GenericEEPROM.hpp>
#include "CRC8.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



template<class Type>
class ParameterGeneric{
public:
	ParameterGeneric()=default;
	virtual ~ParameterGeneric() = default;

	ParameterGeneric(Type def){
		set(def);
	}

	void set(Type data) {
		this->data = data;
	};
	Type get(){
		return data;
	}

	void clear(){
		data = 0;
	}

protected:

	uint8_t* getDataPointer(){
		return (uint8_t*) &data;
	}

	Type data;
};


template<class Type>
class ParameterGenericEEPROM: public ParameterGeneric<Type> {
public:
	ParameterGenericEEPROM() {
		eepromDevice = 0;
		eepromDataAddress = 0;
		ParameterGeneric<Type>::clear();
	}
	ParameterGenericEEPROM(Type def) :
			ParameterGeneric<Type>(def) {
		eepromDevice = 0;
		eepromDataAddress = 0;
		ParameterGeneric<Type>::clear();
	}

	ParameterGenericEEPROM(EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress) {
		this->eepromDevice = eepromDevice;
		this->eepromDataAddress = eepromDataAddress;
		ParameterGeneric<Type>::clear();

	}
	ParameterGenericEEPROM(Type def, EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress) :
			ParameterGeneric<Type>(def) {
		this->eepromDevice = eepromDevice;
		this->eepromDataAddress = eepromDataAddress;
	}
	void registerEEPROM(EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress) {
		this->eepromDevice = eepromDevice;
		this->eepromDataAddress = eepromDataAddress;
	}

	void save(){
		if(eepromDevice){
			uint8_t tempData[sizeof(Type) + 1];
			tempData[0] = CRC8::generate(ParameterGeneric<Type>::getDataPointer(), sizeof(Type));
			memcpy(&tempData[1], ParameterGeneric<Type>::getDataPointer(), sizeof(Type));

			eepromDevice->write(eepromDataAddress, sizeof(Type) + 1, tempData);
		}
	}
	void load(){
		if(eepromDevice){
			uint8_t readen[sizeof(Type) + 1];

			eepromDevice->read(eepromDataAddress, sizeof(Type) + 1, readen);

			if(CRC8::check(&readen[1], sizeof(Type), readen[0])){
				memcpy(ParameterGeneric<Type>::getDataPointer(), &readen[1], sizeof(Type));
			}
		}
	}

	void setAndSave(Type data){
		ParameterGeneric<Type>::set(data);
		save();
	}
	Type getAndLoad(){
		load();
		return ParameterGeneric<Type>::get();
	}

	uint32_t getEndAdress(){
		return eepromDataAddress + sizeof(Type) +1;
	}

private:
	EEPROM_GENERIC * eepromDevice;
	uint16_t eepromDataAddress;
};





template<size_t capacity, class Type>
class ParameterGenericArray{
public:
	ParameterGenericArray()=default;
	virtual ~ParameterGenericArray() = default;

	ParameterGenericArray(Type* def){
		set(def);
	}

	void set(Type* data, size_t size=capacity) {
		memcpy(this->data, data, size*sizeof(Type));
	}
	void get(Type* data, size_t size=capacity){
		memcpy(data, this->data, size*sizeof(Type));
	}

	void clear(){
		for(uint16_t q=0; q<capacity;q++)
			data[q]=0;
	}

	size_t getSize(){
		return capacity;
	}


protected:
	uint8_t* getDataPointer(){
		return (uint8_t*) &data;
	}

	Type data[capacity];
};


template<size_t capacity, class Type>
class ParameterGenericArrayEEPROM : public ParameterGenericArray<capacity, Type>{
public:
	ParameterGenericArrayEEPROM(){
		eepromDevice=0;
		eepromDataAddress=0;
		ParameterGenericArrayEEPROM<capacity, Type>::clear();
	}
	ParameterGenericArrayEEPROM(EEPROM_GENERIC * eepromDevice, uint16_t eepromDataAddress){
		this->eepromDevice=eepromDevice;
		this->eepromDataAddress=eepromDataAddress;
		ParameterGenericArrayEEPROM<capacity, Type>::clear();

	}
	ParameterGenericArrayEEPROM(Type *def, EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress){
		this->eepromDevice = eepromDevice;
		this->eepromDataAddress = eepromDataAddress;
		set(def);
	}
	void registerEEPROM(EEPROM_GENERIC * eepromDevice, uint16_t eepromDataAddress){
		this->eepromDevice=eepromDevice;
		this->eepromDataAddress=eepromDataAddress;
	}

	void save(){
		if(eepromDevice){
			uint8_t tempData[capacity*sizeof(Type) + 1];
			tempData[0] = CRC8::generate(ParameterGenericArray<capacity, Type>::getDataPointer(), capacity*sizeof(Type));
			memcpy(&tempData[1], ParameterGenericArray<capacity, Type>::getDataPointer(), capacity*sizeof(Type));

			eepromDevice->write(eepromDataAddress, capacity*sizeof(Type) + 1, tempData);
		}
	}
	void load(){
		if(eepromDevice){
			uint8_t readen[capacity*sizeof(Type) + 1];

			eepromDevice->read(eepromDataAddress, capacity*sizeof(Type) + 1, readen);

			if(CRC8::check(&readen[1], capacity*sizeof(Type), readen[0])){
				memcpy(ParameterGenericArray<capacity, Type>::getDataPointer(), &readen[1], capacity*sizeof(Type));
			}
		}
	}

	void setAndSave(Type* data, size_t size=capacity){
		ParameterGenericArray<capacity, Type>::set(data, size);
		save();
	}

	void getAndLoad(Type* data, size_t size=capacity){
		load();
		ParameterGenericArray<capacity, Type>::get(data, size);
	}

	uint32_t getEndAdress(){
		return eepromDataAddress + capacity*sizeof(Type) +1;
	}

private:
	EEPROM_GENERIC * eepromDevice;
	uint16_t eepromDataAddress;

};



#endif /* LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERGENERIC_HPP_ */
