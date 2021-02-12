#include "graphics.h"

/*
 * Draw a node of the snake
 * 1 node equals a 2*2 pixels square
 */
void _graphics_drawNode(uint8_t x, uint8_t y) {
    Graphics_Rectangle n_rect = { x*RATIO, y*RATIO, (x+1)*RATIO-1, (y+1)*RATIO-1 };
    Graphics_fillRectangle(&g_sContext,&n_rect);
}
