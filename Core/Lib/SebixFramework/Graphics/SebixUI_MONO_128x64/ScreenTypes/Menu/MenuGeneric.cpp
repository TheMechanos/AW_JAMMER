/*
 * MenuBasic.cpp
 *
 *  Created on: 04.03.2021
 *      Author: SHON
 */

#include "MenuGeneric.hpp"

UIMenuGeneric::UIMenuGeneric(const char *name, uint32_t timeout) :
		UIElementGeneric(name, timeout){

	position = 0;

	positionScreen = 0;
	this->listener = 0;

	showingClock = false;
}

void UIMenuGeneric::initialize(ContextManager *context){

	context->getEncoder()->setMultipler(1);
	context->getEncoder()->setLimits(0, (getLength() > 0) ? getLength()-1 : 0);
	context->getEncoder()->setValue(position);
	context->getEncoder()->setLooping(false);
}

void UIMenuGeneric::exiting(ContextManager *context){
	position = 0;
}

void UIMenuGeneric::registerListener(UIMenuListener *listener){
	this->listener = listener;
}

void UIMenuGeneric::iterate(ContextManager *context){

}

void UIMenuGeneric::onMinuteChangeIterate(ContextManager *context){
	reDraw();
}

void UIMenuGeneric::onExitKeyPressed(ContextManager *context){
	context->back();
}

void UIMenuGeneric::onOKKeyPressed(ContextManager *context){
	if(isPositionEnabled(position)){
		if(getLength() > 0 && listener){
			listener->handle(this, position);
		}
	}
}

void UIMenuGeneric::onEncoderChange(ContextManager *context){
	position = context->getEncoder()->getValue();
	reDraw();
}

void UIMenuGeneric::paint(ContextManager *context){
	drawHeader(context);

	context->getEncoder()->setLimits(0, (getLength() > 0) ? getLength()-1 : 0);

	if(getLength() <= 0)
		return;

	//=---------------------------------------------------------------------------
	if(showingClock){
		char buf[10];
		context->getTime()->getString(buf, TIME::COMPONENTS::HOUR_MINUTE);
		context->getGraphics()->drawText(102, 4, buf, font_5pix);
	}

	//oblicznie pierwszego eleemntu menu ktory znajdzie sie na ekranie
	if(getLength()-1 <= 3)
		positionScreen = 0;
	else{
		positionScreen = position - 1;
		if(positionScreen < 0)
			positionScreen = 0;
		if(positionScreen > getLength()-1 - 3) //3
			positionScreen = getLength()-1 - 3; //3
	}

	//rysowanie kazdego elementu menu z ekranu
	uint8_t q_max = getLength();
	if(q_max > 4)
		q_max = 4;
	for(uint8_t q = 0; q < q_max; q++){

		uint8_t yPos = 17 + (q * 12);

		if(isPositionCheckbox(positionScreen + q)){
			if(isPositionCheckboxChecked(positionScreen + q)){
				context->getGraphics()->drawBitmap(6, yPos + 1, bmp_check1);
			}else{
				context->getGraphics()->drawBitmap(6, yPos + 1, bmp_check0);
			}
			context->getGraphics()->drawText(15, yPos, getPositionName(positionScreen + q), font_8pix, GraphicsMono::Text::NO_LEW_LINE);

		}else if(isPositionText(positionScreen + q)){
			context->getGraphics()->drawText(6, yPos, getPositionName(positionScreen + q), font_8pix, GraphicsMono::Text::NO_LEW_LINE);

			if(isPositionLineUp(positionScreen + q))
				context->getGraphics()->drawRectAbs(1, yPos - 2, 126, yPos - 2);
			if(isPositionLineDown(positionScreen + q))
				context->getGraphics()->drawRectAbs(1, yPos + 9, 126, yPos + 9);

		}else{

			context->getGraphics()->drawText(6, yPos, getPositionName(positionScreen + q), font_8pix, GraphicsMono::Text::NO_LEW_LINE);
		}
	}

	if(isPositionText(position)){
		uint8_t yPos = 18 + (12 * (position - positionScreen));
		context->getGraphics()->drawBitmap(0, yPos, bmp_wska_square);
	}else{
		if(isPositionEnabled(position)){
			context->getGraphics()->drawBitmap(0, 18 + (12 * (position - positionScreen)), bmp_wska);
		}else{
			context->getGraphics()->drawBitmap(0, 18 + (12 * (position - positionScreen)), bmp_cross);
		}
	}

	context->getGraphics()->clsRectAbs(118, 15, 128, 64);

	int w = (40 * position) / (getLength()); //obliczanie wymiarow paska pozycji

	context->getGraphics()->drawRectAbs(120, 17, 126, 17);
	context->getGraphics()->drawRectAbs(120, 60, 126, 60);
	context->getGraphics()->drawRectAbs(120, 17, 120, 60);
	context->getGraphics()->drawRectAbs(126, 17, 126, 60); //122-124, 19-58

	context->getGraphics()->drawRectAbs(122, 19 + w, 124, 19 + w + (39 / (getLength()))); //rysowanie paska pozycji

}




