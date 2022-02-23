/*
 * ParameterNumerical.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERNUMERICAL_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERNUMERICAL_HPP_

#include <Parameters/ParameterNumerical.hpp>

#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/Message/Message.hpp>
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/ActionEntry/ActionEntry.hpp>
#include "../../SebixUI_MONO_128x64.hpp"



class UIParameterNumerical;

class UIParameterNumericalListener{
public:
	virtual void handle(UIParameterNumerical * instance)=0;
	virtual ~UIParameterNumericalListener(){};
};

class UIParameterNumerical : public UIElementGeneric{

public:
	UIParameterNumerical();
	UIParameterNumerical(const char* name, const char* description, ParameterNumerical* param, int32_t step, const char* unit,
			uint32_t timeout=0);



	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context){}
	virtual void paint(ContextManager* context);
	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);
	virtual void onEncoderChange(ContextManager* context);

	void registerActionListener(UIParameterNumericalListener* listener){this->listener=listener;};

	void paramtotext(char * buf);

private:
	char* description;
	char* unit;
	int32_t step;

	ParameterNumerical* param;

	int32_t tempparam;

	UIParameterNumericalListener* listener;

};



#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_PARAMETERNUMERICAL_HPP_ */
