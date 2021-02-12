#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "field.h"

#define LCD_SIZE 128


void graphics_loadField(Graphics_Context *g_sContext, uint8_t **field);


#endif
