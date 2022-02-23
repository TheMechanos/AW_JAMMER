/*
 * Button.cpp
 *
 *  Created on: 13.11.2020
 *      Author: SHON
 */

#include "Button.hpp"

BUTTON::BUTTON(PIN * pin, uint16_t debounce, PULL pinpull, LOGIC logic) :
		INPUT_BASIC(pin, pinpull, logic){

	this->debounce = debounce;

	this->state = false;
	this->lastTempState = false;

	this->lastStateChange = 0;
	this->lastTempStateChange = 0;
	this->lastActionTime = 0;

	this->action = ACTION::NONE;

	this->actionValidTime = 500;

	this->buzzer = 0;
	this->buzTime = 0;
	this->player = 0;
	this->song = 0;

	this->enabled = true;
}

void BUTTON::init(){
	INPUT_BASIC::init();

	this->state = INPUT_BASIC::get();
	this->lastTempState = this->state;
	this->action = ACTION::NONE;

}

void BUTTON::configActionValidTime(uint32_t actionValidTime){
	this->actionValidTime = actionValidTime;
}

void BUTTON::registerBuzzer(OUTPUT_ADVENCED* buzzer, uint8_t buzTime){
	this->buzzer = buzzer;
	this->buzTime = buzTime;
}
void BUTTON::registerMusic(MusicPlayer* player, Song* song){
	this->player = player;
	this->song = song;
}

bool BUTTON::isReleased(){
	return isAction(ACTION::RELEASED);
}

bool BUTTON::isPressed(){
	return isAction(ACTION::PRESSED);
}


bool BUTTON::isAction(ACTION action){
	if(!enabled)return false;

	if(this->action == action){
		this->action = ACTION::NONE;
		if(action == ACTION::RELEASED || action == ACTION::PRESSED)buzz();
		return true;
	}
	return false;
}

BUTTON::ACTION BUTTON::getAction(){
	if(!enabled)return ACTION::NONE;

	ACTION r=action;
	action = ACTION::NONE;
	return r;
}

void BUTTON::buzz(){
	if(buzzer)buzzer->timeON(buzTime);
	if(player)player->play(song);
}

void BUTTON::iterate(uint32_t TICK){

	bool newState = INPUT_BASIC::get();

	if(newState != lastTempState){
		lastTempStateChange = TICK;
		lastTempState = newState;
	}

	if(TICK - lastTempStateChange > debounce && state != lastTempState){
		state = newState;
		lastStateChange=TICK;
		if(newState == true){
			action = ACTION::PRESSED;
		}else{
			action = ACTION::RELEASED;
		}
		lastActionTime = TICK;

	}
	if(TICK - lastActionTime > actionValidTime){
		action = ACTION::NONE;
	}
}

void BUTTON::disable(){
	this->enabled = false;
}

void BUTTON::enable(){
	this->enabled = true;
}
