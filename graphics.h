#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

#ifndef __CONTEXT__
#define __CONTEXT__
extern Graphics_Context g_sContext;
#endif

#define LCD_SIZE    128

#define MIN_RANGE   1           // min margin is 0+1
#define MAX_RANGE   31          // max margin is 128/RATIO-1
#define RATIO       4           // 1:4, 1 node = 4 pixels


void _graphics_drawNode(uint8_t x, uint8_t y);


#endif
