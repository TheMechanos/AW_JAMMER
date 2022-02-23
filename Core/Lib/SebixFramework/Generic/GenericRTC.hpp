/*
 * GenericRTC.hpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */

#ifndef GENERIC_GENERICRTC_HPP_
#define GENERIC_GENERICRTC_HPP_

#include <BasicTypes/RTC/RTCTypes.hpp>
#include "stdint.h"

class RTC_GENERIC{
public:
	virtual void init()=0;

	virtual void setTime(TIME * time)=0;
	virtual void setDate(DATE * date)=0;
	virtual void setDateTime(DATETIME * datetime)=0;

	virtual void getTime(TIME * time)=0;
	virtual void getDate(DATE * date)=0;
	virtual void getDateTime(DATETIME * datetime)=0;

};




#endif /* GENERIC_GENERICRTC_HPP_ */
