/*
 * RealTimeClock.hpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */

#ifndef BASICTYPES_RTC_RTCTYPES_HPP_
#define BASICTYPES_RTC_RTCTYPES_HPP_

#include "stdint.h"
#include <stdio.h>
#include <string.h>

class TIME{
public:
	enum class COMPONENTS{
		ALL, HOUR_MINUTE
	};

	TIME()=default;
	TIME(uint8_t hour, uint8_t min, uint8_t sec);

	void setTime(uint8_t hour, uint8_t min, uint8_t sec);

	void setSecond(uint8_t sec);
	void setMinute(uint8_t min);
	void setHour(uint8_t hour);

	uint8_t getSecond();
	uint8_t getMinute();
	uint8_t getHour();

	void getString(char * string);
	void getString(char * string, COMPONENTS comp);

protected:
	uint8_t sec;
	uint8_t min;
	uint8_t hour;

};

class DATE{
public:
	enum class WEEKDAY {
		SUNDAY = 0, MONDAY, TUESDAY, WENESDAY, THURSDAY, FRIDAY, SATURDAY
	};

	constexpr static const char WEEKDAY_STRING[7][13] = { "NIEDZIELA", "PONIEDZIA£EK", "WTOREK", "ŒRODA", "CZWARTEK", "PI¥TEK", "SOBOTA" };
	constexpr static const char WEEKDAY_STRING_SHORT[7][3] = { "ND", "PN", "WT", "ŒR", "CZ", "PT", "SB" };
	constexpr static const uint8_t DAYS_IN_MONTH[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

	DATE()=default;
	DATE(uint8_t day, uint8_t month, uint16_t year);

	void setDate(uint8_t day, uint8_t month, uint16_t year);

	void setDay(uint8_t day);
	void setMonth(uint8_t month);
	void setYear(uint16_t year);

	bool isLeapYear();
	bool isLeapYear(uint16_t year);

	uint8_t getDay();
	uint8_t getMonth();
	uint16_t getYear();

	void getString(char * string);

	WEEKDAY getWeekday();
	char* getWeekdayString();
	char* getWeekdayString(WEEKDAY weekday);

	static WEEKDAY getWeekday(uint8_t day, uint8_t month, uint16_t year);

protected:
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

class DATETIME : public DATE, public TIME{
public:
	DATETIME()=default;
	DATETIME(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint16_t year);

	void getString(char * string);

};


#endif /* BASICTYPES_RTC_RTCTYPES_HPP_ */
