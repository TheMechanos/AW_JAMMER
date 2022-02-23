
/*******************************************************************************
* image
* filename: C:/Users/skocz/OneDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_chess_knight.xml
* name: bmp_chess_knight
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



static const uint8_t image_data_bmp_chess_knight[4] = {
    0x63, 0x9c, 0xcf, 0x80
};
const tImage bmp_chess_knight = { image_data_bmp_chess_knight, 5, 5 };

