
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_OTG.xml
* name: bmp_OTG
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



static const uint8_t image_data_bmp_OTG[7] = {
    0x79, 0x24, 0xbf, 0x86, 0x18, 0x5e, 0x30
};
const tImage bmp_OTG = { image_data_bmp_OTG, 6, 9 };

