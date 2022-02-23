/*
 * ImpulseInput.hpp
 *
 *  Created on: 3 kwi 2021
 *      Author: SHON
 */

#ifndef BASICTYPES_IMPULSEINPUT_IMPULSEINPUT_HPP_
#define BASICTYPES_IMPULSEINPUT_IMPULSEINPUT_HPP_

#include <BasicTypes/IO/Input.hpp>


class ImpulseInput : public INPUT_BASIC{
public:
	enum class Slope{Both, Rising, Falling};
	ImpulseInput()=default;
	ImpulseInput(PIN * pin, Slope slope, uint32_t samplingTime,PULL pinpull=PULL::NO, LOGIC logic=LOGIC::NORMAL);

	void init();

	void iterate(uint32_t TICK);

	uint32_t getImpulses();
	uint32_t getSampligTime();

	uint32_t getImpulsesPerMs(uint32_t ms);


private:
	INPUT_BASIC* input;
	uint32_t samplingTime;
	bool lastState;

	uint32_t lastImpulses;
	uint32_t impulses;
	uint32_t startingTime;

	Slope slope;

};




#endif /* BASICTYPES_IMPULSEINPUT_IMPULSEINPUT_HPP_ */
