/*
 * Input.cpp
 *
 *  Created on: 29.12.2019
 *      Author: SHON
 */

#include "IO_Pin.hpp"

INPUT_PIN::INPUT_PIN(GPIO_TypeDef * gpio, uint16_t pin, PULL pinpull){
	this->gpio = gpio;

	PinStruct.Pin = pin;
	PinStruct.Pull = (uint32_t)pinpull;
	PinStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	PinStruct.Mode = GPIO_MODE_INPUT;

}
INPUT_PIN::INPUT_PIN(PIN * pin, PULL pinpull) :
		INPUT_PIN(pin->getGPIO(), pin->getPIN()){

	PinStruct.Pull = (uint32_t)pinpull;
}

void INPUT_PIN::init(){
	HAL_GPIO_Init(gpio, &PinStruct);
}
bool INPUT_PIN::get(){
	return (HAL_GPIO_ReadPin(gpio, PinStruct.Pin));
}





OUTPUT_PIN::OUTPUT_PIN(GPIO_TypeDef * gpio, uint16_t pin, MODE pinmode){
	this->gpio=gpio;
	PinStruct.Pin=pin;
	PinStruct.Pull=GPIO_NOPULL;
	PinStruct.Speed=GPIO_SPEED_FREQ_HIGH;
	if(pinmode == MODE::ODPULLUP){
		PinStruct.Mode=(uint32_t)MODE::OD;
		PinStruct.Pull=GPIO_PULLUP;
	}else{
		PinStruct.Mode=(uint32_t)pinmode;
	}
}
OUTPUT_PIN::OUTPUT_PIN(PIN * pin, MODE pinmode):OUTPUT_PIN(pin->getGPIO(), pin->getPIN(), pinmode){

}

void OUTPUT_PIN::init(){
	HAL_GPIO_Init(gpio, &PinStruct);
}

void OUTPUT_PIN::set(bool state){
	HAL_GPIO_WritePin(gpio, PinStruct.Pin, (GPIO_PinState)(state));
}
void OUTPUT_PIN::ON(){
	set(true);
}
void OUTPUT_PIN::OFF(){
	set(false);
}
void OUTPUT_PIN::toggle(){
	HAL_GPIO_TogglePin(gpio, PinStruct.Pin);
}
bool OUTPUT_PIN::get(){
	return HAL_GPIO_ReadPin(gpio, PinStruct.Pin);
}


