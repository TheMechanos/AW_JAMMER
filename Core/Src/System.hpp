/*
 * System.hpp
 *
 *  Created on: 23.10.2020
 *      Author: SHON
 */

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <stm32wlxx.h>
#include <Software/ETL/crc32.h>

#include <stdarg.h>
#include <stdio.h>

#define SKM_PACKET_STATUS_QUEUE_SIZE 	10
#define SKM_PACKET_TX_QUEUE_SIZE 		20
#define SKM_PACKET_RX_QUEUE_SIZE 		20

#define ETL_NO_STL

class System{
public:

	static void SystemErrorHandler();

	static uint32_t getTick();

	static void setLoopsInTenMs(uint16_t s);

	static uint16_t getLoopsInTenMs();

	static int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

	static void get12BUID(uint8_t* address);
	static uint32_t getSKID();

	static int log(const char *format, ...);


private:
	static uint16_t loopsInTenMs;



};


#endif /* SYSTEM_HPP_ */
