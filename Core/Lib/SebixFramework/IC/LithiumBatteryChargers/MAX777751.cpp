
/*
 * MAX777751.cpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */
#include "MAX777751.hpp"




MAX777751::MAX777751(PIN* pinChgInokb, PIN* pinChgStat, PIN* pinChgEnbst, PIN* pinChgItopoff){
	inokb = INPUT_BASIC(pinChgInokb, INPUT_BASIC::PULL::UP, INPUT_BASIC::LOGIC::REVERSE);
	stat = ImpulseInput(pinChgStat, ImpulseInput::Slope::Both, 1250,  INPUT_BASIC::PULL::UP, INPUT_BASIC::LOGIC::REVERSE);
	enbst = OUTPUT_ADVENCED(pinChgEnbst, OUTPUT_BASIC::LOGIC::NORMAL, OUTPUT_BASIC::MODE::ODPULLUP);
	itopoff = OUTPUT_ADVENCED(pinChgItopoff, OUTPUT_BASIC::LOGIC::REVERSE, OUTPUT_BASIC::MODE::OD);

	charging=true;

	state = State::Error;
}

void MAX777751::init(){
	inokb.init();
	stat.init();
	enbst.init();
	itopoff.init();

}

void MAX777751::iterate(uint32_t TICK){
	stat.iterate(TICK);
	enbst.iterate(TICK);
	itopoff.iterate(TICK);

	state = State::Error;
	if(enbst.get() == true){
		state = State::OTG;

	}else{
		if(charging == false){
			state = State::ChargingDisabled;

		}else{
			if(inokb.get() == true){
				if(newcharg == true){
					 state = State::Charging;

					 if(TICK - newchargtime > 2000)newcharg=false;

				}else{
					uint16_t impulses = stat.getImpulsesPerMs(10000);
					if(impulses > 15 && impulses < 25){
						state = State::Charging;
					}else{
						state = State::ChargingDone;
					}
				}
			}else{
				newcharg = true;
				newchargtime = TICK;

				state = State::Buck;
			}

		}

	}


}

MAX777751::State MAX777751::getState(){
	return state;
}

void MAX777751::setOTGState(bool otgEnabled){
	if(otgEnabled == true && state == State::Buck){
		enbst.ON();
	}else{
		enbst.OFF();
	}
}

void MAX777751::setCharging(bool charging){
	this->charging = charging;
	itopoff.set(!charging);
}
