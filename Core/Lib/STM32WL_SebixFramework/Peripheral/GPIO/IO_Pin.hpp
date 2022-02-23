/*
 * Input.hpp
 *
 *  Created on: 29.12.2019
 *      Author: SHON
 */

#ifndef SEBIXFRAMEWORK_BASICCOMPONENTS_INPUT_HPP_
#define SEBIXFRAMEWORK_BASICCOMPONENTS_INPUT_HPP_

#include <Generic/GenericIO.hpp>
#include <Peripheral/GPIO/PIN.hpp>
#include <stm32wlxx.h>




class INPUT_PIN : public INPUT{
public:
	enum class PULL{DOWN=GPIO_PULLDOWN, UP=GPIO_PULLUP, NO=GPIO_NOPULL};

	INPUT_PIN()=default;
	INPUT_PIN(GPIO_TypeDef * gpio, uint16_t pin, PULL pinpull=PULL::NO);
	INPUT_PIN(PIN * pin, PULL pinpull=PULL::NO);

	void init();
	bool get();
private:
	GPIO_TypeDef * gpio;
	GPIO_InitTypeDef PinStruct;

};



class OUTPUT_PIN : public OUTPUT{
public:
	enum class MODE{PP=GPIO_MODE_OUTPUT_PP, OD=GPIO_MODE_OUTPUT_OD, ODPULLUP=GPIO_MODE_OUTPUT_OD+1};

	OUTPUT_PIN()=default;
	OUTPUT_PIN(GPIO_TypeDef * gpio, uint16_t pin, MODE pinmode=MODE::PP);
	OUTPUT_PIN(PIN * pin, MODE pinmode=MODE::PP);

	void init();

	void set(bool state);
	void ON();
	void OFF();
	void toggle();
	bool get();

private:
	GPIO_TypeDef * gpio;
	GPIO_InitTypeDef PinStruct;

};



#endif /* SEBIXFRAMEWORK_BASICCOMPONENTS_INPUT_HPP_ */
