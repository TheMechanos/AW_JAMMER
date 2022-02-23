/*
 * LithiumBattery.cpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */

#include "LithiumBattery.hpp"


const uint16_t LithiumBattery::dat[] = { 2606, 2635, 2664, 2692, 2721, 2749, 2778, 2807, 2835, 2864, 2892, 2921, 2950, 2978, 3007, 3035, 3064, 3093, 3121, 3150,
		3178, 3207, 3236, 3264, 3293, 3321, 3350, 3379, 3407, 3436, 3464, 3493, 3522, 3550, 3579, 3607, 3636, 3665, 3693, 3722, 3750, 3779, 3808, 3836, 3865,
		3893, 3922, 3951, 3979, 4008, 4036 };


LithiumBattery::LithiumBattery(ANALOG_INPUT* voltage, ANALOG_INPUT* ntc){
	this->voltage = voltage;
	this->ntc = ntc;
}

uint8_t LithiumBattery::getPercent(){
	//if(voltage==0)return 0;

	uint8_t p=0;
	uint16_t vol = voltage->getValue();

	for(uint8_t q=0;q<51;q++){
		if(vol > LithiumBattery::dat[q])
			p=q*2;
	}
	if(p>100)p=100;


	return p;
}
uint16_t LithiumBattery::getTemperature(){
	if(ntc == 0)return 0;

}
