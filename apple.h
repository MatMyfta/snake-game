#ifndef __APPLE_H__
#define __APPLE_H__

#include <ti/devices/msp432p4xx/inc/msp.h>

typedef struct Apple {
    uint8_t x;
    uint8_t y;
}Apple;

Apple apple;

void init_apple();


#endif
