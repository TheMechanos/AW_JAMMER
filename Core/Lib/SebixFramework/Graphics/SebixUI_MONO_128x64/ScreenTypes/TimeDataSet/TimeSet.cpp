/*
 * TimeSet.cpp
 *
 *  Created on: 18.10.2020
 *      Author: SHON
 */

#include "TimeSet.hpp"

UIParameterTimeHMS::UIParameterTimeHMS(const char* name, const char* description, TIME * time, uint32_t timeout) :
		UIElementGeneric(name, timeout){

	this->time = time;
	this->description = (char*) description;

	this->timeIdx = 0;

	this->reftim = false;

	this->listener = 0;
}

TIME* UIParameterTimeHMS::getTime(){
	return this->time;
}

void UIParameterTimeHMS::initialize(ContextManager* context){

	timeRaw[0] = time->getHour();
	timeRaw[1] = time->getMinute();
	timeRaw[2] = time->getSecond();


	context->getEncoder()->setMultipler(1);
	context->getEncoder()->setValue(timeRaw[0]);
	context->getEncoder()->setLooping(true);

	this->reftim = true;

}

void UIParameterTimeHMS::iterate(ContextManager* context){

	if(reftim){
		reftim = false;

		if(timeIdx == 0){
			context->getEncoder()->setLimits(0, 23);
		}else if(timeIdx == 1){
			context->getEncoder()->setLimits(0, 59);
		}else if(timeIdx == 2){
			context->getEncoder()->setLimits(0, 59);
		}
		context->getEncoder()->setValue(timeRaw[timeIdx]);
		reDraw();
	}

}

void UIParameterTimeHMS::exiting(ContextManager* context){

	timeIdx = 0;
}

void UIParameterTimeHMS::paint(ContextManager* context){

	drawHeader(context);
	context->getGraphics()->drawText(2, 13, description, font_5pix);

	char buf[10];

	context->getGraphics()->drawRectAbs(1, 31, 127, 31);

	if(timeRaw[0] < 10){
		sprintf(buf, "0%d", timeRaw[0]);
	}else{
		sprintf(buf, "%d", timeRaw[0]);
	}
	context->getGraphics()->drawText(24, 37, buf, font_11pix_BOLD);

	if(timeRaw[1] < 10){
		sprintf(buf, ":0%d", timeRaw[1]);
	}else{
		sprintf(buf, ":%d", timeRaw[1]);
	}
	context->getGraphics()->drawText(47, 37, buf, font_11pix_BOLD);

	if(timeRaw[2] < 10){
		sprintf(buf, ":0%d", timeRaw[2]);
	}else{
		sprintf(buf, ":%d", timeRaw[2]);
	}
	context->getGraphics()->drawText(76, 37, buf, font_11pix_BOLD);
	context->getGraphics()->drawRectAbs(24 + (29 * timeIdx), 54, 43 + (29 * timeIdx), 55);
}

void UIParameterTimeHMS::onExitKeyPressed(ContextManager* context){

	if(timeIdx > 0){
		timeIdx--;
		reftim = true;
	}else{
		context->back();
	}

}

void UIParameterTimeHMS::onOKKeyPressed(ContextManager* context){

	if(timeIdx < 2){
		timeIdx++;
		reftim = true;
	}else{
		time->setHour(timeRaw[0]);
		time->setMinute(timeRaw[1]);
		time->setSecond(timeRaw[2]);
		if(listener)
			listener->handle(this);
		context->back();
	}
}

void UIParameterTimeHMS::onEncoderChange(ContextManager* context){
	timeRaw[timeIdx]=context->getEncoder()->getValue();
	reDraw();
}
