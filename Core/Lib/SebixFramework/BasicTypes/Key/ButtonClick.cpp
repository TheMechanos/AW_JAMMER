/*
 * BUTTON_CLICK.cpp
 *
 *  Created on: 13.11.2020
 *      Author: SHON
 */

#include <BasicTypes/Key/ButtonClick.hpp>

BUTTON_CLICK::BUTTON_CLICK(PIN * pin, uint8_t debounce, PULL pinpull, LOGIC logic) :
		BUTTON(pin, debounce, pinpull, logic){

	this->debounce = debounce;

	this->state = false;
	this->lastTempState = false;

	this->lastActionTime = 0;
	this->lastStateChange = 0;
	this->lastTempStateChange = 0;
	this->lastPressTime = 0;

	this->action = ACTION::NONE;

	this->clickCount = 0;
	this->clicks = 0;

	this->multiclickTime = 400;
	this->longClickTime = 1000;
	this->lockLongClick = false;

	this->actionValidTime = 500;

	this->faderStartInterval = 400;
	this->faderEndInterval = 50;
	this->faderStartTime = 1000;
	this->faderEndTime = 3000;
	this->lastFaderTime = 0;

}
void BUTTON_CLICK::configFader(uint32_t faderStartInterval, uint32_t faderEndInterval, uint32_t faderStartTime, uint32_t faderEndTime){

	this->faderStartInterval = faderStartInterval;
	this->faderEndInterval = faderEndInterval;
	this->faderStartTime = faderStartTime;
	this->faderEndTime = faderEndTime;
}
void BUTTON_CLICK::configMultiClick(uint32_t multiclickTime){
	this->multiclickTime = multiclickTime;
}
void BUTTON_CLICK::configLongClick(uint32_t longClickTime){
	this->longClickTime = longClickTime;
}

bool BUTTON_CLICK::isReleased(){
	return isAction(ACTION::RELEASED);
}

bool BUTTON_CLICK::isPressed(){
	return isAction(ACTION::PRESSED);
}

uint8_t BUTTON_CLICK::isMultiClick(uint8_t clickTarget){
	if(!enabled)return 0;

	if(!clickTarget){
		uint8_t cl = clicks;
		if(isAction(ACTION::MULTICLICK))
			return cl;
	}else{
		if(clickTarget == clicks){
			if( isAction(ACTION::MULTICLICK))
				return true;
		}

	}
	return 0;
}

bool BUTTON_CLICK::isLongHolding(){
	return isAction(ACTION::LONGHOLDING);
}




bool BUTTON_CLICK::isLongPress(uint16_t pressTime){
	if(!enabled)return false;

	if(action == ACTION::LONGHOLDING){
		uint32_t time= System::getTick() - lastPressTime;
		if(time > pressTime && state == true){
			isLongHolding();
			return true;
		}
	}
	return false;
}

bool BUTTON_CLICK::isLongClick(uint16_t minPressTime, uint16_t maxPressTime){
	if(!enabled)return false;

	if(action == ACTION::RELEASED){
		uint32_t time = System::getTick() - lastPressTime;
		if(time > minPressTime && time < maxPressTime){
			isAction(ACTION::RELEASED);
			return true;
		}
	}
	return false;
}

bool BUTTON_CLICK::isAction(ACTION action){
	if(!enabled)return false;

	if(this->action == action){
		this->action = ACTION::NONE;
		if( action == ACTION::PRESSED)buzz();
		if(action == ACTION::MULTICLICK)
			this->clicks = 0;
		return true;
	}
	return false;
}

BUTTON_CLICK::ACTION BUTTON_CLICK::getAction(){
	if(!enabled)return ACTION::NONE;

	ACTION r=action;
	action = ACTION::NONE;
	return r;
}



bool BUTTON_CLICK::isFader(){
	if(!enabled)return false;

	if(state){
		uint32_t sinceLastPress = System::getTick() - lastPressTime;
		uint16_t interval=0;

		if(sinceLastPress < faderStartTime)interval = faderStartInterval;
		else if(sinceLastPress > faderEndTime)interval = faderEndInterval;
		else{
			interval = System::map(sinceLastPress, faderStartTime, faderEndTime, faderStartInterval, faderEndInterval);
		}

		if(System::getTick() - lastFaderTime > interval){
			lastFaderTime = System::getTick();
			buzz();
			return true;
		}

	}else{
		lastFaderTime = 0;
	}
	return false;
}

bool BUTTON_CLICK::isClicked(){
	if(!enabled)return false;

	return state;
}





void BUTTON_CLICK::iterate(uint32_t TICK){

	bool newState = INPUT_BASIC::get();

	if(newState != lastTempState){
		lastTempStateChange = TICK;
		lastTempState = newState;
	}

	if(TICK - lastTempStateChange > debounce && state != lastTempState){
		state = newState;
		lastStateChange=TICK;
		if(newState == true){
			clickCount++;
			action = ACTION::PRESSED;
			lastPressTime = TICK;


		}else{
			action = ACTION::RELEASED;
			lockLongClick=false;
		}
		lastActionTime = TICK;

	}else if(TICK - lastStateChange > multiclickTime && !state){
		if( clickCount > 1){
			clicks = clickCount;
			action = ACTION::MULTICLICK;
			lastActionTime = TICK;
		}
		clickCount=0;

	}else if(TICK - lastStateChange > longClickTime && state && TICK - lastActionTime > actionValidTime && !lockLongClick){
		action = ACTION::LONGHOLDING;
		lastActionTime = TICK;
		clickCount=0;
		lockLongClick=true;

	}

	if(TICK - lastActionTime > actionValidTime){
		action = ACTION::NONE;
		clicks = 0;
	}
}

