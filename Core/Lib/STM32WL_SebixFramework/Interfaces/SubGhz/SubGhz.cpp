/*
 * SubGhz.cpp
 *
 *  Created on: Dec 18, 2021
 *      Author: skocz
 */

#include <Interfaces/SubGhz/SubGhz.hpp>

SubGhz::SubGhz(BaudRatePrescaller prescaller, uint32_t priority) {
	handler.Init.BaudratePrescaler = (uint32_t) prescaller;
	this->priority = priority;
}

void SubGhz::init() {

	HAL_SUBGHZ_Init(&handler);
	enableIRQ();
}

void SubGhz::enableIRQ() {
    HAL_NVIC_SetPriority(SUBGHZ_Radio_IRQn, priority, 0);
    HAL_NVIC_EnableIRQ(SUBGHZ_Radio_IRQn);
}

void SubGhz::disableIRQ() {
	HAL_NVIC_DisableIRQ(SUBGHZ_Radio_IRQn);
}

SUBGHZ_HandleTypeDef* SubGhz::getHandler() {
	return &handler;
}

HAL_StatusTypeDef SubGhz::execSetCmd(uint8_t command, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_ExecSetCmd(&handler, (SUBGHZ_RadioSetCmd_t) command, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::execGetCmd(uint8_t command, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_ExecGetCmd(&handler, (SUBGHZ_RadioGetCmd_t) command, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::writeBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_WriteBuffer(&handler, Offset, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::readBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_ReadBuffer(&handler, Offset, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::writeRegisters(uint8_t Address, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_WriteRegisters(&handler, (uint16_t) Address, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::readRegisters(uint8_t Address, uint8_t *pBuffer, uint16_t Size) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_ReadRegisters(&handler, (uint16_t) Address, pBuffer, Size);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::writeRegister(uint8_t Address, uint8_t Value) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_WriteRegister(&handler, (uint16_t) Address, Value);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}

HAL_StatusTypeDef SubGhz::readRegister(uint8_t Address, uint8_t *pValue) {
	SF_SUBGHZ_CRITICAL_START();
	HAL_StatusTypeDef a = HAL_SUBGHZ_ReadRegister(&handler, (uint16_t) Address, pValue);
	SF_SUBGHZ_CRITICAL_END();
	return a;
}



