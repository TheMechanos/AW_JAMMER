/*
 * DMA.cpp
 *
 *  Created on: 11.09.2020
 *      Author: SHON
 */

#include "DMA.hpp"

DMA::DMA(DMA_Channel_TypeDef * channel, uint32_t Priority, IRQn_Type IRQn, uint8_t PreemptPriority){
	handler.Instance = channel;
	handler.Init.Priority = Priority;

	handler.Init.Direction=123;

	this->IRQn = IRQn;
	this->preemptPriority = PreemptPriority;
}

void DMA::configDirectionAlignment(Direction direction, Mode mode, bool periphInc, bool memInc, PeriphAlign periphDataAlignment, MemAlign memDataAlignment){
	handler.Init.Mode = (uint32_t) mode;
	handler.Init.Direction = (uint32_t) direction;
	handler.Init.PeriphInc = (periphInc) ? DMA_PINC_ENABLE : DMA_PINC_DISABLE;
	handler.Init.MemInc = (memInc) ? DMA_MINC_ENABLE : DMA_MINC_DISABLE;
	handler.Init.PeriphDataAlignment = (uint32_t) periphDataAlignment;
	handler.Init.MemDataAlignment = (uint32_t) memDataAlignment;
}

void DMA::init(){
	if(handler.Instance != 0){
		HAL_DMA_Init(&handler);
	}
}

void DMA::initInterrupt(){
	HAL_NVIC_SetPriority(IRQn, preemptPriority, 0);
	HAL_NVIC_EnableIRQ(IRQn);
}

void DMA::startMemTransfer(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength){
	if(handler.Init.Direction==DMA_MEMORY_TO_MEMORY){
		HAL_DMA_Start(&handler, SrcAddress, DstAddress, DataLength);
	}

}

DMA_HandleTypeDef* DMA::getHandler(){
	return &handler;
}


