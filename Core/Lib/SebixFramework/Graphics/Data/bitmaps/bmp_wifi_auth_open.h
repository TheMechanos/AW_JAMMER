
/*******************************************************************************
* image
* filename: C:/Users/skocz/OneDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_wifi_auth_open.xml
* name: bmp_wifi_auth_open
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



static const uint8_t image_data_bmp_wifi_auth_open[7] = {
    0x38, 0x89, 0x10, 0x2f, 0xfd, 0xfb, 0xbe
};
const tImage bmp_wifi_auth_open = { image_data_bmp_wifi_auth_open, 7, 8 };

