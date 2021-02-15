#include "graphics.h"

#define NULL (void*)0

void _graphics_drawSnake(Snake* s);
void _graphics_drawNode(uint8_t, uint8_t);

void _graphics_drawSnake(Snake *s) {
    Node *_tmp = s->head;

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

void _graphics_hideNode(uint8_t x, uint8_t y) {
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    _graphics_drawNode(x,y);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
}

void _graphics_lose(uint8_t x, uint8_t y) {
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    _graphics_drawNode(x,y);
    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
}

void _graphics_drawApple(Apple *apple) {
    Graphics_fillCircle(&g_sContext, apple->x*RATIO+1, apple->y*RATIO+1, 2);
}

void _graphics_hideApple(Apple *apple) {
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_fillCircle(&g_sContext, apple->x*RATIO+1, apple->y*RATIO+1, 3);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);

}
