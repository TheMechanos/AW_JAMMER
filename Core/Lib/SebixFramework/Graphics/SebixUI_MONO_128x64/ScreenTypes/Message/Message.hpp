/*
 * Statement.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_MESSAGE_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_MESSAGE_HPP_

#include <System.hpp>
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/ActionEntry/ActionEntry.hpp>
#include "../../SebixUI_MONO_128x64.hpp"

class UIMessage;

class UIMessageListener{
public:
	virtual void handle(UIMessage * instance)=0;
	virtual ~UIMessageListener(){};
};

class UIMessage : public UIElementGeneric{
public:
	UIMessage(const char* name, const char* description, uint16_t time, bool is_exit_statement,OUTPUT_ADVENCED::SEQUENCE* buzseq=0, bool skipable=true);

	char* getDescription();
	uint16_t getTime();
	bool is_skipable();
	void setImage(tImage bmp);

	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context);
	virtual void paint(ContextManager* context);
	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);

	void registerActionListener(UIMessageListener* listener){this->listener=listener;};

private:
	char* description;
	uint32_t time;
	bool skipable;
	tImage bmp;
	bool is_exit_statement;
	OUTPUT_ADVENCED::SEQUENCE* buzseq;

	UIMessageListener* listener;
};


#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_MESSAGE_HPP_ */
