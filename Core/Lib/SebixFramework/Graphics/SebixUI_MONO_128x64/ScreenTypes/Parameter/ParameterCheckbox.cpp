/*
 * ParameterCheckbox.cpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */


#include "ParameterCheckbox.hpp"

UIParameterCheckbox::UIParameterCheckbox(const char* name, PARAMETER_LOGICAL* param) :
		UIElementGeneric(name, 0){
	this->param=param;
	this->listener=0;
}
bool UIParameterCheckbox::isSelected(){
	PARAMETER_LOGICAL_EEPROM* parame = dynamic_cast<PARAMETER_LOGICAL_EEPROM*> (param);
	if(parame){
		parame->load();
	}

	return param->get();
}
void UIParameterCheckbox::setState(bool state){
	param->set(state);
}
void UIParameterCheckbox::iterate(ContextManager* context){

	if(param->get()){
		param->set(false);
	}else{
		param->set(true);
	}


	PARAMETER_LOGICAL_EEPROM* parame = dynamic_cast<PARAMETER_LOGICAL_EEPROM*> (param);
	if(parame){
		parame->save();
	}

	context->back();
	if(listener)listener->handle(this);
}


