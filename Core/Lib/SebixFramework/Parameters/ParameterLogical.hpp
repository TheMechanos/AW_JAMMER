/*
 * EEPROMParamater.hpp
 *
 *  Created on: 20.02.2020
 *      Author: SHON
 */

#ifndef EEPROM_PARAMETER_LOGICAL_HPP_
#define EEPROM_PARAMETER_LOGICAL_HPP_

#include <Generic/GenericEEPROM.hpp>
#include "CRC8.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class PARAMETER_LOGICAL{
public:
	PARAMETER_LOGICAL(){data=false;ValueDef=false;};
	PARAMETER_LOGICAL(bool def){data=false;ValueDef=def;};
	virtual ~PARAMETER_LOGICAL() = default;

	void set(bool dat) {
		data=dat;
	};
	bool get(){return data;};

	void setDef(){data=ValueDef;};
	bool getDef(){return ValueDef;};

protected:
	bool data;
	bool ValueDef;
};

class PARAMETER_LOGICAL_EEPROM : public PARAMETER_LOGICAL{
public:
	PARAMETER_LOGICAL_EEPROM();
	PARAMETER_LOGICAL_EEPROM(bool def, EEPROM_GENERIC * EepromDevice, uint16_t EepromDataAddress);

	bool get();

	void save();
	void load();

	void setAndSave(bool dat);
	bool getAndLoad();


private:
	EEPROM_GENERIC * EepromDevice;
	uint16_t EepromDataAddress;

	bool loaded;

};


#endif /* EEPROM_PARAMETER_HPP_ */
