
/*
 * KeyEncoder.cpp
 *
 *  Created on: Mar 28, 2021
 *      Author: SHON
 */

#include "KeyEncoder.hpp"



KeyEncoder::KeyEncoder(BUTTON_CLICK *a, BUTTON_CLICK *b){
	this->a = a;
	this->b = b;
}

void KeyEncoder::init(){
	configFader(750, 150, 600, 2000);
}

void KeyEncoder::configFader(uint32_t faderStartInterval, uint32_t faderEndInterval, uint32_t faderStartTime, uint32_t faderEndTime){
	a->configFader(faderStartInterval, faderEndInterval, faderStartTime, faderEndTime);
	b->configFader(faderStartInterval, faderEndInterval, faderStartTime, faderEndTime);
}

void KeyEncoder::iterate(uint32_t TICK){
	if(a->isFader()){
		value++;
	}else if(b->isFader()){
		value--;
	}

}

uint32_t KeyEncoder::getRawValue(){
	return value;
}

void KeyEncoder::setRawValue(uint32_t val){
	this->value = val;
}

uint16_t KeyEncoder::getPeroid(){
	return 256;
}

void KeyEncoder::setDivider(uint16_t newDivider){
	uint32_t last = getRawValue();

}
