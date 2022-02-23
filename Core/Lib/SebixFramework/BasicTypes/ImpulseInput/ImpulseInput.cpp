/*
 * ImpulseInput.cpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */

#include "ImpulseInput.hpp"

ImpulseInput::ImpulseInput(PIN *pin, Slope slope, uint32_t samplingTime, PULL pinpull, LOGIC logic) :
		INPUT_BASIC(pin, pinpull, logic){

	this->slope = slope;

	this->input = input;
	this->samplingTime = samplingTime;
}

void ImpulseInput::init(){
	INPUT_BASIC::init();

}

void ImpulseInput::iterate(uint32_t TICK){
	bool state = INPUT_BASIC::get();
	if(state != lastState){
		lastState = state;

		if(slope == Slope::Both || (slope == Slope::Falling && state == false) || (slope == Slope::Rising && state == true)){
			impulses++;
		}

	}
	if(TICK - startingTime >= samplingTime){
		lastImpulses = impulses;
		startingTime = TICK;
		impulses=0;

	}

}

uint32_t ImpulseInput::getImpulses(){
	return lastImpulses;
}

uint32_t ImpulseInput::getImpulsesPerMs(uint32_t ms){
	return (ms * getImpulses()) / getSampligTime();
}

uint32_t ImpulseInput::getSampligTime(){
	return samplingTime;
}
