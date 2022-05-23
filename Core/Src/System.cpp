/*
 * System.cpp
 *
 *  Created on: 23.10.2020
 *      Author: SHON
 */

#include "System.hpp"


uint16_t System::loopsInTenMs;



void System::SystemErrorHandler(){
	while(1){


	}
}


uint32_t System::getTick(){
	return HAL_GetTick();
}


void System::setLoopsInTenMs(uint16_t s){
	loopsInTenMs=s;
}


uint16_t System::getLoopsInTenMs(){
	return loopsInTenMs;
}



int32_t System::map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void System::get12BUID(uint8_t* address){
	uint32_t q[3] = {HAL_GetUIDw0(), HAL_GetUIDw1(), HAL_GetUIDw2()};
	memcpy(address, q, 12);
}

uint32_t System::getSKID(){
	uint8_t uid[12];
	get12BUID(uid);

	etl::crc32 crc;

	for(uint8_t q=0;q<12;q++){
		crc.add(uid[q]);
	}
	return crc.value();
}


int System::logLn(const char *format, ...)
{
   va_list arg;
   int done;

   printf("SKWL-[LOG-%04d.%03d] ", getTick()/1000 , getTick()%1000);

   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

   printf("\r\n");

   return done;
}


