/*
 * MAX777751.hpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */

#ifndef IC_LITHIUMBATTERYCHARGERS_MAX777751_HPP_
#define IC_LITHIUMBATTERYCHARGERS_MAX777751_HPP_

#include <Peripheral/GPIO/PIN.hpp>
#include <BasicTypes/IO/Input.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <BasicTypes/ImpulseInput/ImpulseInput.hpp>

class MAX777751{
public:
	enum class State{Error, Buck, Charging, ChargingDone, ChargingDisabled, OTG};

	MAX777751()=default;
	MAX777751(PIN* pinChgInokb, PIN* pinChgStat, PIN* pinChgEnbst, PIN* pinChgItopoff);

	void init();

	void iterate(uint32_t TICK);

	State getState();

	void setOTGState(bool otgEnabled);
	void setCharging(bool charging);



private:

	INPUT_BASIC inokb;
	ImpulseInput stat;
	OUTPUT_ADVENCED enbst;
	OUTPUT_ADVENCED itopoff;

	bool charging;


	bool newcharg;
	uint32_t newchargtime;

	State state;


};


/*
chgInokb = INPUT_BASIC(&pinCHGInokb, INPUT_BASIC::PULL::UP, INPUT_BASIC::LOGIC::REVERSE);
chgStat = ImpulseInput(&pinCHGStat, ImpulseInput::Slope::Both, 1250,  INPUT_BASIC::PULL::UP, INPUT_BASIC::LOGIC::REVERSE);
chgEnbst = OUTPUT_ADVENCED(&pinCHGEnbst, OUTPUT_BASIC::LOGIC::NORMAL, OUTPUT_BASIC::MODE::ODPULLUP);
chgItopoff = OUTPUT_ADVENCED(&pinCHGItopoff, OUTPUT_BASIC::LOGIC::REVERSE, OUTPUT_BASIC::MODE::OD);
*/



#endif /* IC_LITHIUMBATTERYCHARGERS_MAX777751_HPP_ */
