/*
 * Output.cpp
 *
 *  Created on: 31.08.2020
 *      Author: SHON
 */

#include <BasicTypes/IO/Output.hpp>

OUTPUT_BASIC::OUTPUT_BASIC(GPIO_TypeDef * gpio, uint16_t pin, LOGIC logic, MODE pinmode) :
		OUTPUT_PIN(gpio, pin, pinmode){
	this->logic = logic;

	this->state = false;
	override=false;
}
OUTPUT_BASIC::OUTPUT_BASIC(PIN * pin, LOGIC logic, MODE pinmode) :
		OUTPUT_PIN(pin, pinmode){
	this->logic = logic;

	this->state = false;
	override=false;
}

void OUTPUT_BASIC::init(){
	OUTPUT_PIN::init();
	set(false);
}

bool OUTPUT_BASIC::get(){
	return state;
}

bool OUTPUT_BASIC::read(){
	return OUTPUT_PIN::get() ^ (uint8_t)logic;
}

void OUTPUT_BASIC::set(bool state){
	if(override)return;
	this->state = state ^ (uint8_t)logic;
	OUTPUT_PIN::set(this->state);
}
void OUTPUT_BASIC::ON(){
	set(true);
}
void OUTPUT_BASIC::OFF(){
	set(false);
}
void OUTPUT_BASIC::toggle(){
	if(override)return;
	this->state = (state) ? false : true;
	OUTPUT_PIN::toggle();
}




void OUTPUT_BASIC::overrideSet(bool state){
	override = true;
	OUTPUT_PIN::set(state ^ (uint8_t)logic);
}
void OUTPUT_BASIC::overrideDisable(){
	override = false;
}






OUTPUT_ADVENCED::OUTPUT_ADVENCED(GPIO_TypeDef * gpio, uint16_t pin, LOGIC logic, MODE pinmode) :
		OUTPUT_BASIC(gpio, pin, logic, pinmode){
	off_time = 0;
	on_time = 0;
	procedure = PROCEDURE::MANUAL;
	lastiterate = 0;
	cycle = CYCLE::ON;

	numberblink = -1;

	sequence = 0;
	sequence_number = 0;
	sequence_last_iterate = 0;
	sequence_position = 0;
	sequence_time_to_go = 0;

}

OUTPUT_ADVENCED::OUTPUT_ADVENCED(PIN * pin, LOGIC logic, MODE pinmode) :
		OUTPUT_BASIC(pin, logic, pinmode){
	off_time = 0;
	on_time = 0;
	procedure = PROCEDURE::MANUAL;
	lastiterate = 0;
	cycle = CYCLE::ON;

	numberblink = -1;

	sequence = 0;
	sequence_number = 0;
	sequence_last_iterate = 0;
	sequence_position = 0;
	sequence_time_to_go = 0;


}


void OUTPUT_ADVENCED::ON(){
	procedure = PROCEDURE::MANUAL;
	OUTPUT_PIN::ON();
}
void OUTPUT_ADVENCED::OFF(){
	procedure = PROCEDURE::MANUAL;
	OUTPUT_PIN::OFF();
}

void OUTPUT_ADVENCED::blink(uint32_t time, CYCLE cycl){
	blink(time, time, cycl);
}
void OUTPUT_ADVENCED::blink(uint32_t on_time, uint32_t off_time, CYCLE cycl){
	if(procedure == PROCEDURE::BLINKING && this->on_time == on_time && this->off_time == off_time)
		return;
	procedure = PROCEDURE::BLINKING;
	this->on_time = on_time;
	this->off_time = off_time;
	cycle = cycl;
	numberblink = -1;
	set((bool)cycl);
	lastiterate = HAL_GetTick();
}

void OUTPUT_ADVENCED::blinkNumber(int number, uint32_t time, CYCLE cycl){
	blinkNumber(number, time, time, cycl);
}
void OUTPUT_ADVENCED::blinkNumber(int number, uint32_t on_time, uint32_t off_time, CYCLE cycl){
	procedure = PROCEDURE::NUMBER_BLINK;
	this->on_time = on_time;
	this->off_time = off_time;
	cycle = cycl;
	numberblink = (number * 2) - 1;
	if(cycl == CYCLE::OFF)
		numberblink++;
	set((bool)cycl);
	lastiterate = HAL_GetTick();
}

void OUTPUT_ADVENCED::timeON(uint32_t timeon){
	timeSET(timeon, 1);
}
void OUTPUT_ADVENCED::timeOFF(uint32_t timeoff){
	timeSET(timeoff, 0);
}
void OUTPUT_ADVENCED::timeTOG(uint32_t time){
	if(get())
		timeSET(time, 0);
	else
		timeSET(time, 1);
}

void OUTPUT_ADVENCED::timeSET(uint32_t time, bool startvalue){
	procedure = PROCEDURE::NUMBER_BLINK;
	numberblink = 1;
	if(startvalue){
		cycle = CYCLE::ON;
		on_time = time;
	}else{
		cycle = CYCLE::OFF;
		off_time = time;
	}
	set((bool)cycle);
	lastiterate = HAL_GetTick();
}

OUTPUT_ADVENCED::PROCEDURE OUTPUT_ADVENCED::getMode(){
	return procedure;
}

void OUTPUT_ADVENCED::playSequence(SEQUENCE* sequnce, uint16_t number){
	procedure = PROCEDURE::SEQUENCE;
	this->sequence = sequnce;
	this->sequence_number = number;
	this->sequence_last_iterate = 0;
	this->sequence_position = 0;
	this->sequence_time_to_go = 0;
}
void OUTPUT_ADVENCED::stopSequence(){
	if(procedure == PROCEDURE::SEQUENCE)
		procedure = PROCEDURE::MANUAL;
}

void OUTPUT_ADVENCED::iterate(uint32_t TICK){

	if(procedure == PROCEDURE::BLINKING || procedure == PROCEDURE::NUMBER_BLINK){
		if(cycle == CYCLE::ON){
			if(on_time <= (TICK - lastiterate)){ //if(time>= (lastiterate+on_time)){
				set(0);
				cycle = CYCLE::OFF;
				lastiterate = TICK;
				numberblink--;
				if(procedure == PROCEDURE::NUMBER_BLINK && numberblink == 0)
					procedure = PROCEDURE::MANUAL;
				return;
			}
		}else if(cycle == CYCLE::OFF){
			if(off_time <= (TICK - lastiterate)){ //if(time >= (lastiterate + off_time)){
				set(1);
				cycle = CYCLE::ON;
				lastiterate = TICK;
				numberblink--;
				if(procedure == PROCEDURE::NUMBER_BLINK && numberblink == 0)
					procedure = PROCEDURE::MANUAL;
				return;
			}
		}
	}else if(procedure == PROCEDURE::SEQUENCE){
		if(sequence_time_to_go <= (TICK - sequence_last_iterate)){
			sequence_last_iterate = TICK;

			if(sequence->section[sequence_position].state)
				set(1);
			else
				set(0);
			sequence_time_to_go = sequence->section[sequence_position].time;

			sequence_position++;
			if(sequence_position == sequence->length){
				sequence_position = 0;
				if(sequence_number > 0){
					sequence_number--;
					if(sequence_number == 0){
						//set(0);
						procedure = PROCEDURE::MANUAL;
					}
				}
			}

		}
	}
}
