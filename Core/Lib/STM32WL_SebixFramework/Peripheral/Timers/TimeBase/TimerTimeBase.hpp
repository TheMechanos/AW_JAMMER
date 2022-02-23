/*
 * TimerTimeBase.hpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#ifndef PERIPHERAL_TIMERS_TIMEBASE_TIMERTIMEBASE_HPP_
#define PERIPHERAL_TIMERS_TIMEBASE_TIMERTIMEBASE_HPP_

#include <stm32wlxx.h>

class TimerTimeBaseListener{
public:
	virtual void handleTimerIrQn();

	virtual ~TimerTimeBaseListener(){};
};

class TimerTimeBase{
public:
	enum class CounterMode{
		UP= TIM_COUNTERMODE_UP, DOWN= TIM_COUNTERMODE_DOWN
	};
	enum class ClockDivision{
		DIV1 = TIM_CLOCKDIVISION_DIV1, DIV2 = TIM_CLOCKDIVISION_DIV2, DIV4 = TIM_CLOCKDIVISION_DIV4
	};
	enum class AutoReloadPreload{
		ENABLE = TIM_AUTORELOAD_PRELOAD_ENABLE, DISABLE = TIM_AUTORELOAD_PRELOAD_DISABLE
	};

	TimerTimeBase()=default;
	TimerTimeBase(TIM_TypeDef* instance, uint16_t prescaler, uint16_t peroid, CounterMode cmode = CounterMode::UP, ClockDivision cdiv = ClockDivision::DIV1,
			AutoReloadPreload cauto = AutoReloadPreload::ENABLE);

	void configIRQn(IRQn_Type IRQn, uint8_t PreemptPriority, TimerTimeBaseListener* listener);

	void init();

	void setPrescaler(uint16_t prescaler);
	void setPeroid(uint16_t peroid);

	void start();
	void stop();


	void periodElapsed();
	void IRQHandler();


	TIM_HandleTypeDef* getHandler();

private:
	TIM_HandleTypeDef handler;
	IRQn_Type IRQn;
	uint8_t PreemptPriority;
	TimerTimeBaseListener* listener;

};



#endif /* PERIPHERAL_TIMERS_TIMEBASE_TIMERTIMEBASE_HPP_ */
