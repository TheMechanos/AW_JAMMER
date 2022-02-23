/*
 * RealTimeClock.cpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */

#include <BasicTypes/RTC/RTCTypes.hpp>

TIME::TIME(uint8_t hour, uint8_t min, uint8_t sec){
	this->sec = sec;
	this->min = min;
	this->hour = hour;
}

void TIME::setTime(uint8_t hour, uint8_t min, uint8_t sec){
	this->sec = sec;
	this->min = min;
	this->hour = hour;
}

void TIME::setSecond(uint8_t sec){
	this->sec = sec;
}
void TIME::setMinute(uint8_t min){
	this->min = min;
}
void TIME::setHour(uint8_t hour){
	this->hour = hour;
}

uint8_t TIME::getSecond(){
	return sec;
}
uint8_t TIME::getMinute(){
	return min;
}
uint8_t TIME::getHour(){
	return hour;
}

void TIME::getString(char * string){
	getString(string, COMPONENTS::ALL);
}
void TIME::getString(char * string, COMPONENTS comp){

	string[0]=0;

	char buf[4];

	if(comp==COMPONENTS::ALL || comp==COMPONENTS::HOUR_MINUTE){
		if(hour<10)sprintf(buf, "0%d:", hour);
		else sprintf(buf, "%d:", hour);
		strcpy(string, buf);
	}


	if(comp==COMPONENTS::ALL || comp==COMPONENTS::HOUR_MINUTE){
		if(min<10)sprintf(buf, "0%d", min);
		else sprintf(buf, "%d", min);
		strcat(string, buf);
	}

	if(comp==COMPONENTS::ALL){
		if(sec<10)sprintf(buf, ":0%d", sec);
		else sprintf(buf, ":%d", sec);
		strcat(string, buf);
	}


}

constexpr const char DATE::WEEKDAY_STRING[7][13];
constexpr const char DATE::WEEKDAY_STRING_SHORT[7][3];
constexpr const uint8_t DATE::DAYS_IN_MONTH[12];

DATE::DATE(uint8_t day, uint8_t month, uint16_t year){
	this->day = day;
	this->month = month;
	this->year = year;
}

void DATE::setDate(uint8_t day, uint8_t month, uint16_t year){
	this->day = day;
	this->month = month;
	this->year = year;
}

void DATE::setDay(uint8_t day){
	this->day = day;
}
void DATE::setMonth(uint8_t month){
	this->month = month;
}
void DATE::setYear(uint16_t year){
	this->year = year;
}

uint8_t DATE::getDay(){
	return day;
}
uint8_t DATE::getMonth(){
	return month;
}
uint16_t DATE::getYear(){
	return year;
}

void DATE::getString(char * string){
	sprintf(string, "%d.%d.%d", day, month, year);
}

bool DATE::isLeapYear(){
	return isLeapYear(this->year);
}
bool DATE::isLeapYear(uint16_t year){
	if(year%400 || ((year%4==0) && (year%100!=0)))return true;
	return false;
}



DATE::WEEKDAY DATE::getWeekday(){
	return DATE::getWeekday(day, month, year);
}
DATE::WEEKDAY DATE::getWeekday(uint8_t day, uint8_t month, uint16_t year){
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	return (WEEKDAY) ((year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7);
}

char* DATE::getWeekdayString(){
	return (char*) WEEKDAY_STRING[(int)getWeekday()];
}
char* DATE::getWeekdayString(WEEKDAY weekday){
	return (char*) WEEKDAY_STRING[(int)weekday];
}


DATETIME::DATETIME(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint16_t year) :
		DATE(day, month, year), TIME(sec, min, hour){

}

void DATETIME::getString(char * string){
	sprintf(string, "%d:%d:%d %d.%d.%d", hour, min, sec, day, month, year);
}

