/*
 * Statement.cpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#include "Message.hpp"

UIMessage::UIMessage(const char* name, const char* description, uint16_t time, bool is_exit_statement,OUTPUT_ADVENCED::SEQUENCE* buzseq, bool skipable) :
		UIElementGeneric(name, 0){

	this->description=(char*)description;
	this->time=time;
	this->skipable=skipable;
	this->is_exit_statement=is_exit_statement;
	bmp=bmp_info;
	this->buzseq=buzseq;
	this->listener=0;
}

char* UIMessage::getDescription(){

	return description;
}
uint16_t UIMessage::getTime(){

	return time;
}
bool UIMessage::is_skipable(){

	return skipable;
}
void UIMessage::setImage(tImage bmp){

	this->bmp=bmp;
}

void UIMessage::initialize(ContextManager* context){

	if(buzseq!=0)context->getBuzzer()->playSequence(buzseq);
}

void UIMessage::iterate(ContextManager* context){

	if(time < System::getTick() - getLastAction()){
		if(is_exit_statement){
			context->back();
		}
		context->back();
		if(listener)
			listener->handle(this);
	}
}

void UIMessage::exiting(ContextManager* context){

	context->getBuzzer()->stopSequence();
}

void UIMessage::paint(ContextManager* context){

	context->getGraphics()->drawText(4, 2, getName(), font_8pix);

	context->getGraphics()->drawText(2, 17, getDescription(), font_5pix);

	context->getGraphics()->drawRectAbs(1, 0, 126, 0);
	context->getGraphics()->drawRectAbs(1, 12, 126, 12);

	context->getGraphics()->drawBitmap(2, 28, bmp);
}

void UIMessage::onExitKeyPressed(ContextManager* context){

}

void UIMessage::onOKKeyPressed(ContextManager* context){

	if(is_skipable()){
		if(is_exit_statement){
			context->back();
		}
		context->back();
		if(listener)listener->handle(this);
	}
}

