/*
 * HalArray.hpp
 *
 *  Created on: 29 mar 2021
 *      Author: SHON
 */

#ifndef SRC_FEATURES_HALARRAY_HALARRAY_HPP_
#define SRC_FEATURES_HALARRAY_HALARRAY_HPP_

#include <System.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <Interfaces/SPI/SPI.hpp>


class Shift74HC165 : public SPI_EventListener{
public:
	enum class Stage{Off, Wait, Latch, Receive};

	Shift74HC165()=default;
	Shift74HC165(SPI* spi, OUTPUT_ADVENCED* lt, uint32_t refInterval);


	void init(uint8_t* data, uint8_t dataSize);

	void start();
	void stop();

	uint8_t getByte(uint8_t byte);
	bool getBit(uint16_t bit);


	void iterate(uint32_t tick);

	virtual void onDMARxCmplt();

private:

	SPI* spi;
	OUTPUT_ADVENCED* lt;
	uint32_t refInterval;

	uint32_t lastRefresh;

	Stage stage;
public:
	uint8_t* data;
	uint8_t dataSize;

};



#endif /* SRC_FEATURES_HALARRAY_HALARRAY_HPP_ */
