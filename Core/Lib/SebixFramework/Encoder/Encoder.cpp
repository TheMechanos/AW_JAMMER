/*
 * encoder.cpp
 *
 *  Created on: 25.10.2020
 *      Author: SHON
 */


#include "Encoder.hpp"

#include <limits.h>


ENCODER::ENCODER(ENCODER_BASE * encoderBase){
	this->encoderBase = encoderBase;

	this->rawValueLast = 0;

	this->valueLast = 0;
	this->value = 0;

	this->min = -2000000000;
	this->max =  2000000000;

	this->multipler = 1;
	this->divider = 1;

	this->buzzer=0;
	this->buztime=0;

	this->looping=false;

}

void ENCODER::init(){
	encoderBase->init();

}

void ENCODER::registerBuzzer(OUTPUT_ADVENCED * buzzer, uint16_t buztime){
	this->buzzer=buzzer;
	this->buztime=buztime;
}


void ENCODER::iterate(){
	int16_t rawValue = encoderBase->getRawValue();
	if(rawValue != rawValueLast){
		int32_t delta = rawValue - rawValueLast;
		rawValueLast = rawValue;
		uint16_t overflow = encoderBase->getPeroid()/2;
		if(delta > overflow){
			delta -= encoderBase->getPeroid();
		}else if( delta < -overflow){
			delta += encoderBase->getPeroid();
		}
		value+=delta*multipler;

		if(looping){
			if(value > max)value = min;
			if(value < min)value = max;
		}else{
			if(value > max)value = max;
			if(value < min)value = min;
		}
	}
}

int32_t ENCODER::getValue(){
	if(value != valueLast){
		valueLast = value;
		if(buztime>0)buzzer->timeON(buztime);
	}
	return value;
}

void ENCODER::setLimits(int32_t min, int32_t max){
	if(min > max){
		int32_t w = max;
		max = min;
		min = w;
	}
	this->min = min;
	this->max = max;

}

void ENCODER::setValue(int32_t val){
	this->value = val;
	this->valueLast = val;
}

void ENCODER::setLooping(bool looping){
	this->looping=looping;
}


void ENCODER::setDivider(uint32_t divider){
	this->divider=divider;
	encoderBase->setDivider(divider);
	rawValueLast = encoderBase->getRawValue();
}

void ENCODER::setMultipler(int32_t multipler){
	this->multipler=multipler;
}






