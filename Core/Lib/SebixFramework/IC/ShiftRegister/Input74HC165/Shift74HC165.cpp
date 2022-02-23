/*
 * HalArray.cpp
 *
 *  Created on: 29 mar 2021
 *      Author: SHON
 */
#include <IC/ShiftRegister/Input74HC165/Shift74HC165.hpp>

Shift74HC165::Shift74HC165(SPI *spi, OUTPUT_ADVENCED *lt, uint32_t refInterval){
	this->spi = spi;
	this->lt = lt;
	this->refInterval = refInterval;

	this->stage = Stage::Off;

}

void Shift74HC165::init(uint8_t *data, uint8_t dataSize){
	this->data = data;
	this->dataSize = dataSize;

	spi->registerListener(this);
	spi->getRxDMA()->configDirectionAlignment(DMA::Direction::PERIPH_TO_MEM, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);
	spi->getSPIHandler()->Init.CLKPhase = SPI_PHASE_1EDGE;
	spi->getSPIHandler()->Init.CLKPolarity = SPI_POLARITY_LOW;
	spi->getSPIHandler()->Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
	spi->getSPIHandler()->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	spi->init();
}

void Shift74HC165::iterate(uint32_t tick){
	if(tick - lastRefresh > refInterval && stage == Stage::Wait){
		stage = Stage::Latch;
		lt->OFF();
		lt->ON();
	}
	if(stage == Stage::Latch && lt->get() == true){
		stage = Stage::Wait;
		lastRefresh = tick;
		volatile SPI::Status q = spi->receiveDMA(data, dataSize);
		q = q;
	}
}

void Shift74HC165::onDMARxCmplt(){
	stage = Stage::Wait;
}

void Shift74HC165::start(){
	stage = Stage::Wait;
}
void Shift74HC165::stop(){
	stage = Stage::Off;
}

uint8_t Shift74HC165::getByte(uint8_t byte){
	if(byte < dataSize){
		return data[byte];
	}
	return 0;
}

bool Shift74HC165::getBit(uint16_t bit){
	if(bit < (dataSize * 8)){
		uint8_t byte = bit / 8;
		uint8_t bite = bit % 8;
		if(data[byte] & (1 << bite)){
			return true;
		}
	}
	return false;

}
