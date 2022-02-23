/*
 * App.h
 *
 *  Created on: Dec 7, 2021
 *      Author: skocz
 */

#ifndef INC_APP_HPP_
#define INC_APP_HPP_

#include "stm32wlxx_hal.h"

#include <SKWL.hpp>
#include <System.hpp>

#include <Radio/SKM/Packet.hpp>

class App{
public:
	App();

	void run();


	static App* getInstance();
private:
	static App instance;

	SKWL* dev = SKWL::getInstance();

	uint32_t lastLoopTick;
	uint16_t loopsInTenMs;

	void init();
	void loop();
	void loop10ms();

	uint8_t buffer[10];

};
#endif /* INC_APP_HPP_ */





