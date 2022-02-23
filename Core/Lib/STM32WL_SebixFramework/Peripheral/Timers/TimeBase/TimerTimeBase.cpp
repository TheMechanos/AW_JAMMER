/*
 * TimerTImeBase.cpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#include "TimerTimeBase.hpp"



TimerTimeBase::TimerTimeBase(TIM_TypeDef* instance, uint16_t prescaler, uint16_t peroid, CounterMode cmode, ClockDivision cdiv, AutoReloadPreload cauto){
	handler.Instance = instance;
	handler.Init.Prescaler = prescaler;
	handler.Init.Period = peroid;
	handler.Init.CounterMode = (uint32_t)cmode;
	handler.Init.ClockDivision = (uint32_t)cdiv;
	handler.Init.AutoReloadPreload = (uint32_t)cauto;

	this->IRQn = (IRQn_Type)0;
	this->PreemptPriority = 0;
	this->listener = 0;
}

void TimerTimeBase::configIRQn(IRQn_Type IRQn, uint8_t PreemptPriority, TimerTimeBaseListener* listener){
	this->IRQn = IRQn;
	this->PreemptPriority = PreemptPriority;
	this->listener = listener;
}

void TimerTimeBase::init(){

	HAL_TIM_Base_Init(&handler);

	HAL_NVIC_SetPriority(IRQn, PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(IRQn);
}

void TimerTimeBase::start(){
	HAL_TIM_Base_Start_IT(&handler);
}

void TimerTimeBase::stop(){
	HAL_TIM_Base_Stop_IT(&handler);
}


TIM_HandleTypeDef* TimerTimeBase::getHandler(){
	return &handler;
}

void TimerTimeBase::setPrescaler(uint16_t prescaler){
	//stop();
	//HAL_TIM_Base_DeInit(&handler);

	//handler.Instance->CNT=0;
	//handler.Init.Prescaler = prescaler;
	//HAL_TIM_Base_Init(&handler);
}

void TimerTimeBase::setPeroid(uint16_t peroid){
	///stop();
	//HAL_TIM_Base_DeInit(&handler);

	handler.Instance->CNT=0;
	handler.Init.Period = peroid;
	HAL_TIM_Base_Init(&handler);
}


void TimerTimeBase::IRQHandler(){
	HAL_TIM_IRQHandler(&handler);
}

void TimerTimeBase::periodElapsed(){
	if(listener != 0)
		listener->handleTimerIrQn();
}

