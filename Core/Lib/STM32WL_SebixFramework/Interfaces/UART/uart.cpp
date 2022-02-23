/*
 * uart.cpp
 *
 *  Created on: 30.12.2019
 *      Author: SHON
 */

#include "uart.hpp"


UART::UART(PIN * TXPin, PIN * RXPin, USART_TypeDef * uart_instance, uint32_t baudrate){
	this->TXPin = TXPin;
	this->RXPin = RXPin;

	this->uart_instance=uart_instance;
	this->baudrate=baudrate;

	UART_IDLE_is=false;

	DMA_Tx_Stream=0;
	DMA_Tx_Priority=0;
	DMA_Tx_IRQn=(IRQn_Type)0;
	DMA_Tx_PreemptPriority=0;

	DMA_Rx_Stream=0;
	DMA_Rx_Priority=0;
	DMA_Rx_IRQn=(IRQn_Type)0;
	DMA_Rx_PreemptPriority=0;

	UART_IRQn=(IRQn_Type)0;
	UART_PreemptPriority=0;
}

bool UART::Init(){
	GPIO_InitTypeDef pinInit;

	pinInit.Mode = GPIO_MODE_AF_PP;
	pinInit.Speed = GPIO_SPEED_FAST;
	pinInit.Pull = GPIO_PULLUP;

	TXPin->Init(&pinInit);
	RXPin->Init(&pinInit);

	if(DMA_Tx_Stream)initDMA_Tx_IRQn();
	if(DMA_Rx_Stream)initDMA_Rx_IRQn();
	if(UART_IRQn!=0)initUART_IRQn();

	UART_Handle.Instance = uart_instance;
	UART_Handle.Init.BaudRate = baudrate;
	UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
	UART_Handle.Init.StopBits = UART_STOPBITS_1;
	UART_Handle.Init.Parity = UART_PARITY_NONE;
	UART_Handle.Init.Mode = UART_MODE_TX_RX;
	UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_Handle.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&UART_Handle);

	if(UART_IDLE_is)initUART_IDLE_IRQn();

	return false;
}

bool UART::Transmit(const char * s){
	int r = HAL_UART_Transmit(&UART_Handle, (uint8_t *)s, strlen(s), HAL_MAX_DELAY);
	return  r == HAL_OK;
}

DMA_HandleTypeDef*  UART::getDMA_Tx_Handler(){
	return &DMA_Tx_Handle;
}
DMA_HandleTypeDef*  UART::getDMA_Rx_Handler(){
	return &DMA_Rx_Handle;
}
UART_HandleTypeDef* UART::getUART_Handler(){
	return &UART_Handle;
}

void UART::configUART_IRQn(IRQn_Type UART_IRQn, uint8_t UART_PreemptPriority){
	this->UART_IRQn=UART_IRQn;
	this->UART_PreemptPriority=UART_PreemptPriority;
}

void UART::configUART_IDLE_IRQn(){
	UART_IDLE_is=true;
}

void UART::configDMA_Tx_IRQn(DMA_Stream_TypeDef * DMA_Tx_Stream, uint32_t DMA_Tx_Priority, IRQn_Type DMA_Tx_IRQn, uint8_t DMA_Tx_PreemptPriority){
	this->DMA_Tx_Stream=DMA_Tx_Stream;
	this->DMA_Tx_Priority=DMA_Tx_Priority;
	this->DMA_Tx_IRQn=DMA_Tx_IRQn;
	this->DMA_Tx_PreemptPriority=DMA_Tx_PreemptPriority;
}
void UART::configDMA_Rx_IRQn(DMA_Stream_TypeDef * DMA_Rx_Stream, uint32_t DMA_Rx_Priority, IRQn_Type DMA_Rx_IRQn, uint8_t DMA_Rx_PreemptPriority){
	this->DMA_Rx_Stream=DMA_Rx_Stream;
	this->DMA_Rx_Priority=DMA_Rx_Priority;
	this->DMA_Rx_IRQn=DMA_Rx_IRQn;
	this->DMA_Rx_PreemptPriority=DMA_Rx_PreemptPriority;
}

void UART::initDMA_Tx_IRQn(){
	DMA_Tx_Handle.Instance = DMA_Tx_Stream;
	DMA_Tx_Handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
	DMA_Tx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
	DMA_Tx_Handle.Init.MemInc = DMA_MINC_ENABLE;
	DMA_Tx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DMA_Tx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	DMA_Tx_Handle.Init.Mode = DMA_NORMAL;
	DMA_Tx_Handle.Init.Priority = DMA_Tx_Priority;
	HAL_DMA_Init(&DMA_Tx_Handle);
	__HAL_LINKDMA(&UART_Handle, hdmatx, DMA_Tx_Handle);

	HAL_NVIC_SetPriority(DMA_Tx_IRQn, DMA_Tx_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(DMA_Tx_IRQn);
}

void UART::initDMA_Rx_IRQn(){
	DMA_Rx_Handle.Instance = DMA_Rx_Stream;
	DMA_Rx_Handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
	DMA_Rx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
	DMA_Rx_Handle.Init.MemInc = DMA_MINC_ENABLE;
	DMA_Rx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DMA_Rx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	DMA_Rx_Handle.Init.Mode = DMA_NORMAL;
	DMA_Rx_Handle.Init.Priority = DMA_Rx_Priority;
	HAL_DMA_Init(&DMA_Rx_Handle);
	__HAL_LINKDMA(&UART_Handle, hdmarx, DMA_Rx_Handle);

	HAL_NVIC_SetPriority(DMA_Rx_IRQn, DMA_Rx_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(DMA_Rx_IRQn);
}

void UART::initUART_IRQn(){
	HAL_NVIC_SetPriority(UART_IRQn, UART_PreemptPriority, 0);
	HAL_NVIC_EnableIRQ(UART_IRQn);
}

void UART::initUART_IDLE_IRQn(){
	__HAL_UART_ENABLE_IT(&UART_Handle, UART_IT_IDLE);
}

void UART::IRQn_UART_Handler(){
	if(__HAL_UART_GET_FLAG(getUART_Handler(), UART_FLAG_IDLE)){   			 //Judging whether it is idle interruption
		__HAL_UART_CLEAR_IDLEFLAG(getUART_Handler());                  		//Clear idle interrupt sign (otherwise it will continue to enter interrupt)
		IRQn_DMA_Cplt();
	}
}

void UART::IRQn_DMA_Cplt(){
	HAL_UART_DMAStop(getUART_Handler());
	//Calculate the length of the received data
	uint8_t data_length = Size_Buffer_Rx - __HAL_DMA_GET_COUNTER(getDMA_Rx_Handler());

	//Test function: Print out the received data
	//printf("Receive Data(length = %d): ", data_length);
	HAL_UART_Transmit(getUART_Handler(), (uint8_t*) Buffer_Rx, data_length, HAL_MAX_DELAY);
	//printf("\r\n");

	//Zero Receiving Buffer
	memset(Buffer_Rx, 0, data_length);
	data_length = 0;

	Start_DMA_Receiving();
}

void UART::Start_DMA_Receiving(){
	HAL_UART_Receive_DMA(getUART_Handler(), (uint8_t*) Buffer_Rx, Size_Buffer_Rx);
}






