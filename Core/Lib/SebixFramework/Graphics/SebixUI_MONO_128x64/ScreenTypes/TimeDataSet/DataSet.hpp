/*
 * DataSet.hpp
 *
 *  Created on: 19.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_TIMEDATASET_DATASET_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_TIMEDATASET_DATASET_HPP_

#include "../../SebixUI_MONO_128x64.hpp"
#include "../ActionEntry/ActionEntry.hpp"

#include <Generic/GenericRTC.hpp>

class UIParameterData;

class UIParameterDataListener{
public:
	virtual void handle(UIParameterData * instance)=0;
	virtual ~UIParameterDataListener(){};
};

class UIParameterData : public UIElementGeneric{

public:
	UIParameterData(const char* name, const char* description, DATE * date, uint32_t timeout=0);

	virtual void initialize(ContextManager* context);
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context);
	virtual void paint(ContextManager* context);

	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);
	virtual void onEncoderChange(ContextManager* context);

	DATE* getDate();

	void registerActionListener(UIParameterDataListener* listener){this->listener=listener;};

private:
	char* description;

	DATE* date;

	uint16_t dateRaw[3];
	uint8_t dateIdx;

	bool refdate;

	UIParameterDataListener * listener;

};




#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_TIMEDATASET_DATASET_HPP_ */
