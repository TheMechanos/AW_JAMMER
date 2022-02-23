/*
 * AnalogInput.cpp
 *
 *  Created on: 01.09.2020
 *      Author: SHON
 */

#include "AnalogInput.hpp"



ANALOG_INPUT::ANALOG_INPUT(ADC_CHANNEL * ADCChannel, uint16_t measureIterval, uint8_t averagingnumber){
	this->ADCChannel=ADCChannel;
	this->measureIterval=measureIterval;
	this->averagingnumber=averagingnumber;

	lastMeasure=0;
	measuresidx=0;
	calculatedValue=0;

	mapping=false;
	out_min=0;
	out_max=0;
	in_min=0;
	in_max=0;
}

void ANALOG_INPUT::setMapping(int16_t out_min, int16_t out_max){
	setMapping(0, 4096, out_min, out_max);
}

void ANALOG_INPUT::setMapping(int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max){
	mapping=true;
	this->in_min=in_min;
	this->in_max=in_max;
	this->out_min=out_min;
	this->out_max=out_max;
}
void ANALOG_INPUT::disableMapping(){
	mapping=false;
}

int32_t ANALOG_INPUT::getValue(){
	if(mapping)
		return (calculatedValue - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	else
		return calculatedValue;
}
int32_t ANALOG_INPUT::getValuePm(){
	return (getValue()*1000) / out_max;
}

void ANALOG_INPUT::iterate(uint32_t TICK){
	if((TICK-lastMeasure)>measureIterval){
		lastMeasure=TICK;

		measures[measuresidx]=ADCChannel->getValue();
		measuresidx++;
		if(measuresidx>=averagingnumber){
			measuresidx=0;
			calculatedValue = 0;
			for(uint8_t q = 0 ; q < averagingnumber ; q++){
				calculatedValue += measures[q];
			}
			calculatedValue /= averagingnumber;
		}
	}
}

INTERNAL_TEMPERATURE_SENSOR::INTERNAL_TEMPERATURE_SENSOR(ADC_CHANNEL * ADCChannel, uint16_t measureIterval, uint8_t averagingnumber, uint16_t v25,
		uint16_t AvgSlope) :
		ANALOG_INPUT(ADCChannel, measureIterval, averagingnumber){

	this->v25=v25;
	this->AvgSlope=AvgSlope;
}

uint32_t INTERNAL_TEMPERATURE_SENSOR::getTemperature(){
	int32_t t = getValue() * 3300;
	t/=4096;
	t-=v25;
	t*=1000;
	t/=AvgSlope;
	t+=25;

	return t;
}

