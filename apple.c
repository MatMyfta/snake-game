#include "apple.h"
#include "graphics.h"
#include <stdlib.h>

uint8_t get_rand();
void init_apple();

void init_apple() {
    apple.x = get_rand();
    apple.y = get_rand();
    _graphics_drawApple(&apple);
}

uint8_t get_rand() {
    return (uint8_t) (rand() % (MAX_RANGE - MIN_RANGE) + 1);
}
