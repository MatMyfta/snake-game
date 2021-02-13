#include "graphics.h"

#define NULL (void*)0

void _graphics_drawSnake(Snake* s);
void _graphics_drawNode(uint8_t, uint8_t);

void _graphics_drawSnake(Snake *s) {
    Node *_tmp = s->head;

    Graphics_clearDisplay(&g_sContext);

    // For each node
    while (_tmp != NULL) {
        _graphics_drawNode(_tmp->x, _tmp->y);
        _tmp = _tmp->next;
    }
}

/*
 * Draw a node of the snake; 1 node equals a 2*2 pixels square.
 */
void _graphics_drawNode(uint8_t x, uint8_t y) {
    Graphics_Rectangle n_rect = { x*RATIO, y*RATIO, (x+1)*RATIO-1, (y+1)*RATIO-1 };
    Graphics_fillRectangle(&g_sContext,&n_rect);
}
