/*
 * SubGhz.h
 *
 *  Created on: Dec 18, 2021
 *      Author: skocz
 */

#ifndef LIB_STM32WL_SEBIXFRAMEWORK_INTERFACES_SUBGHZ_SUBGHZ_HPP_
#define LIB_STM32WL_SEBIXFRAMEWORK_INTERFACES_SUBGHZ_SUBGHZ_HPP_

#include <stm32wlxx.h>


#define SF_SUBGHZ_CRITICAL_START() uint32_t primask_bit= __get_PRIMASK();__disable_irq()
#define SF_SUBGHZ_CRITICAL_END() __set_PRIMASK(primask_bit)

class SubGhzInterruptListener{

};

class SubGhz {
public:
	enum class BaudRatePrescaller {
		BR2 = SUBGHZSPI_BAUDRATEPRESCALER_2,
		BR4 = SUBGHZSPI_BAUDRATEPRESCALER_4,
		BR8 = SUBGHZSPI_BAUDRATEPRESCALER_8,
		BR16 = SUBGHZSPI_BAUDRATEPRESCALER_16,
		BR32 = SUBGHZSPI_BAUDRATEPRESCALER_32,
		BR64 = SUBGHZSPI_BAUDRATEPRESCALER_64,
		BR128 = SUBGHZSPI_BAUDRATEPRESCALER_128,
		BR256 = SUBGHZSPI_BAUDRATEPRESCALER_256,
	};

	SubGhz()=default;
	SubGhz(BaudRatePrescaller prescaller, uint32_t priority);

	void init();

	void enableIRQ();
	void disableIRQ();

	SUBGHZ_HandleTypeDef* getHandler();

	virtual HAL_StatusTypeDef execSetCmd(uint8_t command, uint8_t *pBuffer, uint16_t Size);
	virtual HAL_StatusTypeDef execGetCmd(uint8_t command, uint8_t *pBuffer, uint16_t Size);

	virtual HAL_StatusTypeDef writeBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size);
	virtual HAL_StatusTypeDef readBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size);

	virtual HAL_StatusTypeDef writeRegisters(uint8_t Address, uint8_t *pBuffer, uint16_t Size);
	virtual HAL_StatusTypeDef readRegisters(uint8_t Address, uint8_t *pBuffer, uint16_t Size);
	virtual HAL_StatusTypeDef writeRegister(uint8_t Address, uint8_t Value);
	virtual HAL_StatusTypeDef readRegister(uint8_t Address, uint8_t *pValue);

private:
	SUBGHZ_HandleTypeDef handler;
	uint32_t priority;

	SubGhzInterruptListener* listner;
};

#endif /* LIB_STM32WL_SEBIXFRAMEWORK_INTERFACES_SUBGHZ_SUBGHZ_HPP_ */
