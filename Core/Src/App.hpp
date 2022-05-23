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

#include <IC/Sensors/ENS210/ENS210.h>

class App{
public:
	App();

	void run();


	static App* getInstance();
private:
	static App instance;
	constexpr static const uint16_t CONFIGS_MAX=3;

	SKWL* dev = SKWL::getInstance();

	uint32_t lastLoopTick;
	uint16_t loopsInTenMs;

	void init();
	void loop();
	void loop10ms();

	SXExampleConfig configs[CONFIGS_MAX];

	int16_t actualConfig;

	bool tx;

	void setTxConfig(bool tx, uint16_t conf =0 );



};
#endif /* INC_APP_HPP_ */





