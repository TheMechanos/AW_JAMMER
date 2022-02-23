/*
 * MenuBasic.hpp
 *
 *  Created on: 04.03.2021
 *      Author: SHON
 */

#ifndef GRAPHICS_SEBIXUI_MONO_128X64_SCREENTYPES_MENU_CUSTOM_MENUCUSTOM_HPP_
#define GRAPHICS_SEBIXUI_MONO_128X64_SCREENTYPES_MENU_CUSTOM_MENUCUSTOM_HPP_


#include "../../SebixUI_MONO_128x64.hpp"

#include <Generic/GenericRTC.hpp>

class UIMenuGeneric;

class UIMenuListener{
public:
	virtual void handle(UIMenuGeneric * instance, uint8_t position)=0;
	virtual ~UIMenuListener(){};
};


class UIMenuGeneric : public UIElementGeneric{

public:
	UIMenuGeneric(const char* name, uint32_t timeout=0);

	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context);

	virtual void onMinuteChangeIterate(ContextManager* context);
	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);
	virtual void onEncoderChange(ContextManager* context);

	virtual void paint(ContextManager* context);


	void setShowingClock(bool showingClock){this->showingClock=showingClock;};

	void registerListener(UIMenuListener* listener);

	virtual uint8_t getLength()=0;

protected:
	int8_t position;
	int8_t positionScreen;

private:
	virtual char* getPositionName(uint8_t posi){return 0;};
	virtual bool  isPositionEnabled(uint8_t posi){return true;};

	virtual bool  isPositionCheckbox(uint8_t posi){return false;};
	virtual bool  isPositionCheckboxChecked(uint8_t posi){return false;};

	virtual bool  isPositionText(uint8_t posi){return true;};
	virtual bool  isPositionLineUp(uint8_t posi){return false;};
	virtual bool  isPositionLineDown(uint8_t posi){return false;};

	bool showingClock;

	UIMenuListener* listener;
};





#endif /* GRAPHICS_SEBIXUI_MONO_128X64_SCREENTYPES_MENU_CUSTOM_MENUCUSTOM_HPP_ */
