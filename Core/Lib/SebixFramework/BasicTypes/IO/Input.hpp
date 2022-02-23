/*
 * Input.hpp
 *
 *  Created on: 29.12.2019
 *      Author: SHON
 */

#ifndef SEBIXFRAMEWORK_BASICTYPES_INPUT_HPP_
#define SEBIXFRAMEWORK_BASICTYPES_INPUT_HPP_

#include <Peripheral/GPIO/IO_Pin.hpp>
#include <Peripheral/GPIO/PIN.hpp>

#ifdef STM32F4
#include <stm32f4xx.h>
#endif

#ifdef STM32F1
#include <stm32f1xx.h>
#endif


class INPUT_BASIC : public INPUT_PIN{
public:
	enum class LOGIC{NORMAL=0, REVERSE=1};

	INPUT_BASIC()=default;
	INPUT_BASIC(GPIO_TypeDef * gpio, uint16_t pin, PULL pinpull=PULL::NO, LOGIC logic=LOGIC::NORMAL);
	INPUT_BASIC(PIN * pin, PULL pinpull=PULL::NO, LOGIC logic=LOGIC::NORMAL);

	bool get();
	bool getPinState();

private:
	LOGIC logic;
};



class INPUT_BUFFERED : public INPUT_BASIC{
public:
	INPUT_BUFFERED()=default;
	INPUT_BUFFERED(uint16_t measureIterval, uint8_t averagingNumber, PIN * pin, PULL pinpull=PULL::NO, LOGIC logic=LOGIC::NORMAL);

	bool get();

	void iterate(uint32_t TICK);

private:
	uint16_t measureIterval;
	uint8_t averagingNumber;
	uint32_t lastIterate;

	bool lastState;

	uint32_t measures;

	static const uint8_t MAX_AVERAGING=32;

};

class INPUT_DEBOUNCED : public INPUT_BASIC{
public:
	INPUT_DEBOUNCED()=default;
	INPUT_DEBOUNCED(uint16_t debounceTime, PIN * pin, PULL pinpull=PULL::NO, LOGIC logic=LOGIC::NORMAL);

	bool get();

	void iterate(uint32_t TICK);

private:
	uint16_t debounceTime;
	uint32_t lastStateChange;

	bool lastTempState;
	bool state;
};




class BASIC_BINARY_INPUTS{
public:
	BASIC_BINARY_INPUTS();

	void addInput(INPUT_BASIC & a);

	uint8_t get();

private:
	INPUT_BASIC * ins[8];
	uint8_t len;
};




#endif /* SEBIXFRAMEWORK_BASICCOMPONENTS_INPUT_HPP_ */
