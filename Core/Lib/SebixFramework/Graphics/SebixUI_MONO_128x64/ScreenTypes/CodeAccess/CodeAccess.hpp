/*
 * CodeAcces.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_CODEACCES_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_CODEACCES_HPP_

#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/Message/Message.hpp>
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/ActionEntry/ActionEntry.hpp>
#include "../../SebixUI_MONO_128x64.hpp"


class UICodeAccess;

class UICodeAccessListener{
public:
	virtual void handle(UICodeAccess * instance)=0;
	virtual ~UICodeAccessListener(){};
};


class UICodeAccess : public UIElementGeneric{

public:
	UICodeAccess(const char* name, const char* description, uint16_t code, uint32_t timeout=0);

	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context){};
	virtual void exiting(ContextManager* context){};
	virtual void backFromAbove(ContextManager* context);

	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);
	virtual void onEncoderChange(ContextManager* context);
	virtual void paint(ContextManager* context);

	void registerChild(UIElementGeneric* next);

	void registerActionListener(UICodeAccessListener* listener){this->listener=listener;};

private:
	char* description;

	static OUTPUT_ADVENCED::SEQUENCE_SECTION sequenceBadCodeSection[];
	static OUTPUT_ADVENCED::SEQUENCE sequenceBadCode;
	static UIMessage statementBadCode;

	UIElementGeneric* next;

	uint16_t code;


	int8_t typingCode[4];
	uint8_t actualNumber;

	UICodeAccessListener* listener;
};




#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_CODEACCES_HPP_ */
