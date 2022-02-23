/*
 * I2C.hpp
 *
 *  Created on: 23 maj 2020
 *      Author: SHON
 */

#ifndef PERIPHERAL_I2C_I2C_HPP_
#define PERIPHERAL_I2C_I2C_HPP_

#include <Peripheral/GPIO/PIN.hpp>
#include <Peripheral/DMA/DMA.hpp>
#include <stm32wlxx.h>

class I2C{
public:
	I2C()=default;
	I2C(PIN *sda_pin, PIN *scl_pin, I2C_TypeDef * I2CInstance, uint32_t kfrequency);

	void initPins();
	void initInterface();

	I2C_HandleTypeDef * getI2CHandler();
	DMA_HandleTypeDef*  getDMA_Tx_Handler();
	DMA_HandleTypeDef*  getDMA_Rx_Handler();

	HAL_StatusTypeDef memWrite(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	HAL_StatusTypeDef memRead(uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

	HAL_StatusTypeDef masterTransmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

	void registerTxDMA(DMA * TxDMA);
	void registerRxDMA(DMA * RxDMA);

	void configEV_IRQn(IRQn_Type I2C_EV_IRQn, uint8_t PreemptPriority);
	void configER_IRQn(IRQn_Type I2C_ER_IRQn, uint8_t PreemptPriority);

private:
	PIN* sda_pin;
	PIN* scl_pin;
	uint32_t kfrequency;
	I2C_TypeDef * I2CInstance;
	I2C_HandleTypeDef I2CHandler;

	IRQn_Type EV_IRQn;
	uint8_t EV_PreemptPriority;
	IRQn_Type ER_IRQn;
	uint8_t ER_PreemptPriority;

	DMA * TxDMA;
	DMA * RxDMA;

	void initDMA_Tx_IRQn();
	void initDMA_Rx_IRQn();
	void initI2C_EV_IRQn();
	void initI2C_ER_IRQn();
};



#endif /* PERIPHERAL_I2C_I2C_HPP_ */
