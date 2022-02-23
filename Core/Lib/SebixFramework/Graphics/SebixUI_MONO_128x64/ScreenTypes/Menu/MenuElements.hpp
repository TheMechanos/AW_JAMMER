/*
 * MenuElements.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_MENUELEMENTS_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_MENUELEMENTS_HPP_

#include <Graphics/SebixUI_MONO_128x64/SebixUI_MONO_128x64.hpp>
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/Parameter/ParameterCheckbox.hpp>
#include <Graphics/SebixUI_MONO_128x64/ScreenTypes/MenuText.hpp>

#include "MenuGeneric.hpp"

#include <Generic/GenericRTC.hpp>

class UIMenuElements : public UIMenuGeneric{

public:
	UIMenuElements(const char* name, uint32_t timeout=0);//Konstruktor - Nazwa menu, Wska¿nik do elementów, d³ugoœc menu, czas dostepnosci

	virtual void onExitKeyPressed(ContextManager* context);
	virtual void onOKKeyPressed(ContextManager* context);

	virtual uint8_t getLength();

	void addElement(UIElementGeneric * elem);
	UIElementGeneric* getUnit(uint8_t position);

private:

	virtual char* getPositionName(uint8_t posi);
	virtual bool  isPositionEnabled(uint8_t posi);

	virtual bool  isPositionCheckbox(uint8_t posi);
	virtual bool  isPositionCheckboxChecked(uint8_t posi);

	virtual bool  isPositionText(uint8_t posi);
	virtual bool  isPositionLineUp(uint8_t posi);
	virtual bool  isPositionLineDown(uint8_t posi);

	static const uint8_t MENU_UNITS_MAX=26;
	UIElementGeneric * menuUnits[MENU_UNITS_MAX];
	int8_t menuUnitsIdx;

};



#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_MENU_HPP_ */
