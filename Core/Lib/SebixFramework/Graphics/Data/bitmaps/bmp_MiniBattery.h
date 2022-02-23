
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_MiniBattery.xml
* name: bmp_MiniBattery
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



static const uint8_t image_data_bmp_MiniBattery[7] = {
    0x33, 0xf8, 0x61, 0x86, 0x18, 0x61, 0xfc
};
const tImage bmp_MiniBattery = { image_data_bmp_MiniBattery, 6, 9 };

