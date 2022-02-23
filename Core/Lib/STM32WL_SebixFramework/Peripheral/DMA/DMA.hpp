/*
 * DMA.hpp
 *
 *  Created on: 11.09.2020
 *      Author: SHON
 */

#ifndef PERIPHERAL_DMA_DMA_HPP_
#define PERIPHERAL_DMA_DMA_HPP_

#include <stm32wlxx.h>

class DMA{
public:
	enum class Direction{PERIPH_TO_MEM=DMA_PERIPH_TO_MEMORY,MEM_TO_PERIPH=DMA_MEMORY_TO_PERIPH,MEM_TO_MEM = DMA_MEMORY_TO_MEMORY};
	enum class Mode{NORMAL=DMA_NORMAL, CIRCULAR=DMA_CIRCULAR};
	enum class PeriphAlign{BYTE = DMA_PDATAALIGN_BYTE, HALF_WORD = DMA_PDATAALIGN_HALFWORD, WORD = DMA_PDATAALIGN_WORD};
	enum class MemAlign{BYTE = DMA_MDATAALIGN_BYTE, HALF_WORD = DMA_MDATAALIGN_HALFWORD, WORD = DMA_MDATAALIGN_WORD};

	DMA()=default;
	DMA(DMA_Channel_TypeDef * channel, uint32_t priority, IRQn_Type IRQn, uint8_t preemptPriority);

	void configDirectionAlignment(Direction direction, Mode mode, bool periphInc, bool memInc, PeriphAlign periphDataAlignment, MemAlign memDataAlignment);

	void init();
	void initInterrupt();

	void startMemTransfer(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);

	DMA_HandleTypeDef* getHandler();

private:
	DMA_HandleTypeDef handler;
	IRQn_Type IRQn;
	uint8_t preemptPriority;

};



#endif /* PERIPHERAL_DMA_DMA_HPP_ */
