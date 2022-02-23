/*
 * ActionEntry.cpp
 *
 *  Created on: 16.10.2020
 *      Author: SHON
 */

#include "ActionEntry.hpp"

UIActionEntry::UIActionEntry(const char* name, uint32_t timeout): UIElementGeneric(name, timeout){
	this->listener=0;
	this->homing =false;
}

void UIActionEntry::registerActionListener(UIActionEntryListener* listener){
	this->listener=listener;
}

void UIActionEntry::setHoming(bool homing){
	this->homing = homing;
}


void UIActionEntry::iterate(ContextManager* context){
	if(listener){
		listener->handle(this);
	}

	if(homing){
		context->home();
	}else{
		context->back();
	}

}
