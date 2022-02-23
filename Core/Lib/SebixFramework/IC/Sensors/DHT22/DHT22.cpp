
/*
 * DHT22.cpp
 *
 *  Created on: 29 pa� 2021
 *      Author: skocz
 */

#include "DHT22.hpp"


DHT22::DHT22(PIN *pin, TimerWait *usTimer, uint32_t measureInterval, uint32_t transmisionErrorTolerance){

	this->usTimer = usTimer;
	this->measureInterval = measureInterval;
	this->transmisionErrorTolerance = transmisionErrorTolerance;
	pinSignal = OUTPUT_PIN(pin, OUTPUT_PIN::MODE::OD);

	this->lastMeasure = 0;
	this->transmisionError = 0;

	this->status = Status::INVALID;

}

void DHT22::init(){
	pinSignal.init();

}

void DHT22::iterate(uint32_t TICK){
	if(TICK - lastMeasure > measureInterval){
		bool valid = makeMeasure();

		if(!valid){
			transmisionError++;
			if(transmisionError > transmisionErrorTolerance){
				temperature.set(0, 0);
				humidity.set(0, 0);
				status = Status::ERROR;
			}else{
				status = Status::INVALID;
			}
		}else{
			transmisionError = 0;
			status = Status::OK;
		}

		lastMeasure = TICK;
	}


}

bool DHT22::makeMeasure(){

	uint8_t bits[5];
	uint8_t i, j = 0;

	for(uint8_t q = 0; q < 5; q++){
		bits[q] = 0;
	}

	//reset port
	pinSet(false);
	usTimer->waitUnit(2000);

	pinSet(true);
	usTimer->waitUnit(30);

	usTimer->waitUnit(40);

	//check start condition 1
	if(pinRead()){
		return false;
	}
	usTimer->waitUnit(80);
	//check start condition 2
	if(!(pinRead())){
		return false;
	}
	usTimer->waitUnit(80);

	//read the data
	uint16_t timeoutcounter = 0;
	for(j = 0; j < 5; j++){ //read 5 byte
		uint8_t result = 0;
		for(i = 0; i < 8; i++){ //read every bit
			timeoutcounter = 0;
			while(!(pinRead())){ //wait for an high input (non blocking)
				usTimer->waitUnit(1);
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT){
					return false; //timeout
				}
			}
			usTimer->waitUnit(30);
			if((pinRead())) //if input is high after 30 us, get result
				result |= (1 << (7 - i));
			timeoutcounter = 0;
			while((pinRead())){ //wait until input get low (non blocking)
				usTimer->waitUnit(1);
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT){
					return false; //timeout
				}
			}
		}
		bits[j] = result;
	}

	//reset port
	pinSet(true);


	int16_t temperature;
	int16_t humidity;

	//check checksum
	if((uint8_t) (bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]){
		//return temperature and humidity
		uint16_t rawhumidity = bits[0] << 8 | bits[1];
		uint16_t rawtemperature = bits[2] << 8 | bits[3];

		if(rawtemperature & 0x8000){
			temperature = ((rawtemperature & 0x7FFF)) * -1;
			this->temperature.set(temperature / 10, (temperature*(-1)) % 10);
		}else{
			temperature = ((rawtemperature & 0x7FFF));
			this->temperature.set(temperature / 10, temperature % 10);

		}


		humidity = rawhumidity;
		this->humidity.set(humidity / 10, humidity % 10);

		return true;
	}
	return false;
}

bool DHT22::pinRead(){
	return pinSignal.get();
}

void DHT22::pinSet(bool state){
	pinSignal.set(state);
}
