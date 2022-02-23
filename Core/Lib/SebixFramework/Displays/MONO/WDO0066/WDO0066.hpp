/*
 * Glcd.hpp
 *
 *  Created on: 02.01.2020
 *      Author: SHON
 */

#ifndef SEBIXFRAMEWORK_GLCD_COG_GLCD_HPP_
#define SEBIXFRAMEWORK_GLCD_COG_GLCD_HPP_

#include <string.h>

#include <BasicTypes/IO/Output.hpp>
#include <Peripheral/GPIO/PIN.hpp>
#include <Peripheral/DMA/DMA.hpp>
#include <Interfaces/SPI/SPI.hpp>

#include <System.hpp>

#include <Displays/MONO/GenericMono.hpp>


#define ST7565_CMD_DISPLAY_OFF   0xAE
#define ST7565_CMD_DISPLAY_ON    0xAF

#define ST7565_CMD_SET_DISP_START_LINE  0x40
#define ST7565_CMD_SET_PAGE  0xB0

#define ST7565_CMD_SET_COLUMN_UPPER  0x10
#define ST7565_CMD_SET_COLUMN_LOWER  0x00

#define ST7565_CMD_SET_ADC_NORMAL  0xA0
#define ST7565_CMD_SET_ADC_REVERSE 0xA1

#define ST7565_CMD_SET_DISP_NORMAL 0xA6
#define ST7565_CMD_SET_DISP_REVERSE 0xA7

#define ST7565_CMD_SET_ALLPTS_NORMAL 0xA4
#define ST7565_CMD_SET_ALLPTS_ON  0xA5
#define ST7565_CMD_SET_BIAS_9 0xA2 
#define ST7565_CMD_SET_BIAS_7 0xA3

#define ST7565_CMD_RMW  0xE0
#define ST7565_CMD_RMW_CLEAR 0xEE
#define ST7565_CMD_INTERNAL_RESET  0xE2
#define ST7565_CMD_SET_COM_NORMAL  0xC0
#define ST7565_CMD_SET_COM_REVERSE  0xC8

#define ST7565_CMD_SET_POWER_CONTROL  0x28
#define ST7565_BIT_POWER_BOSTER (1<<2)
#define ST7565_BIT_POWER_VREG   (1<<1)
#define ST7565_BIT_POWER_VFOLL  (1<<0)

#define ST7565_CMD_SET_RESISTOR_RATIO  0x20
#define ST7565_CMD_SET_VOLUME_FIRST  0x81
#define ST7565_CMD_SET_VOLUME_SECOND  0
#define ST7565_CMD_SET_STATIC_OFF  0xAC
#define ST7565_CMD_SET_STATIC_ON  0xAD
#define ST7565_CMD_SET_STATIC_REG  0x0
#define ST7565_CMD_SET_BOOSTER_FIRST  0xF8
#define ST7565_CMD_SET_BOOSTER_234  0
#define ST7565_CMD_SET_BOOSTER_5  1
#define ST7565_CMD_SET_BOOSTER_6  3
#define ST7565_CMD_NOP  0xE3
#define ST7565_CMD_TEST  0xF0

#define ST7565_DEFAULT_CONTRAST 20


class SPI_DATA_BLOCK{
public:
	SPI_DATA_BLOCK();

	void makeData(uint16_t size, uint8_t* wsk);
	void makeCommand(uint16_t size, uint8_t c1, uint8_t c2=0, uint8_t c3=0, uint8_t c4=0, uint8_t c5=0);

	bool isCommand();
	uint8_t* getBytes();
	uint16_t getSize();
	bool isEmpty();
	void makeEmpty();

private:
	uint16_t size;
	uint8_t * datawsk;
	uint8_t command[5];
	bool Command;
	bool empty;

};

class WDO0066 : public GenericMonoLCD , private SPI_EventListener{
public:
	WDO0066()=default;
	WDO0066(SPI* spi, PIN * pin_a0, PIN * pin_cs, PIN * pin_rst, OUTPUT_BASIC * pin_backlight);

	bool init();

	void iterate();

	void cls(void);
	bool ref(void);
	void setPix(int16_t x, int16_t y, bool state);

	void setContrast(uint8_t cont);

	void setReverse(int16_t a);
	void log(const char* msg, int del);

	void setBacklight(bool state);

private:
	SPI* spi;

	OUTPUT_PIN sig_a0;
	OUTPUT_PIN sig_cs;
	OUTPUT_PIN sig_rst;
	OUTPUT_BASIC* backlight;

	volatile bool busyDMAtransmit;
	volatile uint32_t lastTransmitStart;
	uint32_t lastRef;
	static const uint32_t MIN_REFRESH_ITERVAL = 10;


	uint8_t glcd_buffer_send[1024];
	uint8_t glcd_buffer[1024];
	volatile uint8_t dirty_page_send;
	volatile uint8_t dirty_page;

	void copyBuffer();

	void sendCommand(uint8_t command);
	void sendData(uint8_t *buffer, int size);

	void sendPageNormal(uint8_t page);
	void refNormal();
	void refDMA();

	int8_t sendingBlock;
	SPI_DATA_BLOCK DataBlocktoSend[32];
	void sendDMABlock(SPI_DATA_BLOCK * block);

	static const uint8_t MIN_DELAY_BEFORE_RESEND=1;

	void onDMATxCmplt();


};



#endif /* SEBIXFRAMEWORK_GLCD_COG_GLCD_HPP_ */
