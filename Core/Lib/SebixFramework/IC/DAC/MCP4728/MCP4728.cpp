/*
 * MCP4728.cpp
 *
 *  Created on: 08.09.2020
 *      Author: SHON
 */

#include "MCP4728.hpp"

MCP4728::MCP4728(I2C * I2CInstance, uint8_t Address, uint32_t RefRate){
	this->I2CInstance=I2CInstance;
	this->Address=Address;

	this->RefRate=RefRate;

	this->lastRef = 0;


}

void MCP4728::registerChannel(MCP4728_CHANNEL * channel){
	Channels[(int8_t) channel->getChannel()]=channel;
}

void MCP4728::ref(){
	if(Channels[0]->isNewData() || Channels[1]->isNewData() || Channels[2]->isNewData() || Channels[3]->isNewData()){
		Channels[0]->downloadDataStruct(&DataBuffor[0]);
		Channels[1]->downloadDataStruct(&DataBuffor[3]);
		Channels[2]->downloadDataStruct(&DataBuffor[6]);
		Channels[3]->downloadDataStruct(&DataBuffor[9]);
		HAL_I2C_Master_Transmit(I2CInstance->getI2CHandler(), Address, DataBuffor, 12, I2CTIMEOUT);
	}
}

void MCP4728::init(){

}

void MCP4728::iterate(uint32_t TICK){
	if(TICK - lastRef > RefRate){
		lastRef=TICK;
		if(Channels[0]->isNewData() || Channels[1]->isNewData() || Channels[2]->isNewData() || Channels[3]->isNewData()){

			Channels[0]->downloadDataStruct(&DataBuffor[0]);
			Channels[1]->downloadDataStruct(&DataBuffor[3]);
			Channels[2]->downloadDataStruct(&DataBuffor[6]);
			Channels[3]->downloadDataStruct(&DataBuffor[9]);
			HAL_I2C_Master_Transmit_DMA(I2CInstance->getI2CHandler(), Address, DataBuffor, 12);
		}
	}
}


MCP4728_CHANNEL::MCP4728_CHANNEL(MCP4728::DAC_CH Channel){
	this->RawValue = 0;
	this->min = 0;
	this->max = 0;

	this->Channel=Channel;
	this->Gain=MCP4728::GAIN::X1;
	this->PWRDown=MCP4728::PWR_DOWN::NORMAL;
	this->VRef=MCP4728::VREF::VDD;

	this->newData=true;
}

void MCP4728_CHANNEL::setValue(uint16_t value){
	RawValue=(value - min) * (4096 - 0) / (max - min) + 0;
	this->newData=true;
}
void MCP4728_CHANNEL::setMapping(int16_t min, int16_t max){
	this->min = min;
	this->max = max;
	this->newData=true;
}

void MCP4728_CHANNEL::init(){

}

void MCP4728_CHANNEL::downloadDataStruct(uint8_t * data){
	data[0]  = (uint8_t) MCP4728::CMD::MULTI_WRITE;
	data[0] |= (((uint8_t) Channel) << 1);


	data[1]  = ((uint8_t) VRef) << 7;
	data[1] |= ((uint8_t) PWRDown) << 5;
	data[1] |= ((uint8_t) Gain) << 4;
	data[1] |= RawValue >> 8;

	data[2] = RawValue & (0xFF);

	newData=false;
}

uint16_t MCP4728_CHANNEL::getMaxValue(){
	return max;
}


void MCP4728_CHANNEL::setVRef(MCP4728::VREF VRef){
	this->VRef=VRef;
	this->newData=true;
}
void MCP4728_CHANNEL::setPWRDown(MCP4728::PWR_DOWN PWRDown){
	this->PWRDown=PWRDown;
	this->newData=true;
}
void MCP4728_CHANNEL::setGain(MCP4728::GAIN Gain){
	this->Gain=Gain;
	this->newData=true;
}

MCP4728::DAC_CH MCP4728_CHANNEL::getChannel(){
	return Channel;
}
MCP4728::VREF MCP4728_CHANNEL::getVRef(){
	return VRef;
}
MCP4728::PWR_DOWN MCP4728_CHANNEL::getPWRDown(){
	return PWRDown;
}
MCP4728::GAIN MCP4728_CHANNEL::getGain(){
	return Gain;
}

bool MCP4728_CHANNEL::isNewData(){
	return newData;
}


