/*
 * Timer.hpp
 *
 *  Created on: 30.11.2020
 *      Author: SHON
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_


#include <System.hpp>


class Timer{
public:
	Timer()=default;

	Timer(uint32_t timerTime){
		this->timerSetTime = timerTime;
		this->last = 0;
	}

	bool isTimeNoClear(){
		return isTimeNoClear(timerSetTime);
	}

	bool isTimeNoClear(uint32_t timerTime){
		return (System::getTick() - last) >= timerTime;
	}

	void reset(){
		last = System::getTick();
	}

	bool isTime(){
		return isTime(timerSetTime);
	}

	bool isTime(uint32_t timerTime){
		if(isTimeNoClear(timerTime)){
			reset();
			return true;
		}
		return false;
	}

	uint32_t getSetTime(){
		return timerSetTime;
	}

	uint32_t getTimerPercent(){
		uint16_t a = System::getTick() - last;
		return (a*100 / timerSetTime);
	}


private:
	uint32_t last;
	uint32_t timerSetTime;

};



#endif /* TIMER_HPP_ */
