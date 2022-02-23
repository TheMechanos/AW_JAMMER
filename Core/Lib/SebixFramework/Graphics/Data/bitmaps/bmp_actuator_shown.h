
/*******************************************************************************
* image
* filename: D:/ShonDrive/PROJEKTY/PROGRAMY_STM/.LIBS/Graphics/Images/saves/actuator_shown.xml
* name: actuator_shown
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



static const uint8_t image_data_actuator_shown[7] = {
    0xfc, 0x10, 0x86, 0x1f, 0xc2, 0x1f, 0xc0
};
const tImage bmp_actuator_shown = { image_data_actuator_shown, 11, 5 };

