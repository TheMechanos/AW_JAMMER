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
	this->lastLoopTick = 0;
	this->loopsInTenMs = 0;
}

void App::run(){
	init();
	while(1){
		loopsInTenMs++;
		loop();

		if(lastLoopTick < System::getTick() - 10){
			loop10ms();
			System::setLoopsInTenMs(loopsInTenMs);
			loopsInTenMs = 0;
			lastLoopTick = System::getTick();
		}
	}

}

void App::init(){
	dev->init();

	configs[0].frequency = 433920000;
	configs[1].frequency = 868350000;
	configs[3].frequency = 868350000;

	actualConfig = 0;

	tx = false;

	setTxConfig(tx, actualConfig);

}

void App::setTxConfig(bool tx, uint16_t conf){
	if(tx){
		dev->sxRadio.setRx();
		dev->sxRadio.config(&configs[conf]);
		dev->sxRadio.setModeTxContinousWave();
	}else{
		dev->sxRadio.setRx();
	}

	//SET CONFIG IN LED
	for (uint8_t q = 0; q < 3; q++){
		if(q == actualConfig){
			dev->led[q].ON();
		}else{
			dev->led[q].OFF();
		}
	}
}

void App::loop(){

	if(tx){
		if((dev->button[0].isPressed() || dev->button[1].isPressed() || dev->button[2].isPressed())){
			tx = false;
			setTxConfig(tx, actualConfig);
		}

	}else{
		if(dev->button[1].isPressed()){
			tx = true;
			setTxConfig(tx, actualConfig);

			for (uint8_t q = 0; q < 3; q++){
				dev->led[q].OFF();
			}

			dev->led[2].blink(120, 240);
			HAL_Delay(80);
			dev->led[1].blink(120, 240);
			HAL_Delay(80);
			dev->led[0].blink(120, 240);

		}

		if(dev->button[2].isPressed()){
			actualConfig++;
			if(actualConfig >= CONFIGS_MAX){
				actualConfig = CONFIGS_MAX - 1;
			}

			setTxConfig(tx, actualConfig);

		}

		if(dev->button[0].isPressed()){
			actualConfig--;
			if(actualConfig < 0){
				actualConfig = 0;
			}

			setTxConfig(tx, actualConfig);
		}

	}

}

void App::loop10ms(){
	dev->iterateNonCritical();
}

