/*
 * Graphics.hpp
 *
 *  Created on: 13.12.2020
 *      Author: SHON
 */

#ifndef GRAPHICS_GRAPHICS_HPP_
#define GRAPHICS_GRAPHICS_HPP_

#include <stdint.h>
#include <Displays/MONO/GenericMono.hpp>
#include <Graphics/Data/ImageFontTypes.hpp>

#include <Graphics/Data/ImageFontTypes.hpp>
#include <Graphics/Data/bitmaps/bmp_check0.h>
#include <Graphics/Data/bitmaps/bmp_check1.h>
#include <Graphics/Data/bitmaps/bmp_cross.h>
#include <Graphics/Data/bitmaps/bmp_info.h>
#include <Graphics/Data/bitmaps/bmp_wska.h>
#include <Graphics/Data/bitmaps/bmp_wska_square.h>

#include <Graphics/Data/fonts/font_10pix.h>
#include <Graphics/Data/fonts/font_11pix_BOLD.h>
#include <Graphics/Data/fonts/font_15pix_BOLD.h>
#include <Graphics/Data/fonts/font_5pix.h>
#include <Graphics/Data/fonts/font_8pix.h>

class GraphicsMono{
public:

	GraphicsMono(GenericMonoLCD * display);

	enum class Text{
		NONE = 0,
		FOLD = 1<<1,
		REVERSE = 1<<2,
		NO_LEW_LINE = 1<<3,
		CLS = 1<<4
	};
	enum class Bitmap{
		NONE = 0,
		CLS= 1<<1
	};
	enum class Orientation{
		NORMAL,
		RIGHT_ROTATED,
		LEFT_ROTATED,
		UPSIDE_DOWN,

	};

	void cls(void);
	bool ref();


	void drawBitmap(int16_t x, int16_t y, const tImage & bitmap, Bitmap params = Bitmap::NONE, Orientation orient = Orientation::NORMAL);
	void drawText(int16_t x, int16_t y, char * string, const tFont font, Text PARAMS = Text::NONE, Orientation orient = Orientation::NORMAL);
	void drawText(int16_t x, int16_t y, const char * string, const tFont font, Text PARAMS = Text::NONE, Orientation orient = Orientation::NORMAL);
	//void drawTextc(int16_t x, int16_t y, const char * string, const tFont font, Text PARAMS = Text::NONE, Orientation orient = Orientation::NORMAL);


	void clsRect(int16_t x, int16_t y, int16_t width, int16_t height);
	void clsRectAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void drawRect(int16_t x, int16_t y, int16_t width, int16_t height);
	void drawRectAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void drawFrame(int16_t x, int16_t y, int16_t width, int16_t height);
	void drawFrameAbs(int16_t x1, int16_t y1, int16_t x2, int16_t y2);



	void drawProgressBar(int16_t x, int16_t y, int16_t width, int16_t height, uint8_t percent);

private:
	GenericMonoLCD * disp;

};


#endif /* GRAPHICS_GRAPHICS_HPP_ */
