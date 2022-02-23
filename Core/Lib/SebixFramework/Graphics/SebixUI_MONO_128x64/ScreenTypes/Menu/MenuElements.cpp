/*
 * Menu.cpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/Menu/MenuElements.hpp>

UIMenuElements::UIMenuElements(const char *name, uint32_t timeout) :
	UIMenuGeneric(name, timeout){
	menuUnitsIdx = -1;
}

void UIMenuElements::onExitKeyPressed(ContextManager *context){
	UIMenuGeneric::onExitKeyPressed(context);
}

void UIMenuElements::onOKKeyPressed(ContextManager *context){
	if(isPositionEnabled(position)){
		UIMenuGeneric::onOKKeyPressed(context);

		if(menuUnitsIdx >= 0){
			context->select(getUnit(position));
		}

	}
}

void UIMenuElements::addElement(UIElementGeneric *elem){
	if(menuUnitsIdx >= MENU_UNITS_MAX)
		return;
	menuUnitsIdx++;
	menuUnits[menuUnitsIdx] = elem;
}

UIElementGeneric* UIMenuElements::getUnit(uint8_t position){
	return menuUnits[position];
}

uint8_t UIMenuElements::getLength(){
	return menuUnitsIdx+1;
}

char* UIMenuElements::getPositionName(uint8_t posi){
	return getUnit(posi)->getName();
}

bool UIMenuElements::isPositionEnabled(uint8_t posi){
	return getUnit(posi)->isEnabled();
}

bool UIMenuElements::isPositionCheckbox(uint8_t posi){
	return dynamic_cast<UIParameterCheckbox*>(getUnit(posi)) != 0;
}

bool UIMenuElements::isPositionCheckboxChecked(uint8_t posi){
	if(isPositionCheckbox(posi)){
		return ((UIParameterCheckbox*) getUnit(posi))->isSelected();
	}
	return false;
}

bool UIMenuElements::isPositionText(uint8_t posi){
	return dynamic_cast<UIMenuText*>(getUnit(posi)) != 0;
}

bool UIMenuElements::isPositionLineUp(uint8_t posi){
	if(isPositionText(posi)){
		return ((UIMenuText*) getUnit(posi))->isLineUp();
	}
	return false;
}

bool UIMenuElements::isPositionLineDown(uint8_t posi){
	if(isPositionText(posi)){
		return ((UIMenuText*) getUnit(posi))->isLineDown();
	}
	return false;
}


/*
 UI_MENU::UI_MENU(const char* name, uint32_t timeout) :
 UI_ELEMENT(name, timeout){

 menuUnitsIdx = -1;
 position = 0;
 positionLast = -2;
 positionScreen = 0;

 showingTime=false;
 }


 void UI_MENU::addElement(UI_ELEMENT * elem){

 if(menuUnitsIdx >=  MENU_UNITS_MAX)return;
 menuUnitsIdx++;
 menuUnits[menuUnitsIdx]=elem;
 }


 void UI_MENU::initialize(CONTEXT_MANAGER* context){

 context->getEncoder()->setMultipler(1);
 context->getEncoder()->setLimits(0, (menuUnitsIdx>=0) ? menuUnitsIdx : 0);
 context->getEncoder()->setValue(position);
 context->getEncoder()->setLooping(false);

 positionLast-=MENU_UNITS_MAX+1;
 }


 void UI_MENU::exiting(CONTEXT_MANAGER* context){
 position=0;
 positionLast = -2;
 }

 void UI_MENU::deleteMenuElement(uint8_t position){

 if(position >= MENU_UNITS_MAX)return;

 menuUnits[position]=0;
 for(uint8_t q=position; q < MENU_UNITS_MAX-1; q++){
 menuUnits[q]=menuUnits[q+1];
 }
 menuUnitsIdx--;
 }

 void UI_MENU::deleteMenuElement(UI_ELEMENT * element){

 for(uint8_t q=0; q < MENU_UNITS_MAX; q++){
 if(menuUnits[q] == element){
 deleteMenuElement(q);
 }
 }
 }
 void UI_MENU::deleteMenuAll(){
 menuUnitsIdx = -1;
 for(uint8_t q = 0; q < MENU_UNITS_MAX; q++){
 menuUnits[q] = 0;
 }
 }

 uint8_t UI_MENU::getNumberOfElements(){

 return menuUnitsIdx+1;
 }

 UI_ELEMENT* UI_MENU::getUnit(uint8_t position){

 return menuUnits[position];
 }


 void UI_MENU::iterate(CONTEXT_MANAGER* context){

 }

 void UI_MENU::onMinuteChangeIterate(CONTEXT_MANAGER* context){
 reDraw();
 }

 void UI_MENU::onExitKeyPressed(CONTEXT_MANAGER* context){
 context->back();
 }

 void UI_MENU::onOKKeyPressed(CONTEXT_MANAGER* context){
 if(menuUnits[position]->isEnabled() && menuUnitsIdx >= 0){
 context->select(menuUnits[position]);
 }
 }

 void UI_MENU::onEncoderChange(CONTEXT_MANAGER* context){
 position = context->getEncoder()->getValue();
 reDraw();
 }

 void UI_MENU::paint(CONTEXT_MANAGER* context){
 drawHeader(context);

 if(menuUnitsIdx < 0)
 return;

 if(menuUnits[position]->isSkipping()){
 if(position == 0 || position == menuUnitsIdx){
 position = positionLast;
 }else{
 if(position > positionLast){
 position++;
 }else{
 position--;
 }
 }
 context->getEncoder()->setValue(position);
 }
 //=---------------------------------------------------------------------------
 if(showingTime){
 char buf[10];
 context->getTime()->getString(buf, TIME::COMPONENTS::HOUR_MINUTE);
 context->getGraphics()->drawText(102, 4, buf, font_5pix);
 }

 //oblicznie pierwszego eleemntu menu ktory znajdzie sie na ekranie
 if(menuUnitsIdx <= 3)
 positionScreen = 0;
 else{
 positionScreen = position - 1;
 if(positionScreen < 0)
 positionScreen = 0;
 if(positionScreen > menuUnitsIdx - 3) //3
 positionScreen = menuUnitsIdx - 3; //3
 }

 //rysowanie kazdego elementu menu z ekranu
 uint8_t q_max = menuUnitsIdx + 1;
 if(q_max > 4)
 q_max = 4;
 for(uint8_t q = 0; q < q_max; q++){

 uint8_t yPos = 17 + (q * 12);

 UI_PARAMETER_CHECKBOX* checkbox = dynamic_cast<UI_PARAMETER_CHECKBOX*>(menuUnits[positionScreen + q]);
 UI_MENU_TEXT* text = dynamic_cast<UI_MENU_TEXT*>(menuUnits[positionScreen + q]);
 if(checkbox){
 if(checkbox->isSelected()){
 context->getGraphics()->drawBitmap(6, yPos + 1, bmp_check1);
 }else{
 context->getGraphics()->drawBitmap(6, yPos + 1, bmp_check0);
 }
 context->getGraphics()->drawText(15, yPos, getPositionName(menuUnits[positionScreen + q]), font_8pix, Graphics::TEXT::NO_LEW_LINE);

 }else if(text){
 context->getGraphics()->drawText(6, yPos, getPositionName(menuUnits[positionScreen + q]), font_8pix, Graphics::TEXT::NO_LEW_LINE);

 if(text->isLineUp())
 context->getGraphics()->drawRectAbs(1, yPos - 2, 126, yPos - 2);
 if(text->isLineDown())
 context->getGraphics()->drawRectAbs(1, yPos + 9, 126, yPos + 9);

 }else{

 context->getGraphics()->drawText(6, yPos, getPositionName(menuUnits[positionScreen + q]), font_8pix, Graphics::TEXT::NO_LEW_LINE);
 }
 }

 UI_MENU_TEXT* text = dynamic_cast<UI_MENU_TEXT*>(menuUnits[position]);
 if(text){
 uint8_t yPos = 18 + (12 * (position - positionScreen));
 context->getGraphics()->drawBitmap(0, yPos, bmp_wska_square);
 }else{
 if(menuUnits[position]->isEnabled()){
 context->getGraphics()->drawBitmap(0, 18 + (12 * (position - positionScreen)), bmp_wska);
 }else{
 context->getGraphics()->drawBitmap(0, 18 + (12 * (position - positionScreen)), bmp_cross);
 }
 }

 context->getGraphics()->clsRectAbs(118, 15, 128, 64);

 int w = (40 * position) / (menuUnitsIdx + 1); //obliczanie wymiarow paska pozycji

 context->getGraphics()->drawRectAbs(120, 17, 126, 17);
 context->getGraphics()->drawRectAbs(120, 60, 126, 60);
 context->getGraphics()->drawRectAbs(120, 17, 120, 60);
 context->getGraphics()->drawRectAbs(126, 17, 126, 60); //122-124, 19-58

 context->getGraphics()->drawRectAbs(122, 19 + w, 124, 19 + w + (39 / (menuUnitsIdx + 1))); //rysowanie paska pozycji

 positionLast = position;
 }

 char* UI_MENU::getPositionName(UI_ELEMENT * posi){
 return posi->getName();
 }
 */
