/*
 * ParameterLogical.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERCHECKBOX_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERCHECKBOX_HPP_

#include "../../SebixUI_MONO_128x64.hpp"
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/ActionEntry/ActionEntry.hpp>

class UIParameterCheckbox;

class UIParameterCheckboxListener{
public:
	virtual void handle(UIParameterCheckbox * instance)=0;
	virtual ~UIParameterCheckboxListener(){};
};

class UIParameterCheckbox: public UIElementGeneric{ //Klasa elementu menu
public:
	UIParameterCheckbox():UIElementGeneric("",0){};
	UIParameterCheckbox(const char* name, PARAMETER_LOGICAL* param);   // Konstruktor typu "SELECTABLE"

	bool isSelected();
	void setState(bool state);

	virtual void initialize(ContextManager* context){};
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context){};
	virtual void paint(ContextManager* context){};

	void registerActionListener(UIParameterCheckboxListener* listener){this->listener=listener;};

	void load();

private:
	PARAMETER_LOGICAL* param;

	UIParameterCheckboxListener* listener;
};







#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERCHECKBOX_HPP_ */
