/*
 * encoder.cpp
 *
 *  Created on: 02.01.2020
 *      Author: SHON
 */

#ifndef HARDWARE_ENCODER_ENCODER_CPP_
#define HARDWARE_ENCODER_ENCODER_CPP_

#include <Generic/GenericEncoder.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <Peripheral/GPIO/PIN.hpp>
#include <stm32wlxx.h>



class TIMER_ENCODER : public ENCODER_BASE{
public:
	enum ENCODER_DIR_LOGIC{ENC_DIR_NORMAL, ENC_DIR_REVERSE};
	TIMER_ENCODER()=default;
	TIMER_ENCODER(PIN * pin1, PIN * pin2, TIM_TypeDef * TIM, ENCODER_DIR_LOGIC enc_dir);

	void init();

	uint32_t  getRawValue();
	void setRawValue(uint32_t val);
	void setDivider(uint16_t divider);
	uint16_t getPeroid();

	static const uint16_t ENDODER_PEROID = 30000;

private:
	PIN *pin1;
	PIN *pin2;
	TIM_TypeDef * TIM;
	TIM_HandleTypeDef TimEncoderStruct={0};
	TIM_Encoder_InitTypeDef EncoderStruct={0};

	ENCODER_DIR_LOGIC enc_dir_logic;

	uint16_t divider;





};




#endif /* HARDWARE_ENCODER_ENCODER_CPP_ */
