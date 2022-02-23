/*
 * TimwePWM.cpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#include "TimerPWM.hpp"
#include "Peripheral/GPIO/PIN.hpp"


TimerPWM::TimerPWM(TIM_TypeDef* instance, uint16_t prescaler, uint16_t peroid, CounterMode cmode, ClockDivision cdiv, AutoReloadPreload cauto){
	handler.Instance = instance;
	handler.Init.Prescaler = prescaler;
	handler.Init.Period = peroid;
	handler.Init.CounterMode = (uint32_t)cmode;
	handler.Init.ClockDivision = (uint32_t)cdiv;
	handler.Init.AutoReloadPreload = (uint32_t)cauto;
}

void TimerPWM::init(){
	HAL_TIM_PWM_Init(&handler);
}

TIM_HandleTypeDef* TimerPWM::getHandler(){
	return &handler;
}

void TimerPWM::setPrescaler(uint16_t prescaler){
	HAL_TIM_PWM_Stop(&handler, TIM_CHANNEL_ALL);
	handler.Init.Prescaler = prescaler;
	HAL_TIM_PWM_Init(&handler);
}

void TimerPWM::setPeroid(uint16_t peroid){
	HAL_TIM_PWM_Stop(&handler, TIM_CHANNEL_ALL);
	handler.Init.Period = peroid;
	HAL_TIM_PWM_Init(&handler);
}

uint16_t TimerPWM::getPeroid(){
	return handler.Init.Period;
}





TimerPWMChannel::TimerPWMChannel(TimerPWM* timer, PIN* pin, Channel channel, Mode mode){
	this->timer = timer;
	this->pin = pin;
	this->channel = channel;
	this->mode = mode;

	initStructure.OCMode = (uint32_t)mode;
	initStructure.Pulse = 0;
	initStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	initStructure.OCFastMode = TIM_OCFAST_DISABLE;
}

void TimerPWMChannel::init(){
	GPIO_InitTypeDef p;
	p.Mode = GPIO_MODE_AF_PP;
	p.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pin->Init(&p);

	HAL_TIM_PWM_ConfigChannel(timer->getHandler(), &initStructure, (uint32_t)channel);
	HAL_TIM_PWM_Start(timer->getHandler(), (uint32_t)channel);
}


void TimerPWMChannel::set(uint16_t val){
	__HAL_TIM_SET_COMPARE(timer->getHandler(), (uint32_t) channel, val);
}

uint16_t TimerPWMChannel::get(){
	return __HAL_TIM_GET_COMPARE(timer->getHandler(), (uint32_t) channel);
}


void TimerPWMChannel::setPercent(uint8_t percent){
	if(percent > 100)return;
	set(getTimer()->getPeroid() * percent / 100);
}



void TimerPWMChannel::enable(){
	HAL_TIM_PWM_Start(timer->getHandler(), (uint32_t) channel);
}
void TimerPWMChannel::disable(){
	HAL_TIM_PWM_Stop(timer->getHandler(), (uint32_t) channel);
}

TimerPWM* TimerPWMChannel::getTimer(){
	return timer;
}

TIM_OC_InitTypeDef* TimerPWMChannel::getInitStructure(){
	return &initStructure;
}


