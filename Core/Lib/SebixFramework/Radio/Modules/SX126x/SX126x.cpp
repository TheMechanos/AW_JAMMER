/*
 * SX1262.cpp
 *
 *  Created on: Dec 8, 2021
 *      Author: user
 */

#include "SX126x.hpp"


SX126x::SX126x(SubGhz* subGhz, RadioRFSwitch* rfsw){
	this->subGhz = subGhz;
	this->rfsw = rfsw;
}

void SX126x::init() {

}

SX126x::RxBufferState SX126x::getRxBufferStatus(){
	return readRxBufferStatus();
}
SX126x::PacketStatus SX126x::getPacketStatus(){
	return readPacketStatus();
}
int8_t SX126x::getRssiInst(){
	return readRssiInst();
}
SX126x::Status SX126x::getStatus(){
	return readStatus();
}


void SX126x::writeBuffer(uint8_t offset, uint8_t *data, size_t size) {
	radioWriteBuffer(offset, data, size);
}

void SX126x::readBuffer(uint8_t offset, uint8_t *data, size_t size) {
	radioReadBuffer(offset, data, size);
}

void SX126x::setPacketSize(uint8_t size){
	writePacketSize(size);
}




void SX126x::config(SX126xConfig *conf) {
	this->conf = conf;

	setModeSTDBY(SX126x::STDBY::RC);

	writePacketType(conf->packetType);

	if(conf->txClamp){
		writeTxClampEnable();
	}

	writeRegulatorMode(conf->regulationMode);

	writeBufferBaseAddress(0, 0);

	writeModParams(conf->modParams);

	writeFrequency(conf->frequency);

	writeTxParams(conf->txParams);

	writePacketParams(conf->packetParams);
	writeIrq((uint16_t) SX126x::IrqType::all, (uint16_t) SX126x::IrqType::all, 0, 0);
}


void SX126x::setModeSleep(SleepConfig sleep){
	uint8_t buf = 0;

	if(sleep.startType == SleepConfig::Start::Warm){
		buf |= (1<<2);
	}
	if(sleep.RTCWakeUp){
		buf |= (1<<0);
	}
	radioExecSetCmd(Comm::setSleep, &buf, 1);

}

void SX126x::setModeSTDBY(STDBY mode){
	uint8_t buf[1];
	buf[0] = (uint8_t)mode;

	radioExecSetCmd(Comm::setStandby, buf, 1);
}

void SX126x::setModeFS(){
	radioExecSetCmd(Comm::setFS, 0, 0);
}

void SX126x::setModeTx(uint32_t usTimeout){
	usTimeout /= 15;
	uint8_t buf[3];
	buf[0] = (usTimeout>>16)&0xFF;
	buf[1] = (usTimeout>>8) &0xFF;
	buf[2] = (usTimeout)    &0xFF;

	radioExecSetCmd(Comm::setTx, buf, 3);
}

void SX126x::setModeRx(uint32_t usTimeout){
	usTimeout /= 15;
	uint8_t buf[3];
	buf[0] = (usTimeout>>16)&0xFF;
	buf[1] = (usTimeout>>8) &0xFF;
	buf[2] = (usTimeout)    &0xFF;
	radioExecSetCmd(Comm::setRx, buf, 3);
}
void SX126x::setModeRxCont(){
	uint8_t buf[3];
	buf[0] = 0xFF;
	buf[1] = 0xFF;
	buf[2] = 0xFF;
	radioExecSetCmd(Comm::setRx, buf, 3);
}








SX126x::Status SX126x::readStatus(){

	uint8_t radioResult=0;
	radioExecGetCmd(Comm::getStatus, &radioResult, 1);

	return decodeStatus(radioResult);
}


SX126x::Status SX126x::decodeStatus(uint8_t data){
	Status status;

	uint8_t radioMode   = ((data & 0x70) >> 4);
	uint8_t radioStatus = ((data & 0x0E) >> 1);

	status.mode = (Status::Mode)radioMode;
	status.radio = (Status::Radio)radioStatus;

	return status;
}



void SX126x::writeCalibrateImage(uint32_t frequency) {
	uint8_t calFreq[2];

	if (frequency > 900000000) {
		calFreq[0] = 0xE1;
		calFreq[1] = 0xE9;
	} else if (frequency > 850000000) {
		calFreq[0] = 0xD7;
		calFreq[1] = 0xDB;
	} else if (frequency > 770000000) {
		calFreq[0] = 0xC1;
		calFreq[1] = 0xC5;
	} else if (frequency > 460000000) {
		calFreq[0] = 0x75;
		calFreq[1] = 0x81;
	} else if (frequency > 425000000) {
		calFreq[0] = 0x6B;
		calFreq[1] = 0x6F;
	}
	radioExecSetCmd(Comm::calibrateImage, calFreq, 2);
}


void SX126x::writeSyncWords(uint8_t *syncWord, size_t size){
	uint8_t buf[8];
	for(uint8_t q=0;q<size;q++){
		buf[q]=*(syncWord+q);
	}
	radioWriteRegisters(Reg::syncWordBase, buf, size);
}

void SX126x::writeCRCSeed(uint16_t seed) {
	uint8_t buf[2];

	buf[0] = (uint8_t) ((seed >> 8) & 0xFF);
	buf[1] = (uint8_t) (seed & 0xFF);

	radioWriteRegisters(Reg::crcSeedBase, buf, 2);
}

void SX126x::writeCRCPolynomial(uint16_t polynomial) {
	uint8_t buf[2];

	buf[0] = (uint8_t) ((polynomial >> 8) & 0xFF);
	buf[1] = (uint8_t) (polynomial & 0xFF);

	radioWriteRegisters(Reg::crcPolyBase, buf, 2);
}

void SX126x::writeWhiteningSeed(uint16_t seed) {
	uint8_t regValue = 0;

	radioReadRegister(Reg::whiteBaseMSB, &regValue);
	regValue &= 0xFE;

	regValue = ((seed >> 8) & 0x01) | regValue;
	radioWriteRegister(Reg::whiteBaseMSB, regValue); // only 1 bit.
	radioWriteRegister(Reg::whiteBaseLSB, (uint8_t) seed);
}

void SX126x::writeAddressNode(uint8_t nodeAddress){
	radioWriteRegister(Reg::nodeAddress, nodeAddress);
}

void SX126x::writeBroadcastNode(uint8_t broadcastAddress){
	radioWriteRegister(Reg::broadcastAddress, broadcastAddress);
}

void SX126x::writeLoRaSymbolNumberTimeout(uint8_t loraSymbolTimeout) {
	radioExecSetCmd(Comm::setLoraSymbTimeout, &loraSymbolTimeout, 1);
}


void SX126x::writeFrequency(uint32_t newFrequency) {

	writeCalibrateImage(newFrequency);

	uint32_t temp = (uint32_t) ((((uint64_t) newFrequency) << 25) / (32000000UL));
	uint8_t buf[4];
	buf[0] = (temp >> 24) & 0xFF;
	buf[1] = (temp >> 16) & 0xFF;
	buf[2] = (temp >> 8) & 0xFF;
	buf[3] = (temp) & 0xFF;

	radioExecSetCmd(Comm::setRfFrequency, buf, 4);
}

void SX126x::writeTxParams(TxParams newTxParams) {
	uint8_t buf[4];

	switch (newTxParams.power) {
	case TxParams::Power::P14dBm:
		buf[0] = 0x02;
		buf[1] = 0x02;
		break;
	case TxParams::Power::P17dBm:
		buf[0] = 0x02;
		buf[1] = 0x03;
		break;
	case TxParams::Power::P20dBm:
		buf[0] = 0x03;
		buf[1] = 0x05;
		break;
	case TxParams::Power::P22dBm:
		buf[0] = 0x04;
		buf[1] = 0x07;
		break;
	}
	buf[2] = 0x00;
	buf[3] = 0x01;

	radioExecSetCmd(Comm::setPaConfig, buf, 4);

	uint8_t buf2[2];
	buf2[0] = (uint8_t) newTxParams.power;
	buf2[1] = (uint8_t) newTxParams.ramp;

	radioExecSetCmd(Comm::setTxParams, buf2, 2);

	radioWriteRegister(Reg::ocpConfiguration, 0x38);
}

void SX126x::writeBufferBaseAddress(uint8_t newTxBaseAddress, uint8_t newRxBaseAddress) {
	uint8_t buf[2];
	buf[0]=newTxBaseAddress;
	buf[1]=newRxBaseAddress;

	radioExecSetCmd(Comm::setBufferBaseAddress, buf, 2);

}


void SX126x::writePacketType(PacketType newPacketType){
	this->packetType = newPacketType;

	uint8_t buffer = (uint8_t) newPacketType;
	radioExecSetCmd(Comm::setPacketType, &buffer, 1);
}

void SX126x::writeModParams(ModParams newModParams){

	if(packetType == PacketType::GFSK){
		uint8_t buf[8];

		uint32_t bitrate = 1024000000 / newModParams.GFSK.bitRate;
		buf[0]= (bitrate>>16)&0xFF;
		buf[1]= (bitrate>>8) &0xFF;
		buf[2]= (bitrate)    &0xFF;

		buf[3]=(uint8_t)newModParams.GFSK.pulseShape;

		buf[4]=(uint8_t)newModParams.GFSK.bandWidth;

		uint32_t fdev = (uint32_t) ((((uint64_t) newModParams.GFSK.freqDeviation) << 25) / (32000000UL));
		buf[5] = (fdev >> 16) & 0xFF;
		buf[6] = (fdev >> 8) & 0xFF;
		buf[7] = (fdev) & 0xFF;

		radioExecSetCmd(Comm::setModulationParams, buf, 8);

	}else if(packetType == PacketType::LoRa){
		uint8_t buf[8];

		buf[0] = (uint8_t) newModParams.LoRa.sf;
		buf[1] = (uint8_t) newModParams.LoRa.bandWidth;
		buf[2] = (uint8_t) newModParams.LoRa.cr;
		buf[3] = (uint8_t) newModParams.LoRa.lowDataRateOptimize;
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 0;
		buf[7] = 0;

		radioExecSetCmd(Comm::setModulationParams, buf, 8);
	}
}

void SX126x::writePacketParams(PacketParams newPacketParams) {

	if (packetType == PacketType::GFSK) {

		uint8_t buf[9];

		buf[0] = (newPacketParams.GFSK.preambleLength >> 8) & 0xFF;
		buf[1] = (newPacketParams.GFSK.preambleLength) & 0xFF;

		buf[2] = (uint8_t) newPacketParams.GFSK.preambleDetector;

		buf[3] = newPacketParams.GFSK.syncWordLength*8;

		buf[4] = (uint8_t) newPacketParams.GFSK.addressCompare;

		buf[5] = (uint8_t) newPacketParams.GFSK.packetLength;

		buf[6] = newPacketParams.GFSK.payloadLength;

		buf[7] = (uint8_t) newPacketParams.GFSK.crcType;

		buf[8] = (uint8_t) newPacketParams.GFSK.whitening;

		radioExecSetCmd(Comm::setPacketParams, buf, 9);

		writeCRCSeed(newPacketParams.GFSK.crcSeed);
		writeCRCPolynomial(newPacketParams.GFSK.crcPolynomial);

		writeSyncWords(newPacketParams.GFSK.syncWords, newPacketParams.GFSK.syncWordLength);

		writeAddressNode(newPacketParams.GFSK.nodeAddress);
		writeBroadcastNode(newPacketParams.GFSK.broadcastAddress);

		writeWhiteningSeed(newPacketParams.GFSK.whiteningSeed);

	}else if(packetType == PacketType::LoRa){
		uint8_t buf[9];

		buf[0] = (newPacketParams.LoRa.preambleLength >> 8) & 0xFF;
		buf[1] = (newPacketParams.LoRa.preambleLength) & 0xFF;

		buf[2] = (uint8_t) newPacketParams.LoRa.headerType;

		buf[3] = newPacketParams.LoRa.payloadLength;

		buf[4] = (uint8_t) newPacketParams.LoRa.crcType;

		buf[5] = (uint8_t) newPacketParams.LoRa.invertIQ;

		buf[6] = 0;
		buf[7] = 0;
		buf[8] = 0;

		radioExecSetCmd(Comm::setPacketParams, buf, 9);

		writeLoRaSymbolNumberTimeout(newPacketParams.LoRa.symbolsNumberTimeout);
	}
}

void SX126x::writePacketSize(uint8_t size){
	PacketParams packetParams = conf->packetParams;

	packetParams.GFSK.payloadLength = size;
	writePacketParams(packetParams);
}

void SX126x::setConfigPacketSize(){
	writePacketParams(conf->packetParams);
}

void SX126x::writeRegulatorMode(RegulatorMode newRegulatorMode){
	uint8_t buf[1];
	buf[0] = (uint8_t) newRegulatorMode;
	radioExecSetCmd(Comm::setRegulatorMode, buf, 1);
}

void SX126x::writeIrq(uint16_t mask, uint16_t DIO1, uint16_t DIO2, uint16_t DIO3) {
    uint8_t buf[8];

    buf[0] = ( uint8_t )( ( mask >> 8 ) & 0x00FF );
    buf[1] = ( uint8_t )( mask & 0x00FF );
    buf[2] = ( uint8_t )( ( DIO1 >> 8 ) & 0x00FF );
    buf[3] = ( uint8_t )( DIO1 & 0x00FF );
    buf[4] = ( uint8_t )( ( DIO2 >> 8 ) & 0x00FF );
    buf[5] = ( uint8_t )( DIO2 & 0x00FF );
    buf[6] = ( uint8_t )( ( DIO3 >> 8 ) & 0x00FF );
    buf[7] = ( uint8_t )( DIO3 & 0x00FF );
    radioExecSetCmd(Comm::cfgDioIRQ, buf, 8);
}


void SX126x::clearDeviceErrors(){
	uint8_t buf[2] = { 0x00, 0x00 };
	radioExecSetCmd(Comm::clrError, buf, 2 );
}

void SX126x::clearIrqStatus(uint16_t irq) {
	uint8_t buf[4];

	buf[0] = (uint8_t) (((uint16_t) irq >> 8) & 0x00FF);
	buf[1] = (uint8_t) ((uint16_t) irq & 0x00FF);
	radioExecSetCmd(Comm::clrIRQStatus, buf, 2);
}

uint32_t SX126x::readRandom() {
	uint32_t number = 0;
	uint8_t regAnaLna = 0;
	uint8_t regAnaMixer = 0;

	radioReadRegister(Reg::anaLna, &regAnaLna);
	radioWriteRegister(Reg::anaLna, regAnaLna & ~(1 << 0));

	radioReadRegister(Reg::anaMixer, &regAnaMixer);
	radioWriteRegister(Reg::anaMixer, regAnaMixer & ~(1 << 7));

	// Set radio in continuous reception
	setModeRxCont();

	radioReadRegisters(Reg::randomNumberBase, (uint8_t*) &number, 4);

	setModeSTDBY(STDBY::RC);

	radioWriteRegister(Reg::anaLna, regAnaLna);
	radioWriteRegister(Reg::anaMixer, regAnaMixer);

	return number;

}



SX126x::RxBufferState SX126x::readRxBufferStatus() {
	RxBufferState stat;
	uint8_t buf[2];
	radioExecGetCmd(Comm::getRxBufferStatus, buf, 2);

	stat.payloadLengthRx = buf[0];
	stat.rxStartBufferPointer = buf[1];

	return stat;
}

SX126x::PacketStatus SX126x::readPacketStatus() {
	PacketStatus stat;
	uint8_t buf[3];
	radioExecGetCmd(Comm::getPacketStatus, buf, 3);


	stat.GFSK.Status.preambleError=buf[0] & (1<<7);
	stat.GFSK.Status.syncError = buf[0] & (1<<6);
	stat.GFSK.Status.addressError = buf[0] & (1<<5);
	stat.GFSK.Status.crcError = buf[0] & (1<<4);
	stat.GFSK.Status.lengthError = buf[0] & (1<<3);
	stat.GFSK.Status.abortError = buf[0] & (1<<2);
	stat.GFSK.Status.packerReceived = buf[0] & (1<<1);
	stat.GFSK.Status.packetSent = buf[0] & (1<<0);

	stat.GFSK.rssiSync = -(buf[1]/2);
	stat.GFSK.rssiAvg = -(buf[2]/2);

	return stat;
}

int8_t SX126x::readRssiInst() {
	uint8_t buf[2];
	radioExecGetCmd(Comm::getRSSIInst, buf, 2);

	return -(buf[1]/2);
}

void SX126x::writeTxClampEnable() {
	uint8_t buf;
	radioReadRegister(Reg::txClamp, &buf);
	buf |= 0x1E;
	radioWriteRegister(Reg::txClamp, buf);
}

void SX126x::writeRxGain(bool state) {
	uint8_t buf;
	if(state){
		buf=0x96;
	}else{
		buf=0x94;
	}
	radioWriteRegister(Reg::rxGain, buf);
}









HAL_StatusTypeDef SX126x::radioExecSetCmd(Comm command, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->execSetCmd((uint8_t) command, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioExecGetCmd(Comm command, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->execGetCmd((uint8_t) command, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioWriteBuffer(uint8_t Offset, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->writeBuffer(Offset, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioReadBuffer(uint8_t Offset, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->readBuffer(Offset, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioWriteRegisters(Reg Address, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->writeRegisters((uint8_t)Address, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioReadRegisters(Reg Address, uint8_t *pBuffer,
		uint16_t Size) {

	return subGhz->readRegisters((uint8_t)Address, pBuffer, Size);
}

HAL_StatusTypeDef SX126x::radioWriteRegister(Reg Address, uint8_t Value) {

	return subGhz->writeRegister((uint8_t)Address, Value);
}

HAL_StatusTypeDef SX126x::radioReadRegister(Reg Address, uint8_t *pValue) {

	return subGhz->readRegister((uint8_t)Address, pValue);
}


