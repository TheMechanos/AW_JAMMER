/*
 * uart.hpp
 *
 *  Created on: 30.12.2019
 *      Author: SHON
 */

#ifndef HARDWARE_UART_UART_HPP_
#define HARDWARE_UART_UART_HPP_

#include <Peripheral/GPIO/PIN.hpp>
#include <stm32wlxx.h>
#include <string.h>
#include "stdio.h"



class UART{
public:
	UART()=default;
	UART(PIN * TXPin, PIN * RXPin, USART_TypeDef * uart_instance, uint32_t baudrate);

	bool Init();

	bool Transmit(const char * s);

	void configDMA_Tx_IRQn(DMA_Stream_TypeDef * DMA_Tx_Stream, uint32_t DMA_Tx_Priority, IRQn_Type DMA_Tx_IRQn, uint8_t DMA_Tx_PreemptPriority);
	void configDMA_Rx_IRQn(DMA_Stream_TypeDef * DMA_Rx_Stream, uint32_t DMA_Rx_Priority, IRQn_Type DMA_Rx_IRQn, uint8_t DMA_Rx_PreemptPriority);
	void configUART_IRQn(IRQn_Type UART_IRQn, uint8_t UART_PreemptPriority);
	void configUART_IDLE_IRQn();

	void IRQn_UART_Handler();
	void IRQn_DMA_Cplt();

	void Start_DMA_Receiving();

	DMA_HandleTypeDef*  getDMA_Tx_Handler();
	DMA_HandleTypeDef*  getDMA_Rx_Handler();
	UART_HandleTypeDef* getUART_Handler();

private:
	PIN * TXPin;
	PIN * RXPin;

	USART_TypeDef   * uart_instance;
	uint32_t baudrate;

	DMA_HandleTypeDef DMA_Tx_Handle;
	DMA_Stream_TypeDef * DMA_Tx_Stream;
	uint32_t DMA_Tx_Priority;
	IRQn_Type DMA_Tx_IRQn;
	uint8_t DMA_Tx_PreemptPriority;
	void initDMA_Tx_IRQn();

	DMA_HandleTypeDef DMA_Rx_Handle;
	DMA_Stream_TypeDef * DMA_Rx_Stream;
	uint32_t DMA_Rx_Priority;
	IRQn_Type DMA_Rx_IRQn;
	uint8_t DMA_Rx_PreemptPriority;
	void initDMA_Rx_IRQn();

	IRQn_Type UART_IRQn;
	uint8_t UART_PreemptPriority;
	void initUART_IRQn();

	bool UART_IDLE_is;
	void initUART_IDLE_IRQn();

	UART_HandleTypeDef UART_Handle;

	static const uint16_t Size_Buffer_Tx=128;
	static const uint16_t Size_Buffer_Rx=128;

	uint8_t Buffer_Tx[Size_Buffer_Tx];
	uint8_t Buffer_Rx[Size_Buffer_Rx];

};



#endif /* HARDWARE_UART_UART_HPP_ */
