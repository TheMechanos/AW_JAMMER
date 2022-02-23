/*
 * Output.hpp
 *
 *  Created on: 31.08.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_OUTPUT_HPP_
#define BASICTYPES_OUTPUT_HPP_

#include <Peripheral/GPIO/IO_Pin.hpp>
#include <Peripheral/GPIO/PIN.hpp>

#ifdef STM32F4
#include <stm32f4xx.h>
#endif

#ifdef STM32F1
#include <stm32f1xx.h>
#endif


class OUTPUT_BASIC: public OUTPUT_PIN{
public:
	enum class LOGIC{NORMAL=0, REVERSE=1};

	OUTPUT_BASIC()=default;
	OUTPUT_BASIC(GPIO_TypeDef * gpio, uint16_t pin, LOGIC logic=LOGIC::NORMAL, MODE pinmode=MODE::PP);
	OUTPUT_BASIC(PIN * pin, LOGIC logic=LOGIC::NORMAL, MODE pinmode=MODE::PP);

	void init();

	bool read();
	bool get();
	void set(bool state);

	void ON();
	void OFF();
	void toggle();

	void overrideSet(bool state);
	void overrideDisable();

protected:
	LOGIC logic;

	bool override;
	bool state;

};

class OUTPUT_ADVENCED : public OUTPUT_BASIC{
public:

	typedef struct{
		bool state;
		uint16_t time;
	}SEQUENCE_SECTION;

	typedef struct{
		SEQUENCE_SECTION* section;
		uint8_t length;
	}SEQUENCE;

	enum class PROCEDURE{MANUAL, BLINKING, NUMBER_BLINK, SEQUENCE};
	enum class CYCLE{OFF=0, ON=1};

	OUTPUT_ADVENCED()=default;
	OUTPUT_ADVENCED(GPIO_TypeDef * gpio, uint16_t pin, LOGIC logic=LOGIC::NORMAL, MODE pinmode=MODE::PP);
	OUTPUT_ADVENCED(PIN * pin, LOGIC logic=LOGIC::NORMAL, MODE pinmode=MODE::PP);

	void ON();
	void OFF();

	void blink(uint32_t time, CYCLE cycl = CYCLE::ON);
	void blink(uint32_t on_time, uint32_t off_time, CYCLE cycl = CYCLE::ON);

	void blinkNumber(int number, uint32_t time, CYCLE cycl = CYCLE::ON);
	void blinkNumber(int number, uint32_t on_time, uint32_t off_time, CYCLE cycl = CYCLE::ON);

	void timeON (uint32_t timeon);
	void timeOFF(uint32_t timeoff);
	void timeSET(uint32_t time, bool startvalue);
	void timeTOG(uint32_t time);

	void playSequence(SEQUENCE* sequnce, uint16_t number=1);
	void stopSequence();

	PROCEDURE getMode();

	void iterate(uint32_t TICK);

private:
	PROCEDURE procedure;
	CYCLE cycle;
	uint32_t on_time;
	uint32_t off_time;
	uint32_t lastiterate;

	int numberblink;

	SEQUENCE *sequence;
	int16_t sequence_position;
	uint16_t sequence_number;
	uint16_t sequence_time_to_go;
	uint32_t sequence_last_iterate;

};


#endif /* BASICTYPES_OUTPUT_HPP_ */
