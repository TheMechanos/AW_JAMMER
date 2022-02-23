/*
 * KayEncoder.hpp
 *
 *  Created on: Mar 28, 2021
 *      Author: SHON
 */

#ifndef ENCODER_KEYENCODER_HPP_
#define ENCODER_KEYENCODER_HPP_

#include <Generic/GenericEncoder.hpp>
#include <BasicTypes/Key/ButtonClick.hpp>

class KeyEncoder : public ENCODER_BASE{
public:
	KeyEncoder()=default;

	KeyEncoder(BUTTON_CLICK* a, BUTTON_CLICK* b);

	void configFader(uint32_t faderStartInterval, uint32_t faderEndInterval, uint32_t faderStartTime, uint32_t faderEndTime);

	void iterate(uint32_t TICK);

	virtual void init();

	virtual uint32_t getRawValue();
	virtual void setRawValue(uint32_t val);

	virtual uint16_t getPeroid();

	virtual void setDivider(uint16_t newDivider);

private:
	BUTTON_CLICK* a;
	BUTTON_CLICK* b;

	uint8_t value;
	uint16_t divider;



};




#endif /* ENCODER_KEYENCODER_HPP_ */
