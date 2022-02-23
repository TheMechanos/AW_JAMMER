/*
 * encoder.cpp
 *
 *  Created on: 02.01.2020
 *      Author: SHON
 */

#include "TimerEncoder.hpp"


const uint16_t TIMER_ENCODER::ENDODER_PEROID;


TIMER_ENCODER::TIMER_ENCODER(PIN *pin1, PIN *pin2, TIM_TypeDef * TIM, ENCODER_DIR_LOGIC enc_dir){
	this->pin1=pin1;
	this->pin2=pin2;
	this->TIM = TIM;
	this->enc_dir_logic = enc_dir;
	this->divider=1;
}

void TIMER_ENCODER::init(){
	GPIO_InitTypeDef inp;
	inp.Mode = GPIO_MODE_AF_PP;
	inp.Pull = GPIO_PULLUP;
	inp.Speed = GPIO_SPEED_FREQ_HIGH;

	pin1->Init(&inp);
	pin2->Init(&inp);

	TimEncoderStruct.Instance=TIM;
	TimEncoderStruct.Init.Period = ENDODER_PEROID;
	TimEncoderStruct.Init.Prescaler = divider;
	TimEncoderStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimEncoderStruct.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	TimEncoderStruct.Init.RepetitionCounter=0;

	EncoderStruct.IC2Polarity = TIM_ICPOLARITY_FALLING;
	if(enc_dir_logic==ENC_DIR_REVERSE)EncoderStruct.IC1Polarity=TIM_ICPOLARITY_RISING;
	else EncoderStruct.IC1Polarity=TIM_ICPOLARITY_FALLING;

	EncoderStruct.EncoderMode = TIM_ENCODERMODE_TI12;
	EncoderStruct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	EncoderStruct.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	EncoderStruct.IC1Prescaler = TIM_ICPSC_DIV1;
	EncoderStruct.IC2Prescaler = TIM_ICPSC_DIV1;
	EncoderStruct.IC1Filter = 15;
	EncoderStruct.IC2Filter = 15;

	HAL_TIM_Encoder_Init(&TimEncoderStruct, &EncoderStruct);

	HAL_TIM_Encoder_Start(&TimEncoderStruct, TIM_CHANNEL_ALL);

	TIM->CNT=0;
}

uint32_t TIMER_ENCODER::getRawValue(){
	return TIM->CNT;
}

void TIMER_ENCODER::setRawValue(uint32_t val){
	TIM->CNT = val;
}
void TIMER_ENCODER::setDivider(uint16_t divider){
	this->divider=divider;
	TimEncoderStruct.Init.Prescaler = divider;
	HAL_TIM_Encoder_Init(&TimEncoderStruct, &EncoderStruct);
	HAL_TIM_Encoder_Start(&TimEncoderStruct, TIM_CHANNEL_ALL);
}



uint16_t TIMER_ENCODER::getPeroid(){
	return ENDODER_PEROID;
}



