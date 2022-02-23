/*
 * ADC_DMA.hpp
 *
 *  Created on: 31.08.2020
 *      Author: SHON
 */

#ifndef GPIO_ADC_INTERNAL_HPP_
#define GPIO_ADC_INTERNAL_HPP_

#include <Generic/GenericAnalog.hpp>
#include <Peripheral/GPIO/PIN.hpp>
#include <Peripheral/DMA/DMA.hpp>

#include <stm32wlxx.h>

class ADC_INTERNAL;

class ADC_CHANNEL: public ADC_CHANNEL_GENERIC{
public:
	ADC_CHANNEL()=default;
	ADC_CHANNEL(PIN* pin, uint32_t Channel, ADC_INTERNAL * ADCMaster, uint8_t Rank, uint32_t SamplingTime);

	void init(uint32_t * value);

	void initChannel();

	uint8_t getRank();

	uint16_t getValue();


private:
	uint32_t * value;
	PIN * pin;
	ADC_INTERNAL * ADCMaster;
	ADC_ChannelConfTypeDef ChannelConfig;
};


class ADC_INTERNAL{
public:
	ADC_INTERNAL()=default;
	ADC_INTERNAL(ADC_TypeDef * ADCInstance, uint32_t ADCPrescaler, uint32_t ADCResolution);

	void registerDMA(DMA * dma);

	void init();
	void registerChannel(ADC_CHANNEL * channel);

	void makeConversion();

	ADC_HandleTypeDef* getADCHandler();
	DMA_HandleTypeDef* getDMA_Handler();

private:
public://TODO
	static const uint8_t MAX_CHANNELS=20;

	ADC_HandleTypeDef ADC_Handle;
	ADC_TypeDef * ADC_Instance;
	uint32_t ADC_Prescaler;
	uint32_t ADC_Resolution;

	uint8_t ChannelsNumber;
	ADC_CHANNEL * Channels[MAX_CHANNELS];

	uint32_t ChannelData[MAX_CHANNELS];

	DMA * dma;
};



#endif /* GPIO_ADC_INTERNAL_HPP_ */
