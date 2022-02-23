/*
 * DS18B20.hpp
 *
 *  Created on: 3 lis 2021
 *      Author: skocz
 */

#ifndef LIBS_SEBIXFRAMEWORK_IC_SENSORS_DS18B20_DS18B20_HPP_
#define LIBS_SEBIXFRAMEWORK_IC_SENSORS_DS18B20_DS18B20_HPP_

#include <stdio.h>
#include <string.h>

#include <System.hpp>
#include <Interfaces/Software/OneWire/OneWire.hpp>
#include <DataTypes/TempAndHum.hpp>

#include <Parameters/ParameterGeneric.hpp>

#define DS18B20_SCRATCHPAD_SIZE    9

#define DS18B20_READ_ROM           	0x33
#define DS18B20_MATCH_ROM          	0x55
#define DS18B20_SKIP_ROM           	0xCC

#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD    	0xBE
#define DS18B20_WRITE_SCRATCHPAD	0x4E

#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

class DS18B20Rom{
	public:
		DS18B20Rom();
		DS18B20Rom(uint8_t* rom);

		void setRom(uint8_t* rom);
		uint8_t* getRom();
	private:
		uint8_t rom[8];
};


class DS18B20Finder{
public:
	static uint8_t searchSensors(DS18B20Rom* romTable, uint8_t maxSensors, OneWire* oneWire);

private:
	static void searchSensor(uint8_t *diff, uint8_t* id, OneWire* oneWire);
};



class DS18B20{
public:
	enum class Status{OK, INVALID, ERROR};
	enum class Resolution{B9=0, B10, B11, B12};

	DS18B20()=default;
	DS18B20(OneWire* oneWire, uint32_t measureInterval, uint32_t transmisionErrorTolerance);
	//void defineResolution(Resolution res);

	void init();
	void init(DS18B20Rom rom);

	void iterate(uint32_t TICK);

	void startMeasure();
	bool readMeasure();

	Temperature getTemperature(){
		return temperature;
	}
	Status getStatus(){
		return status;
	}
	bool isError(){
		return status == Status::ERROR;
	}


private:
	OneWire* oneWire;
	uint32_t measureInterval;
	uint32_t transmisionErrorTolerance;

	uint32_t lastMeasure;
	uint32_t transmisionError;

	Temperature temperature;
	Status status;

	bool converting;
	DS18B20Rom rom;
	bool romDefined;

	uint16_t conversionTime;
	Resolution resolution;

	void calculateConversionTime();

	constexpr static const uint16_t ResolutionConversionTime[4] = { 94, 188, 375, 750 };
	constexpr static const uint16_t ResolutionDivider[4] = { 2, 4, 8, 16 };
	constexpr static const uint16_t ResolutionMask[4] = { 0xFFF8, 0xFFFC, 0xFFFE, 0xFFFF };

	void sendSetResolution();

	bool readScratchPad(uint8_t* sp);
	void writeScratchPad(uint8_t* sp);

	uint8_t byte_crc(uint8_t crc, uint8_t byte);
	uint8_t wire_crc(const uint8_t* data, int len);

};



#endif /* LIBS_SEBIXFRAMEWORK_IC_SENSORS_DS18B20_DS18B20_HPP_ */
