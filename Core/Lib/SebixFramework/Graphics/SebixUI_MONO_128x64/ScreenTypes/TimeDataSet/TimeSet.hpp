/*
 * TimeSet.hpp
 *
 *  Created on: 18.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_TIMESET_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_TIMESET_HPP_

#include "../../SebixUI_MONO_128x64.hpp"
#include "../ActionEntry/ActionEntry.hpp"

#include <Generic/GenericRTC.hpp>

class UIParameterTimeHMS;

class UIParameterTimeHMSListener{
public:
	virtual void handle(UIParameterTimeHMS * instance)=0;
	virtual ~UIParameterTimeHMSListener(){};
};

class UIParameterTimeHMS : public UIElementGeneric{

public:
	UIParameterTimeHMS(const char* name, const char* description, TIME * time, uint32_t timeout=0);

	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context);

	virtual void paint(ContextManager* context);
	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);
	virtual void onEncoderChange(ContextManager* context);

	TIME* getTime();

	void registerActionListener(UIParameterTimeHMSListener* listener){this->listener=listener;};

private:
	char* description;

	TIME* time;

	uint8_t timeRaw[3];
	uint8_t timeIdx;

	bool reftim;

	UIParameterTimeHMSListener * listener;

};




#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_TIMESET_HPP_ */
