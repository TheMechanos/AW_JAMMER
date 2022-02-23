/*
 * Input.cpp
 *
 *  Created on: 29.12.2019
 *      Author: SHON
 */

#include <BasicTypes/IO/Input.hpp>


INPUT_BASIC::INPUT_BASIC(PIN * pin, PULL pinpull, LOGIC logic) :
		INPUT_PIN(pin, pinpull){
	this->logic = logic;
}

bool INPUT_BASIC::get(){
	return (INPUT_PIN::get() ^ (uint8_t) logic);
}

bool INPUT_BASIC::getPinState(){
	return (INPUT_PIN::get());
}







INPUT_BUFFERED::INPUT_BUFFERED(uint16_t measureIterval, uint8_t averagingNumber, PIN * pin, PULL pinpull, LOGIC logic) :
		INPUT_BASIC(pin, pinpull, logic){
	this->averagingNumber = (averagingNumber > MAX_AVERAGING) ? MAX_AVERAGING : averagingNumber;
	this->measureIterval = measureIterval;
	this->measures = 0;
	this->lastIterate = 0;
	this->lastState = false;
}

bool INPUT_BUFFERED::get(){
	uint32_t mask = (1 << (averagingNumber+1))-1;

	if((measures & mask) == mask){
		lastState = true;
		return true;
	}
	if((measures & mask) == 0){
		lastState = false;
		return false;
	}
	return lastState;

}

void INPUT_BUFFERED::iterate(uint32_t TICK){
	if(TICK - lastIterate > measureIterval){
		lastIterate = TICK;
		measures = measures << 1;
		if(INPUT_BASIC::get())
			measures |= 1;
	}
}







INPUT_DEBOUNCED::INPUT_DEBOUNCED(uint16_t debounceTime, PIN * pin, PULL pinpull, LOGIC logic) :
		INPUT_BASIC(pin, pinpull, logic){
	this->debounceTime = debounceTime;
	this->lastStateChange = 0;
	this->state = false;
	this->lastTempState=false;
}

bool INPUT_DEBOUNCED::get(){
	return state;
}

void INPUT_DEBOUNCED::iterate(uint32_t TICK){
	bool newState = INPUT_BASIC::get();

	if(newState != lastTempState){
		lastStateChange = TICK;
		lastTempState = newState;
	}
	if(TICK - lastStateChange > debounceTime && state != lastTempState){
		state = newState;
	}
}













BASIC_BINARY_INPUTS::BASIC_BINARY_INPUTS(){
	len = 0;
}

void BASIC_BINARY_INPUTS::addInput(INPUT_BASIC &a){
	ins[len] = &a;
	len++;
}

uint8_t BASIC_BINARY_INPUTS::get(){
	uint8_t ret = 0;

	for(uint8_t q = 0; q < len; q++){
		ret |= (((uint8_t) ins[q]->get()) << q);
	}

	return ret;
}

