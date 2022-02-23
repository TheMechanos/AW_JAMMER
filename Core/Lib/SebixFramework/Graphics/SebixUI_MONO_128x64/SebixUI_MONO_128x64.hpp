/*
 * menu.hpp
 *
 *  Created on: 20.08.2019
 *      Author: SHON
 */

#ifndef SEBIX_COG_UI_HPP_
#define SEBIX_COG_UI_HPP_

#include <BasicTypes/Key/ButtonClick.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <Encoder/Encoder.hpp>
#include <stdlib.h>

#include <System.hpp>

#include <Parameters/ParameterLogical.hpp>

#include <Generic/GenericRTC.hpp>
#include <Peripheral/GPIO/IO_Pin.hpp>

#include <Graphics/Data/ImageFontTypes.hpp>

#include <Displays/MONO/GenericMono.hpp>
#include <Graphics/Graphics.hpp>





class UIElementGeneric;

class ContextManager{
public:
	ContextManager()=default;
	ContextManager(GenericMonoLCD* glcd, ENCODER* encoder, OUTPUT_ADVENCED* buzzer, BUTTON_CLICK* ok, BUTTON_CLICK * exit, TIME* sysTime=0);

	void setFirst(UIElementGeneric* first);

	void iterate();
	void iterateForceRef();

	void select(UIElementGeneric* target);
	void back();
	void home();

	uint8_t getStackPosition();

	bool isEmpty();

	UIElementGeneric* getActual();

	GenericMonoLCD*  getDisp(){return glcd;}
	GraphicsMono* getGraphics(){return &graphics;};
	ENCODER*     getEncoder(){return encoder;}
	OUTPUT_ADVENCED*  getBuzzer(){return buzzer;}
	BUTTON_CLICK*     getButtonOk(){return buttonOK;}
	BUTTON_CLICK*     getButtonExit(){return buttonExit;}
	TIME*        getTime(){return sysTime;}

private:

	uint8_t stack_position;
	static const uint8_t UI_CONTEXT_STACK_SIZE=20;
	UIElementGeneric* UI_stack[UI_CONTEXT_STACK_SIZE];

	GenericMonoLCD * glcd;
	GraphicsMono graphics = GraphicsMono(0);
	ENCODER *encoder;
	OUTPUT_ADVENCED *buzzer;
	BUTTON_CLICK *buttonOK;
	BUTTON_CLICK *buttonExit;
	TIME* sysTime;
};



/*
class ERROR_SCREEN : public UI_ELEMENT{
public:
	ERROR_SCREEN(const char* name, uint32_t timeout=0);
	void iterate(CONTEXT_MANAGER* context)=0;
private:

	void initialize(CONTEXT_MANAGER* context)=0;
	void exiting(CONTEXT_MANAGER* context)=0;
};
*/

class UIElementGeneric{
public:
	friend class ContextManager;

	UIElementGeneric()=default;
	UIElementGeneric(const char* name, uint32_t timeout=0);

	char* getName(){return name;};
	void setName(char* name){this->name = name;};

	void setEnabled(bool enabled){this->enabled=enabled;};
	bool isEnabled(){return enabled;};

	void setVisible(bool visible){this->visible=visible;};
	bool isVisible(){return visible;};

	void setSkipping(bool skipping){this->skipping=skipping;};
	bool isSkipping(){return skipping;};

	void UIinit(ContextManager* context);
	void UIreiterate(ContextManager* context);
	void UIexit(ContextManager* context);

	virtual ~UIElementGeneric(){};

	bool isTimeOutExpiried(ContextManager* context);

	void reDraw(){isToReDraw=true;}

protected:

	bool isInitialized(){return initialized;};
	void deInitialize(){initialized=false;};

	void drawHeader(ContextManager* context);

	void configTimeIterateInterval(uint16_t timeIterateInterval){this->timeIterateInterval = timeIterateInterval;};
	void configReDrawInterval(uint16_t reDrawInterval){this->reDrawInterval = reDrawInterval;};

	void configUIComponents(bool useEncoder, bool useOkKey, bool useExitKey);


	uint32_t getLastAction(){return lastAction;}

	bool useEncoder;
	bool useOkKey;
	bool useExitKey;


private:
	virtual void initialize(ContextManager* context)=0;
	virtual void iterate(ContextManager* context){};
	virtual void exiting(ContextManager* context){};
	virtual void backFromAbove(ContextManager* context){};

	virtual void timeIterate(ContextManager* context){};
	virtual void onTimeout(ContextManager* context){};
	virtual void onMinuteChangeIterate(ContextManager* context){};
	virtual void onExitKeyPressed(ContextManager* context){};
	virtual void onOKKeyPressed(ContextManager* context){}	;
	virtual void onEncoderChange(ContextManager* context){};
	virtual void paint(ContextManager* context)=0;

	void refLastAction(){lastAction=HAL_GetTick();}

	bool enabled;
	bool visible;
	bool skipping;

	char * name;

	uint32_t timeout;
	uint32_t lastAction;

	bool initialized;

	uint16_t timeIterateInterval;
	uint32_t timeIterateLastTime;

	uint16_t reDrawInterval;
	uint32_t reDrawLastTime;

	uint8_t lastMinute;
	int32_t lastEncoder;

	bool isToReDraw;
	bool isDrawed;

};























#endif /* SEBIX_COG_UI_HPP_ */
