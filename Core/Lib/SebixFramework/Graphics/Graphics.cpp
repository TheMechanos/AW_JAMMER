/*
 * Graphics.cpp
 *
 *  Created on: 13.12.2020
 *      Author: SHON
 */

#include "Graphics.hpp"


GraphicsMono::GraphicsMono(GenericMonoLCD * display){
	this->disp = display;
}

void GraphicsMono::cls(void){
	disp->cls();
}

bool GraphicsMono::ref(void){
	return disp->ref();
}


void GraphicsMono::drawText(int16_t x, int16_t y, const char * string, const tFont font, Text params, Orientation orient){
	drawText(x, y, (char*) string, font, params, orient);
}

void GraphicsMono::drawText(int16_t x, int16_t y, char * string, const tFont font, Text params, Orientation orient){
	char znak;
	int posX=x;
	int posY=y;


	while ((znak = *(string++))){
		uint16_t chnr=0;
		if(znak<32 || znak>126){ //ZNAK POZA STANDARD ASCII
			bool finded=false;
			for(uint16_t q=0;q<font.length;q++){
				if(font.chars[q].code == znak){
					chnr=q;
					finded=true;
					break;
				}
			}
			if (!finded) {
				for (uint16_t q = 0; q < font.length; q++) {
					long int newZnak = (znak<<8) | (*(string));
					if (font.chars[q].code == newZnak) {
						chnr = q;
						string++;
						break;
					}
				}
			}


		}else{//ZNAK STANDARD ASCII
			chnr= znak-32;
		}
		tImage a= *(font.chars[chnr].image);


		if(orient == Orientation::NORMAL){
			if(znak == '\n'){
				if(params == Text::NO_LEW_LINE)
					continue;
				posX = x;
				posY += a.height + 1;
				continue;
			}
			if((posX + a.width) > 128 && params == Text::FOLD){
				posX = x;
				posY += a.height + 1;
			}

		}else if(orient == Orientation::RIGHT_ROTATED){
			if(znak == '\n'){
				if(params == Text::NO_LEW_LINE)
					continue;
				posX -= a.height - 1;
				posY = y;
				continue;
			}
			if((posY + a.width) > 64 && params == Text::FOLD){
				posY = y;
				posX -= a.height -1;
			}

		}else if(orient == Orientation::LEFT_ROTATED){
			if(znak == '\n'){
				if(params == Text::NO_LEW_LINE)
					continue;
				posX += a.height - 1;
				posY = y;
				continue;
			}
			if((posY + a.width) < 0 && params == Text::FOLD){
				posY = y;
				posX += a.height -1;
			}

		}else if(orient == Orientation::UPSIDE_DOWN){
			if(znak == '\n'){
				if(params == Text::NO_LEW_LINE)
					continue;
				posX = x;
				posY -= a.height + 1;
				continue;
			}
			if((posX + a.width) > 128 && params == Text::FOLD){
				posX = x;
				posY -= a.height + 1;
			}

		}



		if(params == Text::CLS)
			drawBitmap(posX, posY, a, Bitmap::CLS, orient);
		else
			drawBitmap(posX, posY, a, Bitmap::NONE, orient);



		if(orient == Orientation::NORMAL){
			posX += font.chars[chnr].image->width + 1;
		}else if(orient == Orientation::RIGHT_ROTATED){
			posY += font.chars[chnr].image->width + 1;
		}else if(orient == Orientation::LEFT_ROTATED){
			posY -= font.chars[chnr].image->width + 1;
		}else if(orient == Orientation::UPSIDE_DOWN){
			posX -= font.chars[chnr].image->width + 1;
		}

	}

}


void GraphicsMono::drawBitmap(int16_t x, int16_t y, const tImage &bitmap, Bitmap params, Orientation orient){

	if(params == Bitmap::CLS)
		clsRectAbs(x, y, x + bitmap.width - 1, y + bitmap.height - 1);

	int current_pixel = 0;
	if(orient == Orientation::NORMAL){
		for(int posY = y; posY < (y + bitmap.height); posY++){
			for(int posX = x; posX < (x + bitmap.width); posX++){
				uint8_t pixbyte = bitmap.data[current_pixel / 8];
				bool pix = pixbyte & (1 << (7 - (current_pixel % 8)));

				if(pix)
					disp->setPix(posX, posY, 1);
				current_pixel++;
			}
		}
	}else if(orient == Orientation::RIGHT_ROTATED){
		for(int posY = 0; posY < bitmap.height; posY++){
			for(int posX = 0; posX < bitmap.width; posX++){

				uint8_t pixbyte = bitmap.data[current_pixel / 8];
				bool pix = pixbyte & (1 << (7 - (current_pixel % 8)));

				if(pix)
					disp->setPix(x + bitmap.height - 1 - posY, y + posX, 1);
				current_pixel++;
			}
		}
	}else if(orient == Orientation::LEFT_ROTATED){
		for(int posY = 0; posY < bitmap.height; posY++){
			for(int posX = 0; posX < bitmap.width; posX++){
				uint8_t pixbyte = bitmap.data[current_pixel / 8];
				bool pix = pixbyte & (1 << (7 - (current_pixel % 8)));

				if(pix)
					disp->setPix(x + posY, y + bitmap.height -1-posX, 1);
				current_pixel++;
			}
		}
	}else if(orient == Orientation::UPSIDE_DOWN){
		for(int posY = y; posY < (y + bitmap.height); posY++){
			for(int posX = x; posX < (x + bitmap.width); posX++){
				uint8_t pixbyte = bitmap.data[current_pixel / 8];
				bool pix = pixbyte & (1 << (7 - (current_pixel % 8)));

				if(pix)
					disp->setPix((bitmap.width - (posX - x)) + x, (bitmap.width - (posY - y)) + y, 1);
				current_pixel++;
			}
		}
	}
}

void GraphicsMono::drawRectAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
	for (uint8_t xx = x1; xx <= x2; xx++){
		for (uint8_t yy = y1; yy <= y2; yy++){
			disp->setPix(xx, yy, 1);
		}
	}
}
void GraphicsMono::drawFrameAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
	drawRectAbs(x1, y1, x2, y1);
	drawRectAbs(x1, y2, x2, y2);

	drawRectAbs(x1, y1, x1, y2);
	drawRectAbs(x2, y1, x2, y2);
}

void GraphicsMono::clsRectAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
	for (uint8_t xx = x1; xx <= x2; xx++){
		for (uint8_t yy = y1; yy <= y2; yy++){
			disp->setPix(xx, yy, false);
		}
	}
}


void GraphicsMono::clsRect(int16_t x, int16_t y, int16_t width, int16_t height){
	clsRectAbs(x, y, x+width, y+height);
}
void GraphicsMono::drawRect(int16_t x, int16_t y, int16_t width, int16_t height){
	drawRectAbs(x, y, x+width-1, y+height-1);
}
void GraphicsMono::drawFrame(int16_t x, int16_t y, int16_t width, int16_t height){
	drawFrameAbs(x, y, x+width, y+height);
}

void GraphicsMono::drawProgressBar(int16_t x, int16_t y, int16_t width, int16_t height, uint8_t percent){
	if(height<5)return;
	if(width<10)return;

	drawFrame(x, y, width, height-1);

	if(percent>100 || percent == 0)return;

	uint8_t insideWidth = percent * (width- 4) /100;

	drawRect(x+2, y+2, insideWidth+1, height-4);
}

