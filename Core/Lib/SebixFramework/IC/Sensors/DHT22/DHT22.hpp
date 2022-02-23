/*
 * DHT22.hpp
 *
 *  Created on: 29 pa� 2021
 *      Author: skocz
 */

#ifndef SRC_DHT22_DHT22_HPP_
#define SRC_DHT22_DHT22_HPP_

#include <Peripheral/GPIO/IO_Pin.hpp>
#include <Peripheral/GPIO/PIN.hpp>

#include <Peripheral/Timers/Wait/TimerWait.hpp>
#include <System.hpp>
#include <DataTypes/TempAndHum.hpp>

class DHT22{
public:
	enum class Status{OK, INVALID, ERROR};

	DHT22()=default;
	DHT22(PIN* pin, TimerWait* usTimer, uint32_t measureInterval, uint32_t transmisionErrorTolerance);

	void init();

	void iterate(uint32_t TICK);

	bool makeMeasure();

	Temperature getTemperature(){
		return temperature;
	}
	Humidity getHumidity(){
		return humidity;
	}

	Status getStatus(){
		return status;
	}
	bool isError(){
		return status == Status::ERROR;
	}



private:
	TimerWait* usTimer;
	uint32_t measureInterval;
	uint32_t transmisionErrorTolerance;

	OUTPUT_PIN pinSignal;
	uint32_t lastMeasure;
	uint32_t transmisionError;

	Temperature temperature;
	Humidity humidity;

	Status status;

	static const uint16_t DHT_TIMEOUT = 50;

	bool pinRead();
	void pinSet(bool state);

};




#endif /* SRC_DHT22_DHT22_HPP_ */
