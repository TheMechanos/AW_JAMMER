/*
 * rtc.hpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */

#ifndef RTC_RTC_HPP_
#define RTC_RTC_HPP_

#include <Generic/GenericRTC.hpp>
#include <stm32wlxx.h>

class RTCTYPE : public RTC_GENERIC{
public:
	RTCTYPE()=default;

	void init();

	void setTime(TIME * time);
	void setDate(DATE * date);
	void setDateTime(DATETIME * datetime);

	void getTime(TIME * time);
	void getDate(DATE * date);
	void getDateTime(DATETIME * datetime);

private:
	RTC_HandleTypeDef rtc;
	RTC_TimeTypeDef RtcTime;
	RTC_DateTypeDef RtcDate;
};




#endif /* RTC_RTC_HPP_ */
