/*
 * LCD_MONO_GENERIC_128x64.hpp
 *
 *  Created on: 30.07.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_BASE_LCD_MONO_GENERIC_HPP_
#define SEBIXUI_MONO_128X64_BASE_LCD_MONO_GENERIC_HPP_

class GenericMonoLCD{
public:
	GenericMonoLCD(){};
	virtual ~GenericMonoLCD(){};

	virtual bool init()=0;

	virtual void iterate(){};

	virtual void cls(void)=0;
	virtual bool ref(void)=0;
	virtual void setPix(int16_t x, int16_t y, bool state)=0;

	virtual void setContrast(uint8_t cont)=0;
	virtual void setBacklight(bool state)=0;


};


#endif /* SEBIXUI_MONO_128X64_BASE_LCD_MONO_GENERIC_HPP_ */
