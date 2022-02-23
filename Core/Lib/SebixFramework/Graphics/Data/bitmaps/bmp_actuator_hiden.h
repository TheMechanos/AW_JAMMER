
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/actuator_hiden.xml
* name: actuator_hiden
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



static const uint8_t image_data_actuator_hiden[5] = {
    0xfc, 0x85, 0x87, 0x85, 0xfc
};
const tImage bmp_actuator_hiden = { image_data_actuator_hiden, 8, 5 };

