/*
 * TimerPWM.hpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#ifndef PERIPHERAL_TIMERS_PWM_TIMERPWM_HPP_
#define PERIPHERAL_TIMERS_PWM_TIMERPWM_HPP_

#include <stm32wlxx.h>
#include "Peripheral/GPIO/PIN.hpp"

class TimerPWM{
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

	TimerPWM()=default;
	TimerPWM(TIM_TypeDef* instance, uint16_t prescaler, uint16_t peroid, CounterMode cmode = CounterMode::UP, ClockDivision cdiv = ClockDivision::DIV1,
			AutoReloadPreload cauto = AutoReloadPreload::ENABLE);

	void init();

	void setPrescaler(uint16_t prescaler);
	void setPeroid(uint16_t peroid);

	uint16_t getPeroid();


	TIM_HandleTypeDef* getHandler();

private:
	TIM_HandleTypeDef handler;

};


class TimerPWMChannel{
public:
	enum class Mode {
		NORMAL = TIM_OCMODE_PWM1, REVERSED = TIM_OCMODE_PWM2
	};
	enum class Channel{
		CH1 = TIM_CHANNEL_1, CH2 = TIM_CHANNEL_2, CH3 = TIM_CHANNEL_3, CH4 = TIM_CHANNEL_4
	};
	TimerPWMChannel()=default;
	TimerPWMChannel(TimerPWM* timer, PIN* pin, Channel channel, Mode mode=Mode::NORMAL);

	void init();

	void set(uint16_t val);
	void setPercent(uint8_t percent);
	uint16_t get();

	void enable();
	void disable();

	TimerPWM* getTimer();

	TIM_OC_InitTypeDef* getInitStructure();


private:
	TIM_OC_InitTypeDef initStructure;
	PIN* pin;
	TimerPWM* timer;
	Channel channel;
	Mode mode;

};





#endif /* PERIPHERAL_TIMERS_PWM_TIMERPWM_HPP_ */
