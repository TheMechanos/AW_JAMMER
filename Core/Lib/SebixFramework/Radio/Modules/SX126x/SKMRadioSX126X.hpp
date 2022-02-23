/*
 * SX126xController.hpp
 *
 *  Created on: 18 gru 2021
 *      Author: skocz
 */

#ifndef LIB_SEBIXFRAMEWORK_RADIO_MODULES_SX126X_SKMRADIOSX126X_HPP_
#define LIB_SEBIXFRAMEWORK_RADIO_MODULES_SX126X_SKMRADIOSX126X_HPP_

#include "SX126x.hpp"
#include <System.hpp>

#include <Software/CircuralContainers/CircularQueue.h>

#include <Radio/SKM/Packet.hpp>
#include <Radio/SKM/SKMRadio.hpp>

class SKMRadioSX126X : public SX126x, public SKMRadio{
public:
	/*enum class Mode{
		Disabled, SendOnly, ContRx, RxWithAutoTx
	};*/

	SKMRadioSX126X()=default;
	SKMRadioSX126X(SubGhz* subGhz, RadioRFSwitch* rfsw);

	void configTxTimeout(uint16_t msTxTimeout);


	virtual void iterate();

	virtual void setSleep();
	virtual void setIdle();
	virtual void setRx();

	virtual State getState();

	virtual void sendPacket(SKMPacket* packet);
	virtual uint16_t importAvalaiblePacket(SKMPacket* packet);



	void irqTxCpltCallback();
	void irqRxCpltCallback();
	void irqPreambleDetectedCallback();
	void irqSyncWordValidCallback();
	void irqCRCErrorCallback();
	void irqRxTxTimeoutCallback();


private:

	void transmitPacket(SKMPacket* packet, uint32_t timeout);
	uint8_t receivePacket(SKMPacket* packet, uint32_t timeout);

	void transmit(uint8_t* buffer, uint8_t size, uint32_t timeout);
	uint8_t receive(uint8_t* buffer, uint8_t maxSize, uint32_t timeout);

	uint16_t txTimeout;

	bool isSleep;
	bool isReceiving;

	//CircularQueue<SKMPacket, SKM_PACKET_TX_QUEUE_SIZE> txQueue;
	//CircularQueue<SKMPacket, SKM_PACKET_RX_QUEUE_SIZE> rxQueue;

};

#endif /* LIB_SEBIXFRAMEWORK_RADIO_MODULES_SX126X_SKMRADIOSX126X_HPP_ */
