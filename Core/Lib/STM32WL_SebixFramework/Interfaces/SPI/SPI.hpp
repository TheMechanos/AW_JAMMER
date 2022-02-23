/*
 * SPI.hpp
 *
 *  Created on: 13.06.2020
 *      Author: SHON
 */

#ifndef PERIPHERAL_SPI_SPI_HPP_
#define PERIPHERAL_SPI_SPI_HPP_

#include <Peripheral/GPIO/PIN.hpp>
#include <Peripheral/DMA/DMA.hpp>

#include <stm32wlxx.h>

class SPI_EventListener{
public:
	virtual ~SPI_EventListener(){}
	virtual void onGlobalInterrupt(){};
	virtual void onDMATxHalfCmplt(){};
	virtual void onDMATxCmplt(){};
	virtual void onDMARxHalfCmplt(){};
	virtual void onDMARxCmplt(){};
};

class SPI{
public:
	enum class Status {HAL_OK = 0x00U, HAL_ERROR = 0x01U, HAL_BUSY = 0x02U, HAL_TIMEOUT = 0x03U};

	SPI() = default;
	SPI(PIN *mosi_pin, PIN *miso_pin, PIN *sck_pin, SPI_TypeDef * SPIInstance, uint32_t BaudRatePrescaler);

	void init();

	SPI_HandleTypeDef * getSPIHandler();
	DMA_HandleTypeDef*  getDMA_Tx_Handler();
	DMA_HandleTypeDef*  getDMA_Rx_Handler();

	void IRQn_SPI_Handler();
	void IRQn_DMA_Tx_Cplt();
	void IRQn_DMA_Rx_Cplt();
	void IRQn_DMA_Tx_HalfCplt();
	void IRQn_DMA_Rx_HalfCplt();

	void configDMA_IRQn(IRQn_Type SPI_IRQn, uint8_t SPI_PreemptPriority);

	void registerTxDMA(DMA * TxDMA);
	void registerRxDMA(DMA * RxDMA);
	void registerListener(SPI_EventListener* listener);

	DMA* getTxDMA();
	DMA* getRxDMA();

	Status transmitDMA(uint8_t *pData, uint16_t Size);
	Status transmit(uint8_t *pData, uint16_t Size, uint32_t timeout);

	Status receiveDMA(uint8_t *pData, uint16_t Size);
	Status receive(uint8_t *pData, uint16_t Size, uint32_t timeout);

	Status stopDMA();

private:
	PIN *mosi_pin;
	PIN *miso_pin;
	PIN *sck_pin;
	SPI_TypeDef * SPIInstance;
	SPI_HandleTypeDef SPI_Handle = {0};
	SPI_EventListener* listener;

	IRQn_Type SPI_IRQn;
	uint8_t SPI_PreemptPriority;

	DMA * TxDMA;
	DMA * RxDMA;

	void initDMA_Tx_IRQn();
	void initDMA_Rx_IRQn();
	void initSPI_IRQn();
};




#endif /* PERIPHERAL_SPI_SPI_HPP_ */
