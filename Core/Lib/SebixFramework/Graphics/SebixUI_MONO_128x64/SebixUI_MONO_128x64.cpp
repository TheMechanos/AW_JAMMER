/*
 * menu.cpp
 *
 *  Created on: 20.08.2019
 *      Author: SHON
 */

#include <Graphics/SebixUI_MONO_128x64/SebixUI_MONO_128x64.hpp>



UIElementGeneric::UIElementGeneric(const char* name, uint32_t timeout){
	this->name = (char*) name;
	this->timeout = timeout;

	this->enabled = true;
	this->visible = true;
	this->skipping = false;

	this->initialized = false;
	this->lastAction = 0;

	this->timeIterateInterval = 0;
	this->timeIterateLastTime = 0;

	this->reDrawInterval = 0;
	this->reDrawLastTime = 0;

	this->useEncoder = true;
	this->useExitKey = true;
	this->useOkKey = true;

	this->isToReDraw = true;
	this->isDrawed = false;

	this->lastMinute = 100;
	this->lastEncoder= -1111111;
}


void UIElementGeneric::UIinit(ContextManager* context){
	initialized=true;
	isToReDraw = true;
	refLastAction();
	initialize(context);
}

void UIElementGeneric::UIreiterate(ContextManager* context){
	if(useOkKey && context->getButtonOk()->isPressed()){
		onOKKeyPressed(context);
		refLastAction();
	}

	if(useExitKey && context->getButtonExit()->isPressed()){
		onExitKeyPressed(context);
		refLastAction();
	}

	if(useEncoder){
		int32_t encoder = context->getEncoder()->getValue();
		if(encoder != lastEncoder){
			lastEncoder = encoder;
			onEncoderChange(context);
			refLastAction();
		}
	}

	if(reDrawInterval && reDrawInterval <= (System::getTick() - reDrawLastTime)){
		reDrawLastTime = System::getTick();
		reDraw();
	}

	if(isToReDraw){
		if(!isDrawed){
			context->getGraphics()->cls();
			paint(context);
			isDrawed=true;
		}
		if(context->getGraphics()->ref()){
			isToReDraw=false;
			isDrawed=false;
			refLastAction();
		}
	}

	if(context->getTime()->getMinute() != lastMinute){
		lastMinute = context->getTime()->getMinute();
		onMinuteChangeIterate(context);
	}

	if(timeIterateInterval && timeIterateInterval <= (System::getTick() - timeIterateLastTime)){
		timeIterateLastTime = System::getTick();
		timeIterate(context);
	}

	iterate(context);

}

void UIElementGeneric::UIexit(ContextManager* context){
	initialized=false;
	exiting(context);
}

void UIElementGeneric::drawHeader(ContextManager* context){
	context->getGraphics()->drawText(2, 2, getName(), font_8pix);
	context->getGraphics()->drawRectAbs(1, 0, 126, 0);
	context->getGraphics()->drawRectAbs(1, 12, 126, 12);
}

void UIElementGeneric::configUIComponents(bool useEncoder, bool useOkKey, bool useExitKey){
	this->useEncoder = useEncoder;
	this->useExitKey = useExitKey;
	this->useOkKey = useOkKey;
}

bool UIElementGeneric::isTimeOutExpiried(ContextManager* context){
	if(timeout > 0){
		if(timeout < HAL_GetTick() - lastAction){
			onTimeout(context);
			return true;
		}
	}
	return false;
}






ContextManager::ContextManager(GenericMonoLCD* glcd, ENCODER* encoder, OUTPUT_ADVENCED* buzzer, BUTTON_CLICK* ok, BUTTON_CLICK * exit, TIME* sysTime){
	this->glcd = glcd;
	this->encoder = encoder;
	this->buzzer = buzzer;
	this->buttonOK = ok;
	this->buttonExit = exit;
	this->sysTime = sysTime;

	graphics = GraphicsMono(glcd);

	stack_position = 0;
}

void ContextManager::setFirst(UIElementGeneric* first){
	UI_stack[0]=first;
}

UIElementGeneric* ContextManager::getActual(){
	return UI_stack[stack_position];
}

uint8_t ContextManager::getStackPosition(){
	return stack_position;
}

void ContextManager::iterateForceRef(){
	getActual()->UIinit(this);
	return iterate();
}

void ContextManager::iterate(){
	if(UI_stack[0] == 0)return;

	if(!getActual()->isInitialized()){
		getActual()->UIinit(this);
	}
	if(getActual()->isTimeOutExpiried(this))home();

	getActual()->UIreiterate(this);
}

bool ContextManager::isEmpty(){
	return stack_position == 0;
}

void ContextManager::select(UIElementGeneric* target){
	if(target==0)return;
	if(stack_position>=UI_CONTEXT_STACK_SIZE)return;

	getActual()->deInitialize();

	stack_position++;
	UI_stack[stack_position]=target;
}

void ContextManager::home(){
	while(stack_position)back();
}

void ContextManager::back(){
	if(stack_position==0)return;
	UI_stack[stack_position]->UIexit(this);
	UI_stack[stack_position]=0;
	stack_position--;
	getActual()->backFromAbove(this);
}






























