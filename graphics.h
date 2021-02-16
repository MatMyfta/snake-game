#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "snake.h"
#include "apple.h"

extern uint8_t highscore;
extern Graphics_Context g_sContext;

#define LCD_SIZE    128

#define MIN_RANGE   0           // min margin is 0+1
#define MAX_RANGE   31          // max margin is 128/RATIO-1
#define RATIO       4           // 1:4, 1 node = 4 pixels

void _graphics_initMenu();
void _graphics_drawSnake(Snake* s);
void _graphics_drawNode(uint8_t x, uint8_t y);
void _graphics_hideNode(uint8_t x, uint8_t y);
void _graphics_lose(Snake* s, uint8_t x, uint8_t y);
void _graphics_drawApple(Apple *apple);
void _graphics_hideApple(Apple *apple);


#endif
