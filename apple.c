#include "apple.h"
#include "graphics.h"
#include <stdlib.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

uint8_t get_rand();
void init_apple();

void init_apple() {
    apple.x = get_rand();
    apple.y = get_rand();
    _graphics_drawApple(&apple);
}

uint8_t get_rand() {
    return (uint8_t) ((rand()*ADC14_getResult(ADC_MEM0)/ADC14_getResult(ADC_MEM1) << 10)% (MAX_RANGE-1 - MIN_RANGE) + 1);
}
