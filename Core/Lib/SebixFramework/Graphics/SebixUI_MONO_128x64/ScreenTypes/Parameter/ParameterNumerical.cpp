/*
 * ParameterNumerical.cpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/Parameter/ParameterNumerical.hpp>

UIParameterNumerical::UIParameterNumerical() :
		UIElementGeneric("", 0){

	description=0;
	unit=0;
	step=0;
	tempparam=0;
	param=0;
	listener=0;
}

UIParameterNumerical::UIParameterNumerical(const char* name, const char* description, ParameterNumerical* param,
		 int32_t step, const char* unit, uint32_t timeout) :
		UIElementGeneric(name, timeout){

	this->param = param;

	this->description = (char*)description;
	this->unit = (char*)unit;
	this->step=step;

	tempparam=0;

	this->listener=0;
}


void UIParameterNumerical::initialize(ContextManager* context){

	tempparam = param->getAndLoad();

	context->getEncoder()->setLimits(param->getMin(), param->getMax());
	context->getEncoder()->setMultipler(step);
	context->getEncoder()->setDivider(4);
	context->getEncoder()->setLooping(false);
	context->getEncoder()->setValue(tempparam);

}


void UIParameterNumerical::iterate(ContextManager* context){

}

void UIParameterNumerical::paint(ContextManager* context){

	drawHeader(context);

	context->getGraphics()->drawText(2, 13, description, font_5pix, GraphicsMono::Text::FOLD);//FOLD TEXT //TODO
	context->getGraphics()->drawRectAbs(1, 31, 126, 31);

	char buf[30];
	sprintf(buf, "=%ld%s", tempparam, unit);

	//context->getGraphics()->clsRectAbs(0, 36, 128, 54);
	context->getGraphics()->drawText(5, 34, buf, font_11pix_BOLD);

	context->getGraphics()->drawRectAbs(1, 53, 126, 53);
	sprintf(buf, "%ld - %ld  : %ld", param->getMin(), param->getMax(), step);
	context->getGraphics()->drawText(5, 55, buf, font_5pix);
}

void UIParameterNumerical::onExitKeyPressed(ContextManager* context){

	context->back();
}
void UIParameterNumerical::onOKKeyPressed(ContextManager* context){

	param->setAndSave(tempparam);

	if(listener)listener->handle(this);

	context->back();
}

void UIParameterNumerical::onEncoderChange(ContextManager* context){
	tempparam = context->getEncoder()->getValue();
	reDraw();
}

