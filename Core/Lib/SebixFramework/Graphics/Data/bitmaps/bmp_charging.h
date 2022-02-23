
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_charging.xml
* name: bmp_charging
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



static const uint8_t image_data_bmp_charging[6] = {
    0x52, 0xbf, 0xf7, 0x10, 0x84, 0x20
};
const tImage bmp_charging = { image_data_bmp_charging, 5, 9 };

