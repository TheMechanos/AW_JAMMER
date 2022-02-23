/*
 * DataSet.cpp
 *
 *  Created on: 19.10.2020
 *      Author: SHON
 */

#include "DataSet.hpp"

UIParameterData::UIParameterData(const char* name, const char* description, DATE * date, uint32_t timeout) :
		UIElementGeneric(name, timeout){
	this->date = date;
	this->description = (char*) description;

	this->dateIdx = 0;

	this->refdate = false;

	this->listener = 0;
}

DATE* UIParameterData::getDate(){
	return this->date;
}


void UIParameterData::initialize(ContextManager* context){

	dateRaw[0] = date->getYear();
	dateRaw[1] = date->getMonth();
	dateRaw[2] = date->getDay();

	context->getEncoder()->setDivider(4);
	context->getEncoder()->setMultipler(1);
	context->getEncoder()->setValue(dateRaw[0]);
	context->getEncoder()->setLooping(true);

	this->refdate = true;

}
void UIParameterData::iterate(ContextManager* context){

	if(refdate){
		refdate = false;

		if(dateIdx == 0){
			context->getEncoder()->setLimits(2000, 2050);
		}else if(dateIdx == 1){
			context->getEncoder()->setLimits(1, 12);
		}else if(dateIdx == 2){
			uint8_t daysInMonth = date->DAYS_IN_MONTH[dateRaw[1] - 1]; //DATE::DAYS_IN_MONTH[dateRaw[1]] //TODO
			if(dateRaw[1] == 2)
				context->getEncoder()->setLimits(1, daysInMonth - ((date->isLeapYear(dateRaw[0])) ? 1 : 0));
			else
				context->getEncoder()->setLimits(1, daysInMonth);
		}
		context->getEncoder()->setValue(dateRaw[dateIdx]);
		reDraw();
	}

}
void UIParameterData::exiting(ContextManager* context){
	dateIdx = 0;
}

void UIParameterData::paint(ContextManager* context){

	drawHeader(context);
	context->getGraphics()->drawText(2, 13, description, font_5pix);
	context->getGraphics()->drawRectAbs(1, 31, 127, 31);

	char buf[10];
	if(dateRaw[0] < 10){
		sprintf(buf, "0%d", dateRaw[0]);
	}else{
		sprintf(buf, "%d", dateRaw[0]);
	}
	context->getGraphics()->drawText(5, 37, buf, font_11pix_BOLD);

	if(dateRaw[1] < 10){
		sprintf(buf, ".0%d", dateRaw[1]);
	}else{
		sprintf(buf, ".%d", dateRaw[1]);
	}
	context->getGraphics()->drawText(51, 37, buf, font_11pix_BOLD);

	if(dateRaw[2] < 10){
		sprintf(buf, ".0%d", dateRaw[2]);
	}else{
		sprintf(buf, ".%d", dateRaw[2]);
	}
	context->getGraphics()->drawText(81, 37, buf, font_11pix_BOLD);

	context->getGraphics()->drawRectAbs(((dateIdx == 0) ? 5 : 27) + (30 * dateIdx), 54, 46 + (30 * dateIdx), 55);

	char * wek = (char*) DATE::WEEKDAY_STRING_SHORT[(uint8_t) DATE::getWeekday(dateRaw[2], dateRaw[1], dateRaw[0])];
	context->getGraphics()->drawText(113, 34, wek, font_5pix);

}
void UIParameterData::onExitKeyPressed(ContextManager* context){
	if(dateIdx > 0)
		dateIdx--;
	else{
		context->back();
	}
	refdate = true;
}
void UIParameterData::onOKKeyPressed(ContextManager* context){
	if(dateIdx < 2)
		dateIdx++;
	else{
		date->setYear(dateRaw[0]);
		date->setMonth(dateRaw[1]);
		date->setDay(dateRaw[2]);
		if(listener)
			listener->handle(this);
		context->back();
	}
	refdate = true;

}
void UIParameterData::onEncoderChange(ContextManager* context){
	dateRaw[dateIdx]=context->getEncoder()->getValue();
	reDraw();
}
