/*
 * Button.hpp
 *
 *  Created on: 13.11.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_KEY_BUTTON_HPP_
#define BASICTYPES_KEY_BUTTON_HPP_


#include <BasicTypes/IO/Input.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <System.hpp>

#include <Music/MusicPlayer.hpp>
#include <Music/notesAndSong.hpp>

class BUTTON : public INPUT_BASIC{
public:
	enum class ACTION{
		NONE, RELEASED, PRESSED
	};

	BUTTON()=default;
	BUTTON(PIN * pin, uint16_t debounce, PULL pinpull=PULL::UP, LOGIC logic=LOGIC::REVERSE);

	void configActionValidTime(uint32_t actionValidTime);

	void registerBuzzer(OUTPUT_ADVENCED* buzzer, uint8_t buzTime);
	void registerMusic(MusicPlayer* player, Song* song);

	void init();

	void iterate(uint32_t TICK);

	bool isReleased();
	bool isPressed();

	bool isAction(ACTION action);
	ACTION getAction();

	void buzz();

	void disable();
	void enable();

protected:

	bool state;
	bool lastTempState;

	uint32_t lastTempStateChange;
	uint32_t lastStateChange;
	uint32_t lastActionTime;

	uint32_t actionValidTime;
	uint16_t debounce;

	bool enabled;

private:

	ACTION action;

	OUTPUT_ADVENCED* buzzer;
	uint8_t buzTime;
	MusicPlayer* player;
	Song* song;

};



#endif /* BASICTYPES_KEY_BUTTON_HPP_ */
