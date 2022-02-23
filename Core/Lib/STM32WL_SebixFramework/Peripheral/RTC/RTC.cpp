/*
 * RTC.cpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */


#include "RTC.hpp"

void RTCTYPE::init(){

	HAL_PWR_EnableBkUpAccess();
	//__HAL_RCC_BKPSRAM_CLK_ENABLE(); //TODO------------

	rtc.Instance = RTC;
	rtc.Init.HourFormat = RTC_HOURFORMAT_24;
	rtc.Init.AsynchPrediv = 127;
	rtc.Init.SynchPrediv = 255;
	rtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	rtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	rtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

	if((RCC->BDCR & RCC_BDCR_RTCEN) == 0)
		HAL_RTC_Init(&rtc);

}

void RTCTYPE::setTime(TIME * time){
	RtcTime.Seconds=time->getSecond();
	RtcTime.Minutes=time->getMinute();
	RtcTime.Hours=time->getHour();
	HAL_RTC_SetTime(&rtc, &RtcTime, RTC_FORMAT_BIN);
}
void RTCTYPE::setDate(DATE * date){
	RtcDate.Date=date->getDay();
	RtcDate.Month=date->getMonth();
	RtcDate.Year=date->getYear()-2000;
	HAL_RTC_SetDate(&rtc, &RtcDate, RTC_FORMAT_BIN);
}
void RTCTYPE::setDateTime(DATETIME * datetime){
	RtcTime.Seconds=datetime->getSecond();
	RtcTime.Minutes=datetime->getMinute();
	RtcTime.Hours=datetime->getHour();
	HAL_RTC_SetTime(&rtc, &RtcTime, RTC_FORMAT_BIN);

	RtcDate.Date=datetime->getDay();
	RtcDate.Month=datetime->getMonth();
	RtcDate.Year=datetime->getYear()-2000;
	HAL_RTC_SetDate(&rtc, &RtcDate, RTC_FORMAT_BIN);
}

void RTCTYPE::getTime(TIME * time){
	HAL_RTC_GetTime(&rtc, &RtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&rtc, &RtcDate, RTC_FORMAT_BIN);
	time->setTime(RtcTime.Hours, RtcTime.Minutes, RtcTime.Seconds);
}
void RTCTYPE::getDate(DATE * date){
	HAL_RTC_GetTime(&rtc, &RtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&rtc, &RtcDate, RTC_FORMAT_BIN);
	date->setDate(RtcDate.Date, RtcDate.Month, RtcDate.Year+2000);
}
void RTCTYPE::getDateTime(DATETIME * datetime){
	HAL_RTC_GetTime(&rtc, &RtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&rtc, &RtcDate, RTC_FORMAT_BIN);
	datetime->setDate(RtcDate.Date, RtcDate.Month, RtcDate.Year+2000);
	datetime->setTime(RtcTime.Hours, RtcTime.Minutes, RtcTime.Seconds);
}

