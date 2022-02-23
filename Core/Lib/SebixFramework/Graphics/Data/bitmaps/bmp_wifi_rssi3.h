
/*******************************************************************************
* image
* filename: C:/Users/skocz/OneDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/bmp_wifi_rssi3.xml
* name: bmp_wifi_rssi3
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



static const uint8_t image_data_bmp_wifi_rssi3[7] = {
    0x03, 0x03, 0x03, 0x1b, 0x1b, 0x1b, 0xdb
};
const tImage bmp_wifi_rssi3 = { image_data_bmp_wifi_rssi3, 8, 7 };

