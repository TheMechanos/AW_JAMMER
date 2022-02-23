/*
 * CodeAcces.cpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/CodeAccess/CodeAccess.hpp>

OUTPUT_ADVENCED::SEQUENCE_SECTION UICodeAccess::sequenceBadCodeSection[2] = { { true, 1500 }, { false, 1 } };
OUTPUT_ADVENCED::SEQUENCE UICodeAccess::sequenceBadCode = { (OUTPUT_ADVENCED::SEQUENCE_SECTION*) sequenceBadCodeSection, 2 };
UIMessage UICodeAccess::statementBadCode("INFO", "B��DNY KOD", 1500, true, (OUTPUT_ADVENCED::SEQUENCE*) (&sequenceBadCode));

UICodeAccess::UICodeAccess(const char* name, const char* description, uint16_t code, uint32_t timeout) :
		UIElementGeneric(name, timeout){
	this->code = code;
	this->description = (char*) description;
	this->actualNumber = 0;
	this->next = 0;
	this->listener = 0;
}

void UICodeAccess::registerChild(UIElementGeneric* next){
	this->next=next;
}

void UICodeAccess::initialize(ContextManager* context){

	actualNumber = 0;

	for(uint8_t q = 0; q < 4; q++)
		typingCode[q] = 0;

	context->getEncoder()->setLimits(0,9);
	context->getEncoder()->setMultipler(1);
	context->getEncoder()->setLooping(true);
	context->getEncoder()->setValue(typingCode[0]);
}
void UICodeAccess::backFromAbove(ContextManager* context){
	context->back();
}


void UICodeAccess::onExitKeyPressed(ContextManager* context){
	if(actualNumber == 0){
		context->back();
		return;
	}
	actualNumber--;
	context->getEncoder()->setValue(typingCode[actualNumber]);
	reDraw();
}


void UICodeAccess::onOKKeyPressed(ContextManager* context){
	if(actualNumber == 3){
		uint16_t tempCode = (typingCode[0] * 1000) + (typingCode[1] * 100) + (typingCode[2] * 10) + (typingCode[3]);
		if(tempCode == code){
			if(listener)
				listener->handle(this);
			context->select(next);
		}else{
			context->select(&statementBadCode);
		}
		return;
	}
	actualNumber++;
	context->getEncoder()->setValue(typingCode[actualNumber]);
	reDraw();
}

void UICodeAccess::onEncoderChange(ContextManager* context){
	typingCode[actualNumber] = context->getEncoder()->getValue();

	reDraw();
}

void UICodeAccess::paint(ContextManager* context){
	drawHeader(context);
	context->getGraphics()->drawText(2, 13, description, font_5pix);
	context->getGraphics()->drawRectAbs(1, 31, 127, 31);

	char buf[10];
	for(uint8_t q = 0; q < 4; q++){
		sprintf(buf, "%d", typingCode[q]);
		context->getGraphics()->drawText(34 + (14 * q), 37, buf, font_11pix_BOLD);
	}
	context->getGraphics()->drawRectAbs(34 + (14 * actualNumber), 54, 42 + (14 * actualNumber), 55);
}

