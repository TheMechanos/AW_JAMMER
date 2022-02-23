/*
 * Glcd.cpp
 *
 *  Created on: 02.01.2020
 *      Author: SHON
 */

#include <Displays/MONO/WDO0066/WDO0066.hpp>

WDO0066::WDO0066(SPI* spi, PIN * sig_a0, PIN * sig_cs, PIN * sig_rst, OUTPUT_BASIC * pin_backlight){
	this->sig_cs=OUTPUT_PIN(sig_cs);
	this->sig_a0=OUTPUT_PIN(sig_a0);
	this->sig_rst=OUTPUT_PIN(sig_rst);
	this->backlight=pin_backlight;
	this->dirty_page=0xFF;
	sendingBlock=-1;
	this->spi=spi;
	busyDMAtransmit=false;
	this->lastRef = 0;
}

bool WDO0066::init(){
	sig_a0.init();
	sig_cs.init();
	sig_rst.init();
	if(backlight)backlight->init();

	spi->getTxDMA()->configDirectionAlignment(DMA::Direction::MEM_TO_PERIPH, DMA::Mode::NORMAL, false, true, DMA::PeriphAlign::BYTE, DMA::MemAlign::BYTE);
	spi->getSPIHandler()->Init.Direction = SPI_DIRECTION_1LINE;
	spi->init();
	spi->registerListener(this);

	sig_rst.OFF();
	HAL_Delay(200);
	sig_rst.ON();
	HAL_Delay(2);
	sig_cs.OFF();

	sendCommand(ST7565_CMD_SET_BIAS_9);
	sendCommand(ST7565_CMD_SET_ADC_REVERSE);
	sendCommand(ST7565_CMD_SET_COM_NORMAL);
	
	sendCommand(ST7565_CMD_SET_RESISTOR_RATIO | 0x06);
	setContrast(ST7565_DEFAULT_CONTRAST);
		
	sendCommand(ST7565_CMD_SET_POWER_CONTROL | ST7565_BIT_POWER_BOSTER | ST7565_BIT_POWER_VREG | ST7565_BIT_POWER_VFOLL);
	
	sendCommand(ST7565_CMD_DISPLAY_ON);
	
	
	cls();
	ref();
	HAL_Delay(100);
	ref();

	return true;
}


void WDO0066::iterate(){
	if(System::getTick() - lastTransmitStart > 500 && busyDMAtransmit){
		busyDMAtransmit=false;
	}

}

void WDO0066::setContrast(uint8_t cont){
	if(cont > 63)cont = 63;
	sendCommand(ST7565_CMD_SET_VOLUME_FIRST);
	sendCommand(ST7565_CMD_SET_VOLUME_SECOND | (cont & 0x3F));
}

void WDO0066::setBacklight(bool state){
	if(backlight){
		backlight->set(state);
	}
}


void WDO0066::cls(void){
	for (int q = 0; q < 1024; q++)
		glcd_buffer[q] = 0;
	dirty_page = 0xFF;
}

bool WDO0066::ref(void){
	if(busyDMAtransmit)return false;

	lastTransmitStart = System::getTick();
	busyDMAtransmit = true;
	copyBuffer();
	uint8_t idx = 0;
	for(uint8_t page = 0; page < 8; page++){
		if(dirty_page_send & (1 << page)){
			DataBlocktoSend[idx].makeCommand(3, 0xB0 | page, 0x00, 0x10);
			idx++;

			DataBlocktoSend[idx].makeData(128, glcd_buffer_send + (page * 128));
			idx++;

		}
	}
	DataBlocktoSend[idx].makeCommand(1, ST7565_CMD_DISPLAY_ON);
	idx++;
	DataBlocktoSend[idx].makeEmpty();
	idx++;
	DataBlocktoSend[idx].makeEmpty();

	sendingBlock = 0;
	sendDMABlock(&DataBlocktoSend[0]);
	///sendingBlock++;

	return true;
}

void WDO0066::copyBuffer(){
	memcpy(glcd_buffer_send, glcd_buffer, 1024);
	dirty_page_send = dirty_page;
	dirty_page=0x00;
}




void WDO0066::sendDMABlock(SPI_DATA_BLOCK * block){
	sig_cs.OFF();
	if(block->isCommand())sig_a0.OFF();
	spi->transmitDMA(block->getBytes(), block->getSize());
}
void WDO0066::setPix(int16_t x, int16_t y, bool state){
	if(x >= 128 || y >= 64 || x<0 || y<0)
		return;
	if(state)
		glcd_buffer[((y / 8) * 128) + x] |= (1 << (y % 8));
	else
		glcd_buffer[((y / 8) * 128) + x] &= ~(1 << (y % 8));

	dirty_page |= (1 << (y / 8));
}



void WDO0066::setReverse(int16_t a){
	if(a)sendCommand(ST7565_CMD_SET_DISP_REVERSE);
	else sendCommand(ST7565_CMD_SET_DISP_NORMAL);
}

void WDO0066::sendCommand(uint8_t command){
	sig_a0.OFF();
	sig_cs.OFF();
	spi->transmit(&command, 1, HAL_MAX_DELAY);
	sig_cs.ON();
	sig_a0.ON();
}

void WDO0066::sendData(uint8_t *buffer, int size){
	sig_cs.OFF();
	spi->transmit(buffer, size, HAL_MAX_DELAY);//HAL_SPI_Transmit_DMA(&SPI_Handle, buffer, size);
	sig_cs.ON();
}

void WDO0066::onDMATxCmplt(){
	sig_a0.ON();
	sig_cs.ON();
	if(!DataBlocktoSend[sendingBlock].isEmpty()){
		sendDMABlock(&DataBlocktoSend[sendingBlock]);
	}else{
		busyDMAtransmit=false;
	}
	sendingBlock++;
}





SPI_DATA_BLOCK::SPI_DATA_BLOCK(){
	this->datawsk=0;
	this->size=0;
	this->Command=false;
	this->empty=true;
}

void SPI_DATA_BLOCK::makeData(uint16_t size, uint8_t* wsk){
	Command=false;
	empty=false;
	this->size=size;
	this->datawsk=wsk;
}
void SPI_DATA_BLOCK::makeCommand(uint16_t size, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4, uint8_t c5){
	Command=true;
	empty=false;

	this->size=size;
	this->command[0]=c1;
	this->command[1]=c2;
	this->command[2]=c3;
	this->command[3]=c4;
	this->command[4]=c5;
}

bool SPI_DATA_BLOCK::isCommand(){
	return Command;
}
uint8_t* SPI_DATA_BLOCK::getBytes(){
	if(isCommand())return command;
	else return datawsk;
}
uint16_t SPI_DATA_BLOCK::getSize(){
	return size;
}
bool SPI_DATA_BLOCK::isEmpty(){
	return empty;
}
void SPI_DATA_BLOCK::makeEmpty(){
	empty=true;
}





