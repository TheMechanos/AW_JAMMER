/*
 * ImageFontTypes.hpp
 *
 *  Created on: 16.03.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_BASE_IMAGEFONTTYPES_HPP_
#define SEBIXUI_MONO_128X64_BASE_IMAGEFONTTYPES_HPP_


typedef struct {
	const uint8_t *data;
	uint16_t width;
	uint16_t height;
} tImage;

typedef struct {
	long int code;
	const tImage *image;
} tChar;

typedef struct {
	int length;
	const tChar *chars;
} tFont;



#endif /* SEBIXUI_MONO_128X64_BASE_IMAGEFONTTYPES_HPP_ */
