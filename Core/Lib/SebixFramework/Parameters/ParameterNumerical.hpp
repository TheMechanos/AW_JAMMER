/*
 * ParameterNumerical.hpp
 *
 *  Created on: 18 gru 2021
 *      Author: skocz
 */

#ifndef LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERNUMERICAL_HPP_
#define LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERNUMERICAL_HPP_

#include <Parameters/ParameterGeneric.hpp>

class ParameterNumerical : public ParameterGenericEEPROM<int32_t>{
public:
	ParameterNumerical()=default;

	ParameterNumerical(int32_t def, int32_t min, int32_t max) :
			ParameterGenericEEPROM<int32_t>(def) {
		this->def = def;
		this->min = min;
		this->max = max;

		eepromDevice = 0;
		eepromDataAddress = 0;
	}
	ParameterNumerical(int32_t def, int32_t min, int32_t max, EEPROM_GENERIC *eepromDevice, uint16_t eepromDataAddress) :
			ParameterGenericEEPROM<int32_t>(def, eepromDevice, eepromDataAddress) {
		this->def = def;
		this->min = min;
		this->max = max;

	}

	uint32_t getDef(){
		return def;
	}
	uint32_t getMin(){
		return min;
	}
	uint32_t getMax(){
		return max;
	}

private:
	int32_t def;
	int32_t min;
	int32_t max;
	EEPROM_GENERIC *eepromDevice;
	uint16_t eepromDataAddress;
};


#endif /* LIBS_SEBIXFRAMEWORK_PARAMETERS_PARAMETERNUMERICAL_HPP_ */
