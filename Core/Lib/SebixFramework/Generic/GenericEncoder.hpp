/*
 * GenericEncoder.hpp
 *
 *  Created on: 23.10.2020
 *      Author: SHON
 */

#ifndef GENERIC_GENERICENCODER_HPP_
#define GENERIC_GENERICENCODER_HPP_

#include "stdint.h"

class ENCODER_BASE{
public:
	virtual void init()=0;

	virtual uint32_t  getRawValue()=0;
	virtual void setRawValue(uint32_t val)=0;

	virtual uint16_t getPeroid()=0;

	virtual void setDivider(uint16_t divider)=0;

	virtual ~ENCODER_BASE(){};
};



#endif /* GENERIC_GENERICENCODER_HPP_ */
