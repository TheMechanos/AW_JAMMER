/*
 * WSLEDDriver.hpp
 *
 *  Created on: 30 mar 2021
 *      Author: SHON
 */

#ifndef SRC_FEATURES_WSLEDDRIVER_WSLEDDRIVER_HPP_
#define SRC_FEATURES_WSLEDDRIVER_WSLEDDRIVER_HPP_

#include <stdint.h>
#include <Interfaces/SPI/SPI.hpp>

//SPI  6Mbit <-> 6.75Mbit.    | 54Mhz / 8 prescaller

class WS2812BDriver : public SPI_EventListener{
public:
	enum class State{Idle, Transmit};
	typedef struct{
		uint8_t g;
		uint8_t r;
		uint8_t b;
	}WSLED;

	void configSlopes(uint8_t zero, uint8_t one);

	WS2812BDriver();
	WS2812BDriver(SPI* spi);

	void cls();

	void init(WSLED* data, uint16_t dataLength);

	void ref();

	void setLed(uint16_t led, WSLED color);
	void setLed(uint16_t led, uint8_t r, uint8_t g, uint8_t b);
	void setWhite(uint16_t led, uint8_t white);
	void setLedR(uint16_t led, uint8_t r);
	void setLedG(uint16_t led, uint8_t g);
	void setLedB(uint16_t led, uint8_t b);


	WSLED* getLedPointer(uint16_t led);


	virtual void onDMATxHalfCmplt();
	virtual void onDMATxCmplt();

private:

	void WSLEDtoBytes(uint16_t led, uint8_t * dat);

	uint8_t buffer[48];
	uint16_t currentLED;
	uint8_t isReset;

	SPI* spi;
	WSLED* data;
	uint16_t dataLength;

	uint8_t zero;
	uint8_t one;


	State state;





};



#endif /* SRC_FEATURES_WSLEDDRIVER_WSLEDDRIVER_HPP_ */
