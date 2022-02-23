/*
 * ClickButton.hpp
 *
 *  Created on: 13.11.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_KEY_BUTTONCLICK_HPP_
#define BASICTYPES_KEY_BUTTONCLICK_HPP_

#include <BasicTypes/Key/Button.hpp>
#include <BasicTypes/IO/Input.hpp>
#include <System.hpp>

#include <stdio.h>

class BUTTON_CLICK : public BUTTON{
public:
	enum class ACTION{
		NONE, RELEASED, PRESSED, MULTICLICK, LONGHOLDING
	};

	BUTTON_CLICK()=default;
	BUTTON_CLICK(PIN * pin, uint8_t debounce, PULL pinpull=PULL::UP, LOGIC logic=LOGIC::REVERSE);

	void configFader(uint32_t faderStartInterval, uint32_t faderEndInterval, uint32_t faderStartTime, uint32_t faderEndTime);
	void configMultiClick(uint32_t multiclickTime);
	void configLongClick(uint32_t longClickTime);

	void iterate(uint32_t TICK);

	bool isReleased();
	bool isPressed();
	uint8_t isMultiClick(uint8_t clickTarget=0);
	bool isLongHolding();

	bool isLongPress(uint16_t pressTime);
	bool isLongClick(uint16_t minPressTime, uint16_t maxPressTime);

	bool isAction(ACTION action);
	ACTION getAction();

	bool isFader();
	bool isClicked();

private:


	uint8_t clickCount;
	uint8_t clicks;

	uint32_t lastPressTime;


	uint32_t multiclickTime;
	uint32_t longClickTime;
	bool lockLongClick;

	uint32_t faderStartInterval;
	uint32_t faderEndInterval;
	uint32_t faderStartTime;
	uint32_t faderEndTime;
	uint32_t lastFaderTime;

	ACTION action;

};




#endif /* BASICTYPES_KEY_BUTTONCLICK_HPP_ */
