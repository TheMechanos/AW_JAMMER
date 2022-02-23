/*
 * RFRadioSwitch.hpp
 *
 *  Created on: 10 gru 2021
 *      Author: user
 */

#ifndef SRC_SX1262_RADIORFSWITCH_HPP_
#define SRC_SX1262_RADIORFSWITCH_HPP_


#include <Generic/GenericIO.hpp>

class RadioRFSwitch{
public:
	enum class Mode{
		OFF, Tx, Rx
	};
	RadioRFSwitch()=default;

	RadioRFSwitch(OUTPUT* pinTx, OUTPUT* pinRx){
		this->pinTx = pinTx;
		this->pinRx = pinRx;
	}

	void init(){

	}

	void set(Mode mode){
		switch(mode){
		case Mode::OFF:
			pinTx->set(false);
			pinRx->set(false);
			break;
		case Mode::Rx:
			pinTx->set(false);
			pinRx->set(true);
			break;
		case Mode::Tx:
			pinTx->set(true);
			pinRx->set(false);
		}
	}

private:
	OUTPUT* pinTx;
	OUTPUT* pinRx;

};



#endif /* SRC_SX1262_RADIORFSWITCH_HPP_ */
