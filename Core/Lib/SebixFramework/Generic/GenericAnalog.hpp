/*
 * Encoder.hpp
 *
 *  Created on: 11.08.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_GENERICANALOG_HPP_
#define BASICTYPES_GENERICANALOG_HPP_

#include "stdint.h"


class ADC_CHANNEL_GENERIC{
public:
	virtual uint16_t getValue()=0;
	//virtual void init()=0;

	virtual ~ADC_CHANNEL_GENERIC(){};
};

class DAC_CHANNEL_GENERIC{
public:
	virtual void setValue(uint16_t value)=0;
	virtual uint16_t getMaxValue()=0;
	virtual void init()=0;

	virtual ~DAC_CHANNEL_GENERIC(){};
};


#endif /* BASICTYPES_GENERICTYPES_HPP_ */
