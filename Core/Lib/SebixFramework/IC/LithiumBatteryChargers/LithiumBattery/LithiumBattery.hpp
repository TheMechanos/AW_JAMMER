/*
 * BatteryIndicator.hpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */

#ifndef IC_LITHIUMBATTERYCHARGERS_LITHIUMBATTERY_LITHIUMBATTERY_HPP_
#define IC_LITHIUMBATTERYCHARGERS_LITHIUMBATTERY_LITHIUMBATTERY_HPP_

#include <BasicTypes/AnalogInput/AnalogInput.hpp>

class LithiumBattery{
public:
	LithiumBattery()=default;
	LithiumBattery(ANALOG_INPUT* voltage, ANALOG_INPUT* ntc);

	uint8_t getPercent();
	uint16_t getTemperature();

private:
	ANALOG_INPUT* voltage;
	ANALOG_INPUT* ntc;
	//0% - 100% by 2% in mV
	static const uint16_t dat[]; //51 elementów

};




#endif /* IC_LITHIUMBATTERYCHARGERS_LITHIUMBATTERY_LITHIUMBATTERY_HPP_ */
