/*
 * PIN.hpp
 *
 *  Created on: 19.05.2020
 *      Author: SHON
 */

#ifndef GPIO_PIN_HPP_
#define GPIO_PIN_HPP_

#include <stm32wlxx.h>

class PIN{
public:
	PIN() = default;

	PIN(GPIO_TypeDef * gpio, uint16_t pin, uint8_t alternate=0){
		this->gpio=gpio;
		this->pin=pin;
		this->alternate=alternate;
	}

	void Init(GPIO_InitTypeDef* InitTypdef){
		InitTypdef->Pin=pin;
		InitTypdef->Alternate=alternate;
		HAL_GPIO_Init(gpio, InitTypdef);
	}

	GPIO_TypeDef* getGPIO(){return gpio;}
	uint16_t getPIN(){return pin;}

private:
	GPIO_TypeDef * gpio;
	uint16_t pin;
	uint8_t alternate;
};




#endif /* GPIO_PIN_HPP_ */
