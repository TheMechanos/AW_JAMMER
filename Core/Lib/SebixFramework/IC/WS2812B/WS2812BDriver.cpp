/*
 * WS2812BDriver.cpp
 *
 *  Created on: 30 mar 2021
 *      Author: SHON
 */

#include <IC/WS2812B/WS2812BDriver.hpp>

WS2812BDriver::WS2812BDriver(){
}

WS2812BDriver::WS2812BDriver(SPI *spi){
	this->spi = spi;
	this->state = State::Idle;

	this->zero= 0b11000000;
	this->one = 0b11111100;


}

void WS2812BDriver::init(WSLED *data, uint16_t dataLength){

	spi->getTxDMA()->configDirectionAlignment(DMA::Direction::MEM_TO_PERIPH, DMA::Mode::CIRCULAR, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);
	spi->init();
	spi->registerListener(this);

	this->data = data;
	this->dataLength = dataLength;

	this->zero= 0b11000000;
	this->one = 0b11111100;

	cls();
	ref();


}

void WS2812BDriver::cls(){
	for(uint8_t q=0; q< dataLength;q++){
		data[q].r=0;
		data[q].g=0;
		data[q].b=0;
	}
}


void WS2812BDriver::ref(){
	if(data==0 || dataLength ==0)return;

	if(state == State::Transmit)return;

	currentLED=0;
	isReset=1;

	state = State::Transmit;

	for(uint8_t q = 0; q < 48; q++){
		buffer[q] = 0;
	}

	spi->transmitDMA(buffer, 48);
}

void WS2812BDriver::configSlopes(uint8_t zero, uint8_t one){
	this->zero = zero;
	this->one = one;
}

void WS2812BDriver::onDMATxHalfCmplt(){ //Zapełnia 0 - 23
	if(isReset){
		isReset=false;
		return;
	}

	if(currentLED > dataLength){
		for(uint8_t q=0;q<48;q++)
			buffer[0]=0;
		spi->stopDMA();
		state = State::Idle;
	}

	WSLEDtoBytes(currentLED, &buffer[0]);
	currentLED++;



}

void WS2812BDriver::onDMATxCmplt(){ //Zapełnia 24-47
	if(currentLED > dataLength){
		for(uint8_t q=0;q<48;q++)
			buffer[0]=0;
		spi->stopDMA();
		state = State::Idle;
	}

	WSLEDtoBytes(currentLED, &buffer[24]);
	currentLED++;


}
void WS2812BDriver::WSLEDtoBytes(uint16_t led, uint8_t *dat){
	uint8_t id=0;
	for(int8_t q = 7; q >= 0 ; q--){
		if(data[led].g & (1 << q)){
			dat[id++] = one;
		}else{
			dat[id++] = zero;
		}
	}

	for(int8_t q = 7; q >= 0 ; q--){
		if(data[led].r & (1 << q)){
			dat[id++] = one;
		}else{
			dat[id++] = zero;
		}
	}

	for(int8_t q = 7; q >= 0 ; q--){
		if(data[led].b & (1 << q)){
			dat[id++] = one;
		}else{
			dat[id++] = zero;
		}
	}

}

void WS2812BDriver::setLed(uint16_t led, WSLED color){
	if(led < dataLength && state != State::Transmit){
		data[led] = color;
	}
}

void WS2812BDriver::setLed(uint16_t led, uint8_t r, uint8_t g, uint8_t b){
	if(led < dataLength && state != State::Transmit){
		data[led].r = r;
		data[led].g = g;
		data[led].b = b;
	}
}
void WS2812BDriver::setWhite(uint16_t led, uint8_t white){
	if(led < dataLength && state != State::Transmit){
		data[led].r = white;
		data[led].g = white;
		data[led].b = white;
	}
}
void WS2812BDriver::setLedR(uint16_t led, uint8_t r){
	if(led < dataLength && state != State::Transmit){
		data[led].r = r;
	}
}

void WS2812BDriver::setLedG(uint16_t led, uint8_t g){
	if(led < dataLength && state != State::Transmit){
		data[led].g = g;
	}
}

void WS2812BDriver::setLedB(uint16_t led, uint8_t b){
	if(led < dataLength && state != State::Transmit){
		data[led].b = b;
	}
}

WS2812BDriver::WSLED* WS2812BDriver::getLedPointer(uint16_t led){
	return &data[led];
}
