/*
 * App.c
 *
 *  Created on: Dec 7, 2021
 *      Author: skocz
 */

#include <App.hpp>


App App::instance;
App* App::getInstance(){
	return &instance;
}

App::App(){
	this->lastLoopTick=0;
	this->loopsInTenMs=0;
}


void App::run(){
	init();
	while(1){
		loopsInTenMs++;
		loop();

		if(lastLoopTick < System::getTick()-10){
			loop10ms();
			System::setLoopsInTenMs(loopsInTenMs);
			loopsInTenMs=0;
			lastLoopTick = System::getTick();
		}
	}

}


void App::init(){
	dev->init();

	dev->led[0].ON();


	SKMPacket pack[3];

	pack[0].header.packet.id = 1;
	pack[0].setDataSize(1);

	pack[1].header.packet.id = 2;
	pack[1].setDataSize(2);

	pack[2].header.packet.id = 3;
	pack[2].setDataSize(3);

	dev->radio.send(&pack[0]);
	dev->radio.send(&pack[1]);
	dev->radio.send(&pack[2]);

}

//kontrola id pakietu przy dodawaniu

void App::loop(){

	if(uint8_t q = dev->button[0].isMultiClick()){

		static uint16_t idr=0;
		SKMPacket pac;
		pac.header.packet.id = idr++;
		pac.setDataSize(q);

		dev->radio.send(&pac);

		dev->led[2].timeON(300);
	}



	//dev->sx.iterate();

	if(dev->button[2].isMultiClick(2)){ //Send PacketStatusQueue
		System::log("Packet status Queue (size=%d):", dev->radio.packetStatus.size());

		for (uint8_t q = 0; q < dev->radio.packetStatus.size(); q++){
			SKMPacketStatus* s = &dev->radio.packetStatus[q];
			System::log("ID: %d, status: %d, txTime: %d",s->id,s->status,s->sendedTime);
		}

	}


}



void App::loop10ms(){
	dev->iterateNonCritical();
}

