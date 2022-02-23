/*
 * I2C.cpp
 *
 *  Created on: 23 maj 2020
 *      Author: SHON
 */

#include "I2C.hpp"


I2C::I2C(PIN *sda_pin, PIN *scl_pin, I2C_TypeDef * I2CInstance, uint32_t kfrequency){
	this->sda_pin = sda_pin;
	this->scl_pin = scl_pin;
	this->I2CInstance = I2CInstance;
	this->kfrequency = kfrequency;

	this->ER_PreemptPriority = 0;
	this->EV_PreemptPriority = 0;

	this->TxDMA = 0;
	this->RxDMA = 0;

	this->ER_IRQn = (IRQn_Type) 0;
	this->EV_IRQn = (IRQn_Type) 0;
}


void I2C::initPins(){

	GPIO_InitTypeDef i2cg;
	i2cg.Pull = GPIO_PULLUP;
	i2cg.Mode = GPIO_MODE_AF_OD;
	i2cg.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	sda_pin->Init(&i2cg);
	scl_pin->Init(&i2cg);

}

void I2C::initInterface(){


	if(TxDMA)initDMA_Tx_IRQn();
	if(RxDMA)initDMA_Rx_IRQn();
	if(EV_IRQn)initI2C_EV_IRQn();
	if(ER_IRQn)initI2C_ER_IRQn();

	I2CHandler.Instance = I2CInstance;
	//I2CHandler.Init.ClockSpeed = kfrequency*1000;
	//I2CHandler.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2CHandler.Init.OwnAddress1 = 0x0;
	I2CHandler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2CHandler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CHandler.Init.OwnAddress2 = 0x0;
	I2CHandler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2CHandler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	HAL_I2C_Init(&I2CHandler);

	//HAL_I2CEx_ConfigAnalogFilter(&I2CHandler, I2C_ANALOGFILTER_DISABLE);
	//HAL_I2CEx_ConfigDigitalFilter(&I2CHandler, 0);
}

I2C_HandleTypeDef * I2C::getI2CHandler(){
	return &I2CHandler;
}


void I2C::registerTxDMA(DMA * TxDMA){
	this->TxDMA = TxDMA;
}
void I2C::registerRxDMA(DMA * RxDMA){
	this->RxDMA = RxDMA;
}

void I2C::configEV_IRQn(IRQn_Type I2C_EV_IRQn, uint8_t PreemptPriority){
	this->EV_IRQn = I2C_EV_IRQn;
	this->EV_PreemptPriority = PreemptPriority;
}

void I2C::configER_IRQn(IRQn_Type I2C_ER_IRQn, uint8_t PreemptPriority){
	this->ER_IRQn = I2C_ER_IRQn;
	this->ER_PreemptPriority = PreemptPriority;
}

void I2C::initDMA_Tx_IRQn(){

	TxDMA->configDirectionAlignment(DMA::Direction::MEM_TO_PERIPH, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);

	TxDMA->init();
	__HAL_LINKDMA(&I2CHandler, hdmatx, (*TxDMA->getHandler()));
	TxDMA->initInterrupt();

}

void I2C::initDMA_Rx_IRQn(){

	RxDMA->configDirectionAlignment(DMA::Direction::PERIPH_TO_MEM, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);

	RxDMA->init();
	__HAL_LINKDMA(&I2CHandler, hdmarx, (*RxDMA->getHandler()));
	RxDMA->initInterrupt();

}

void I2C::initI2C_EV_IRQn(){
	HAL_NVIC_SetPriority(EV_IRQn, EV_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(EV_IRQn);
}

void I2C::initI2C_ER_IRQn(){
	HAL_NVIC_SetPriority(ER_IRQn, ER_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(ER_IRQn);
}

HAL_StatusTypeDef I2C::memWrite(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout){
	return HAL_I2C_Mem_Write(&I2CHandler, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
}

HAL_StatusTypeDef I2C::memRead(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout){
	return HAL_I2C_Mem_Read(&I2CHandler, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
}

HAL_StatusTypeDef I2C::masterTransmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout){
	return HAL_I2C_Master_Transmit(&I2CHandler, DevAddress, pData, Size, Timeout);
}


DMA_HandleTypeDef*  I2C::getDMA_Tx_Handler(){
	return TxDMA->getHandler();
}
DMA_HandleTypeDef*  I2C::getDMA_Rx_Handler(){
	return RxDMA->getHandler();
}
