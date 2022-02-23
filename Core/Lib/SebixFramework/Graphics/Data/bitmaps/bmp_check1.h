
/*******************************************************************************
* image
* filename: unsaved
* name: bmp_check1
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



static const uint8_t image_data_bmp_check1[5] = {
    0xfe, 0x1b, 0x6d, 0x87, 0xf0
};
const tImage bmp_check1 = { image_data_bmp_check1, 6, 6 };

