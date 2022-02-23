/*
 * SPI.cpp
 *
 *  Created on: 13.06.2020
 *      Author: SHON
 */

#include "SPI.hpp"



SPI::SPI(PIN *mosi_pin, PIN *miso_pin, PIN *sck_pin, SPI_TypeDef * SPIInstance, uint32_t BaudRatePrescaler){
	this->mosi_pin = mosi_pin;
	this->miso_pin = miso_pin;
	this->sck_pin = sck_pin;
	this->SPIInstance = SPIInstance;
	this->listener=0;

	SPI_IRQn = (IRQn_Type) 0;
	SPI_PreemptPriority = 0;

	this->TxDMA = 0;
	this->RxDMA = 0;


	//EXAMPLE INIT!
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.NSS = SPI_NSS_SOFT;
	SPI_Handle.Init.BaudRatePrescaler = BaudRatePrescaler;
	SPI_Handle.Init.Direction = SPI_DIRECTION_2LINES;
	SPI_Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI_Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_Handle.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI_Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI_Handle.Init.CRCPolynomial = 10;
}

void SPI::init(){

	if(TxDMA)initDMA_Tx_IRQn();
	if(RxDMA)initDMA_Rx_IRQn();
	if(SPI_IRQn)initSPI_IRQn();

	GPIO_InitTypeDef spig;
	spig.Mode = GPIO_MODE_AF_PP;
	spig.Pull = GPIO_PULLDOWN;
	spig.Speed = GPIO_SPEED_FREQ_HIGH;

	if(mosi_pin)mosi_pin->Init(&spig);
	if(miso_pin)miso_pin->Init(&spig);
	sck_pin->Init(&spig);


	//EXAMPLE INIT!
	SPI_Handle.Instance=SPIInstance;
	HAL_SPI_Init(&SPI_Handle);

}

SPI_HandleTypeDef * SPI::getSPIHandler(){
	return &SPI_Handle;
}
DMA_HandleTypeDef*  SPI::getDMA_Tx_Handler(){
	return TxDMA->getHandler();
}
DMA_HandleTypeDef*  SPI::getDMA_Rx_Handler(){
	return RxDMA->getHandler();
}

void SPI::registerListener(SPI_EventListener* listener){
	this->listener=listener;
}


SPI::Status SPI::transmitDMA(uint8_t *pData, uint16_t Size){
	return (Status) HAL_SPI_Transmit_DMA(&SPI_Handle, pData, Size);
}
SPI::Status SPI::transmit(uint8_t *pData, uint16_t Size, uint32_t timeout){
	return (Status) HAL_SPI_Transmit(&SPI_Handle, pData, Size, timeout);
}


SPI::Status SPI::receive(uint8_t *pData, uint16_t Size, uint32_t timeout){
	return (Status) HAL_SPI_Receive(&SPI_Handle, pData, Size, timeout);
}
SPI::Status SPI::receiveDMA(uint8_t *pData, uint16_t Size){
	return (Status) HAL_SPI_Receive_DMA(&SPI_Handle, pData, Size);
}


SPI::Status SPI::stopDMA(){
	return (Status) HAL_SPI_DMAStop(&SPI_Handle);
}

void SPI::configDMA_IRQn(IRQn_Type SPI_IRQn, uint8_t SPI_PreemptPriority){
	this->SPI_IRQn=SPI_IRQn;
	this->SPI_PreemptPriority=SPI_PreemptPriority;
}


void SPI::registerRxDMA(DMA * RxDMA){
	this->RxDMA = RxDMA;
}

void SPI::registerTxDMA(DMA * TxDMA){
	this->TxDMA = TxDMA;
}

DMA* SPI::getTxDMA(){
	return TxDMA;
}

DMA* SPI::getRxDMA(){
	return RxDMA;
}

void SPI::initDMA_Tx_IRQn(){

	//TxDMA->configDirectionAlignment(DMA::Direction::MEM_TO_PERIPH, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);
	TxDMA->initInterrupt();
	TxDMA->init();
	__HAL_LINKDMA(&SPI_Handle, hdmatx, (*TxDMA->getHandler()));


}
void SPI::initDMA_Rx_IRQn(){

	//RxDMA->configDirectionAlignment(DMA::Direction::PERIPH_TO_MEM, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);
	RxDMA->initInterrupt();
	RxDMA->init();
	__HAL_LINKDMA(&SPI_Handle, hdmarx, (*RxDMA->getHandler()));



}

void SPI::initSPI_IRQn(){
	HAL_NVIC_SetPriority(SPI_IRQn, SPI_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(SPI_IRQn);
}



void SPI::IRQn_SPI_Handler(){
	if(listener)listener->onGlobalInterrupt();
}
void SPI::IRQn_DMA_Tx_Cplt(){
	if(listener)listener->onDMATxCmplt();
}
void SPI::IRQn_DMA_Rx_Cplt(){
	if(listener)listener->onDMARxCmplt();
}
void SPI::IRQn_DMA_Tx_HalfCplt(){
	if(listener)listener->onDMATxHalfCmplt();
}
void SPI::IRQn_DMA_Rx_HalfCplt(){
	if(listener)listener->onDMARxHalfCmplt();
}


