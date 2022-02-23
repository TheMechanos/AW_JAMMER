
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_logoChess.xml
* name: bmp_logoChess
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



static const uint8_t image_data_bmp_logoChess[450] = {
    0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x07, 0x0f, 0x07, 0x87, 0x01, 0xff, 0xff, 0x80, 0x70, 0xf0, 0x78, 0x70, 0x1f, 0xf0, 0x38, 0x07, 0x0f, 0x07, 0x87, 0x01, 0xc0, 0x03, 0x80, 0x70, 0xf0, 0x78, 0x70, 0x1c, 0x00, 0x38, 0x07, 0x0f, 0x07, 0x87, 0x01, 0xc0, 0x03, 0x80, 0x7f, 0xff, 0xff, 0xf0, 0x1c, 0x00, 0x38, 0x03, 0xff, 0xff, 0xfe, 0x01, 0xc0, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x38, 0x01, 0xff, 0xff, 0xfc, 0x01, 0xc0, 0x03, 0x80, 0x3f, 0xff, 0xff, 0xe0, 0x1c, 0x00, 0x38, 0x03, 0xff, 0xff, 0xfe, 0x01, 0xc0, 0x03, 0x80, 0x1f, 0xff, 0xff, 0xc0, 0x1c, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xf0, 0x01, 0xff, 0x03, 0x80, 0x07, 0xff, 0xff, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x7f, 0xff, 0xf0, 0x01, 0xc0, 0x03, 0x80, 0x07, 0xff, 0xff, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x7f, 0xff, 0xf0, 0x01, 0xc0, 0xff, 0x80, 0x07, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xf0, 0x01, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0x80, 0x1f, 0xf0, 0x38, 0x00, 0xff, 0xff, 0xf8, 0x01, 0xc0, 0x03, 0x80, 0x0f, 0xff, 0xff, 0x80, 0x1c, 0x00, 0x38, 0x00, 0xff, 0xff, 0xf8, 0x01, 0xc0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x0f, 0xf8, 0x07, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0x81, 0xff, 0x03, 0x80, 0x7f, 0xff, 0xff, 0xf0, 0x1c, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x03, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x1c, 0x00, 0x38, 0x7f, 0xff, 0xff, 0xff, 0xf1, 0xc0, 0x03, 0x87, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x0f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x38, 0x70, 0xe1, 0xc1, 0xc0, 0x00, 0x03, 0x83, 0x87, 0x0e, 0x1c, 0x1c, 0x00
};
const tImage bmp_logoChess = { image_data_bmp_logoChess, 60, 60 };

