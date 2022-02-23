/*
 * SKMController.hpp
 *
 *  Created on: 16 lut 2022
 *      Author: skocz
 */

#ifndef LIB_SEBIXFRAMEWORK_RADIO_SKM_CONTROLLERS_SKMCONTROLLER_HPP_
#define LIB_SEBIXFRAMEWORK_RADIO_SKM_CONTROLLERS_SKMCONTROLLER_HPP_

#include <System.hpp>
#include <Radio/SKM/Packet.hpp>
#include <Radio/SKM/SKMRadio.hpp>
#include <Software/CircuralContainers/CircularQueue.h>
#include <Software/CircuralContainers/CircularDeque.h>

#include <Software/Vector/Vector.h>

class SKMController : public SKMRadioListner{
public:
	SKMController();
	SKMController(SKMRadio* radio);


	void init();
	void iterate();

	void enable();
	void disable();
	bool isEnabled();

	void send(SKMPacket* packet);

	virtual void onTxDone();
	virtual void onRxDone();
	virtual void onTxRxFail();

//private:
	SKMRadio* radio;

	SKMPacketStatus arrayPacketStatus[SKM_PACKET_STATUS_QUEUE_SIZE];
	Vector<SKMPacketStatus> packetStatus;

	SKMPacket arrayTxQueue[SKM_PACKET_TX_QUEUE_SIZE];
	Vector<SKMPacket> txQueue;

	SKMPacket arrayRxQueue[SKM_PACKET_RX_QUEUE_SIZE];
	Vector<SKMPacket> rxQueue;



	int16_t actualSendingPacketIndex;

	bool enabled;

	SKMPacketStatus* getPacketStatus(SKMPacket* source);

};

#endif /* LIB_SEBIXFRAMEWORK_RADIO_SKM_CONTROLLERS_SKMCONTROLLER_HPP_ */
