/*
 * MCP4728.hpp
 *
 *  Created on: 08.09.2020
 *      Author: SHON
 */

#ifndef IC_DAC_MCP4728_MCP4728_HPP_
#define IC_DAC_MCP4728_MCP4728_HPP_

#include <stdint.h>
#include <Generic/GenericAnalog.hpp>
#include <Interfaces/I2C/I2C.hpp>

class MCP4728_CHANNEL;

class MCP4728{
public:
	enum class CMD {FAST_WRITE = 0x00, MULTI_WRITE = 0x40, SINGLE_WRITE = 0x58, SEQ_WRITE = 0x50, SELECT_VREF = 0x80, SELECT_GAIN = 0xC0, SELECT_PWRDOWN = 0xA0};
	enum class DAC_CH {A, B, C, D};
	enum class VREF {VDD, INTERNAL_2_8V};
	enum class PWR_DOWN {NORMAL, GND_1KOHM, GND_100KOHM, GND_500KOHM};
	enum class GAIN {X1, X2};

	MCP4728()=default;
	MCP4728(I2C * I2CInstance, uint8_t Address, uint32_t RefRate);

	void registerChannel(MCP4728_CHANNEL * channel);

	void ref();

	void init();

	void iterate(uint32_t TICK);


private:
	static const uint8_t I2CTIMEOUT = 10;

	MCP4728_CHANNEL * Channels[4];
	uint8_t DataBuffor[12];

	I2C * I2CInstance;
	uint8_t Address;

	uint32_t RefRate;
	uint32_t lastRef;




};

class MCP4728_CHANNEL : public DAC_CHANNEL_GENERIC{
public:
	MCP4728_CHANNEL()=default;
	MCP4728_CHANNEL(MCP4728::DAC_CH Channel);

	void setValue(uint16_t value);
	void setMapping(int16_t min, int16_t max);

	uint16_t getMaxValue();

	void init();

	void setVRef(MCP4728::VREF VRef);
	void setPWRDown(MCP4728::PWR_DOWN PWRDown);
	void setGain(MCP4728::GAIN Gain);

	MCP4728::DAC_CH getChannel();
	MCP4728::VREF getVRef();
	MCP4728::PWR_DOWN getPWRDown();
	MCP4728::GAIN getGain();

	bool isNewData();

	void downloadDataStruct(uint8_t * data);

private:
	uint16_t max;
	uint16_t min;

	uint16_t RawValue;

	bool newData;

	MCP4728::DAC_CH Channel;
	MCP4728::VREF VRef;
	MCP4728::PWR_DOWN PWRDown;
	MCP4728::GAIN Gain;

};




#endif /* IC_DAC_MCP4728_MCP4728_HPP_ */
