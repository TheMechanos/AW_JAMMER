
/*******************************************************************************
* image
* filename: C:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_wska_square.xml
* name: bmp_wska_square
*
* preset name: Monochrome_COG
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Diffuse Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: yes
*******************************************************************************/
#pragma once
/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_bmp_wska_square[5] = {
    0x00, 0x03, 0x0c, 0x00, 0x00
};
const tImage bmp_wska_square = { image_data_bmp_wska_square, 6, 6 };

