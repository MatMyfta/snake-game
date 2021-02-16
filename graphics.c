#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

extern uint8_t highscore;

void _graphics_drawSnake(Snake* s);
void _graphics_drawNode(uint8_t, uint8_t);

void _graphicsInit(){
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setFont(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);

}

void _graphics_initMenu() {
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Welcome to SNAKE",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    20,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Press left button",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    55,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"to start game",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    70,
                                    OPAQUE_TEXT);

    char string[19];
    sprintf(string, "highscore: %5d", highscore);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    19,
                                    64,
                                    105,
                                    OPAQUE_TEXT);
}

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

void _graphics_lose(Snake *s, uint8_t x, uint8_t y) {
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    _graphics_drawNode(x,y);

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"You lose",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    25,
                                    OPAQUE_TEXT);
    char string[14];
    sprintf(string, "Score: %5d", s->score);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    14,
                                    64,
                                    60,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Press left button",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    85,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"to go back to menu",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    100,
                                    OPAQUE_TEXT);
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
