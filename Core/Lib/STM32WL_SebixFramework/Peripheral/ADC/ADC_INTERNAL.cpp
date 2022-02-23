/*
 * ADC_DMA.cpp
 *
 *  Created on: 31.08.2020
 *      Author: SHON
 */

#include "ADC_INTERNAL.hpp"


ADC_CHANNEL::ADC_CHANNEL(PIN* pin, uint32_t Channel, ADC_INTERNAL * ADCMaster, uint8_t Rank, uint32_t SamplingTime){
	this->pin=pin;
	this->ChannelConfig.Channel=Channel;
	this->ChannelConfig.Rank=Rank;
	this->ChannelConfig.SamplingTime=SamplingTime;
	//this->ChannelConfig.Offset=0;

	this->value=0;

	this->ADCMaster=ADCMaster;

}

void ADC_CHANNEL::init(uint32_t * value){
	this->value=value;

	if(pin){
		GPIO_InitTypeDef gp;
		gp.Mode=GPIO_MODE_ANALOG;
		gp.Pull=GPIO_NOPULL;

		pin->Init(&gp);
	}

	initChannel();
}
void ADC_CHANNEL::initChannel(){
	HAL_ADC_ConfigChannel(ADCMaster->getADCHandler(), &ChannelConfig);
}

uint16_t ADC_CHANNEL::getValue(){
	return *value;
}

uint8_t ADC_CHANNEL::getRank(){
	return ChannelConfig.Rank;
}







ADC_INTERNAL::ADC_INTERNAL(ADC_TypeDef * ADCInstance, uint32_t ADCPrescaler, uint32_t ADCResolution){
	this->ADC_Instance=ADCInstance;
	this->ADC_Prescaler=ADCPrescaler;
	this->ADC_Resolution=ADCResolution;

	this->dma = 0;

	this->ChannelsNumber=0;

	for(uint8_t q=0;q<MAX_CHANNELS;q++){
		Channels[q]=0;
		ChannelData[q]=0;
	}
}

void ADC_INTERNAL::registerDMA(DMA * dma){
	this->dma=dma;
}

void ADC_INTERNAL::init(){


	dma->configDirectionAlignment(DMA::Direction::PERIPH_TO_MEM, DMA::Mode::CIRCULAR, false, true, DMA::PeriphAlign::WORD, DMA::MemAlign::WORD);

	dma->init();
	__HAL_LINKDMA(&ADC_Handle, DMA_Handle, (*dma->getHandler()));
	dma->initInterrupt();

	ADC_Handle.Instance = ADC_Instance;
	ADC_Handle.Init.ClockPrescaler = ADC_Prescaler;
	ADC_Handle.Init.Resolution = ADC_Resolution;
	ADC_Handle.Init.ScanConvMode = ENABLE;
	ADC_Handle.Init.ContinuousConvMode = ENABLE;
	ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
	ADC_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC_Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC_Handle.Init.NbrOfConversion = ChannelsNumber;
	ADC_Handle.Init.DMAContinuousRequests = ENABLE;
	ADC_Handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&ADC_Handle);

	for(uint8_t q=0;q<ChannelsNumber;q++){
		Channels[q]->init(&ChannelData[Channels[q]->getRank()-1]);
	}

	HAL_ADC_Start_DMA(&ADC_Handle, ChannelData, ChannelsNumber);

}


void ADC_INTERNAL::makeConversion(){
	if(dma != 0)return;


	for(uint8_t q=0;q<ChannelsNumber;q++){
		//Channels[q]->initChannel();

		HAL_ADC_Start(&ADC_Handle);

		HAL_ADC_PollForConversion(&ADC_Handle, 10);

		ChannelData[q] = HAL_ADC_GetValue(&ADC_Handle);
	}

}


void ADC_INTERNAL::registerChannel(ADC_CHANNEL * channel){
	Channels[channel->getRank()-1]=channel;
	ChannelsNumber++;
}

ADC_HandleTypeDef* ADC_INTERNAL::getADCHandler(){
	return &ADC_Handle;
}
DMA_HandleTypeDef* ADC_INTERNAL::getDMA_Handler(){
	return dma->getHandler();
}



