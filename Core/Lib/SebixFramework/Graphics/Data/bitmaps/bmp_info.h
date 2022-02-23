
/*******************************************************************************
* image
* filename: C:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_info.xml
* name: bmp_info
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



static const uint8_t image_data_bmp_info[145] = {
    0x00, 0x07, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x0f, 0xe1, 0xfc, 0x00, 0x07, 0xc0, 0x0f, 0x80, 0x03, 0xc0, 0x00, 0xf0, 0x01, 0xc0, 0x00, 0x0e, 0x00, 0xe0, 0x1e, 0x01, 0xc0, 0x70, 0x0f, 0xc0, 0x38, 0x38, 0x03, 0xf0, 0x07, 0x0e, 0x00, 0xfc, 0x01, 0xc7, 0x00, 0x3f, 0x00, 0x39, 0xc0, 0x07, 0x80, 0x0e, 0x60, 0x00, 0x00, 0x01, 0xb8, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7f, 0x80, 0x1f, 0x00, 0x0f, 0xc0, 0x03, 0xc0, 0x03, 0xf0, 0x00, 0xf0, 0x00, 0xfc, 0x00, 0x3c, 0x00, 0x3f, 0x00, 0x0f, 0x80, 0x0f, 0xc0, 0x07, 0xe0, 0x03, 0xf0, 0x01, 0xd8, 0x00, 0xfc, 0x00, 0x67, 0x00, 0x3f, 0x00, 0x39, 0xc0, 0x0f, 0xc0, 0x0e, 0x38, 0x03, 0xf0, 0x07, 0x0e, 0x01, 0xfe, 0x01, 0xc1, 0xc0, 0xff, 0xc0, 0xe0, 0x38, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x38, 0x00, 0xf0, 0x00, 0x3c, 0x00, 0x1f, 0x00, 0x3e, 0x00, 0x03, 0xf8, 0x7f, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00
};
const tImage bmp_info = { image_data_bmp_info, 34, 34 };

