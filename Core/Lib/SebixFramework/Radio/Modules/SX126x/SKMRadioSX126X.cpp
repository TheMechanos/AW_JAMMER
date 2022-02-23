/*
 * SKMRadioSX126X.cpp
 *
 *  Created on: 18 gru 2021
 *      Author: skocz
 */

#include <Radio/Modules/SX126x/SKMRadioSX126X.hpp>

SKMRadioSX126X::SKMRadioSX126X(SubGhz *subGhz, RadioRFSwitch *rfsw) :
		SX126x(subGhz, rfsw){

	txTimeout = 100;

	isSleep = false;
	isReceiving = false;
}

void SKMRadioSX126X::configTxTimeout(uint16_t msTxTimeout){
	this->txTimeout = msTxTimeout;
}

void SKMRadioSX126X::setSleep(){
	SleepConfig sc;
	sc.RTCWakeUp = false;
	sc.startType = SleepConfig::Start::Warm;
	setModeSleep(sc);

	isSleep = true;
	isReceiving = false;
}

void SKMRadioSX126X::setIdle(){
	setModeSTDBY(SX126x::STDBY::RC);
	isSleep = false;
	isReceiving = false;
}

void SKMRadioSX126X::setRx(){
	setModeRxCont();
	isSleep = false;
	isReceiving = false;
}


SKMRadioSX126X::State SKMRadioSX126X::getState(){//Sleep, Busy, Idle, Rx, Tx
	SX126x::Status st = getStatus();

	if(isReceiving){
		return State::Busy;
	}
	if(isSleep){
		return State::Sleep;
	}
	if(st.mode == SX126x::Status::Mode::RX){
		return State::Rx;
	}
	if(st.mode == SX126x::Status::Mode::TX){
		return State::Tx;
	}
	if(st.mode == SX126x::Status::Mode::STDBY_RC || st.mode == SX126x::Status::Mode::STDBY_XOSC){
		return State::Idle;
	}
	return State::Busy;
}

void SKMRadioSX126X::sendPacket(SKMPacket* packet){
	isSleep = false;
	isReceiving = false;
	transmitPacket(packet, txTimeout);
}

uint16_t SKMRadioSX126X::importAvalaiblePacket(SKMPacket* packet){
	if(getStatus().radio == Status::Radio::DataAvailable){

		PacketStatus packetStatus = getPacketStatus();
		if(packetStatus.GFSK.Status.crcError == false){

			RxBufferState rxb = getRxBufferStatus();

			packet->setTotalSize(rxb.payloadLengthRx);
			readBuffer(rxb.rxStartBufferPointer, packet->idx, rxb.payloadLengthRx);

			return rxb.payloadLengthRx;
		}
	}
	return 0;
}

void SKMRadioSX126X::iterate(){

}


/*
void SKMRadioSX126X::sendPacket(SKMPacket* packet){
	if(mode == Mode::ContRx || mode == Mode::Disabled)return;
	txQueue.push(*packet);
}

void SKMRadioSX126X::iterate(){
	if(mode == Mode::Disabled)return;


	if(mode == Mode::RxWithAutoTx || mode == Mode::SendOnly){
		auto stat = getStatus();
		if(txQueue.size() > 0 && stat.mode != SX126x::Status::Mode::TX){
			SKMPacket p = txQueue.front();
			txQueue.pop();
			transmitPacket(&p, txTimeout);
		}
	}
}

void SKMRadioSX126X::setMode(Mode newMode){
	if(newMode == Mode::ContRx){
		setModeRxCont();

	}else if(newMode == Mode::SendOnly){
		setModeSTDBY(SX126x::STDBY::RC);

	}else if(newMode == Mode::Disabled){
		SleepConfig sc;
		sc.RTCWakeUp = false;
		sc.startType = SleepConfig::Start::Warm;
		setModeSleep(sc);

	}else if(newMode == Mode::RxWithAutoTx){
		setModeRxCont();

	}

	mode = newMode;
}
*/

void SKMRadioSX126X::transmitPacket(SKMPacket* packet, uint32_t timeout){
	transmit(packet->idx, packet->getTotalSize(), timeout);
}

uint8_t SKMRadioSX126X::receivePacket(SKMPacket* packet, uint32_t timeout){
	uint8_t data[255];
	uint8_t len = receive(data, packet->getPacketMaxLength(), timeout);

	packet->setTotalSize(len);

	for(uint8_t q=0;q<len;q++){
		packet->idx[q] = data[q];
	}
	return len - SKMPacket::SizeHeader;
}

void SKMRadioSX126X::transmit(uint8_t *buffer, uint8_t size, uint32_t timeout) {

	setModeSTDBY();

	setPacketSize(size);
	writeBuffer(0, buffer, size);

	rfsw->set(RadioRFSwitch::Mode::Tx);
	setModeTx(timeout*1000);

}

uint8_t SKMRadioSX126X::receive(uint8_t *buffer, uint8_t size, uint32_t timeout) {

	if(conf->packetParams.GFSK.packetLength == PacketParams::PacketLength::Const){
		setPacketSize(size);
	}else{
		setConfigPacketSize();
	}

	rfsw->set(RadioRFSwitch::Mode::Rx);
	setModeRx(timeout*1000);

	uint32_t endTick = System::getTick() + timeout;
	while (1) {
		if(System::getTick() > endTick){
			return 0;
		}

		Status s = getStatus();

		if(s.radio == Status::Radio::DataAvailable){
			PacketStatus packetStatus = getPacketStatus();

			if(packetStatus.GFSK.Status.crcError == false){
				break;
			}else{
				return 0;
			}

		}

	}
	RxBufferState rxb = getRxBufferStatus();

	if(rxb.payloadLengthRx > size){
		return 0;
	}

	readBuffer(rxb.rxStartBufferPointer, buffer, rxb.payloadLengthRx);

	return rxb.payloadLengthRx;

}





void SKMRadioSX126X::irqTxCpltCallback(){
	/*if(mode == Mode::RxWithAutoTx){
		setModeRxCont();
	}else{
		setModeSTDBY(SX126x::STDBY::RC);
	}*/
	listner->onTxDone();
}

void SKMRadioSX126X::irqRxCpltCallback(){
	isReceiving = false;
	/*if(mode == Mode::ContRx){
		importAvalaiblePacket();
		setModeRxCont();

	}else if(mode == Mode::RxWithAutoTx){
		importAvalaiblePacket();
		setModeRxCont();

	}*/
	listner->onRxDone();
}

void SKMRadioSX126X::irqPreambleDetectedCallback(){
	isReceiving = true;
}

void SKMRadioSX126X::irqSyncWordValidCallback(){

}

void SKMRadioSX126X::irqCRCErrorCallback(){
	isReceiving = false;
	listner->onTxRxFail();
}

void SKMRadioSX126X::irqRxTxTimeoutCallback(){
	isReceiving = false;
	listner->onTxRxFail();
}
