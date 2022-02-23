/*
 * AnalogInput.hpp
 *
 *  Created on: 01.09.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_ANALOGINPUT_HPP_
#define BASICTYPES_ANALOGINPUT_HPP_

#include <Peripheral/ADC/ADC_INTERNAL.hpp>

class ANALOG_INPUT{
public:
	ANALOG_INPUT()=default;
	ANALOG_INPUT(ADC_CHANNEL * ADCChannel, uint16_t measureIterval, uint8_t averagingnumber);

	int32_t getValue();
	int32_t getValuePm();

	void iterate(uint32_t TICK);

	void setMapping(int16_t out_min, int16_t out_max);
	void setMapping(int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);
	void disableMapping();

private:
	ADC_CHANNEL * ADCChannel;

	static const uint8_t MAXAVERAGING=32;
	uint32_t lastMeasure;
	uint16_t measureIterval;
	uint8_t averagingnumber;

	uint16_t measures[MAXAVERAGING];
	uint8_t measuresidx;

	int32_t calculatedValue;

	bool mapping;
	int32_t in_min;
	int32_t in_max;
	int32_t out_min;
	int32_t out_max;
};

class INTERNAL_TEMPERATURE_SENSOR : public ANALOG_INPUT{
public:
	INTERNAL_TEMPERATURE_SENSOR()=default;
	INTERNAL_TEMPERATURE_SENSOR(ADC_CHANNEL * ADCChannel, uint16_t measureIterval, uint8_t averagingnumber, uint16_t v25, uint16_t AvgSlope);

	uint32_t getTemperature();

private:
	 uint16_t v25;
	 uint16_t AvgSlope;

};


#endif /* BASICTYPES_ANALOGINPUT_HPP_ */
