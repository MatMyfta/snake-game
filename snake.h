#ifndef __SNAKE_H__
#define __SNAKE_H__


#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdlib.h>
#include "graphics.h"

#ifndef __CONTEXT__
#define __CONTEXT__
extern Graphics_Context g_sContext;
#endif

enum SnakeDirection {UP,LF,DW,RT};

typedef struct Node {
    uint8_t x;
    uint8_t y;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Snake {
    Node *head;
    Node *tail;
}Snake;


void s_init(Snake *s);
void s_move(Snake *s, uint8_t x, uint8_t y);
void s_add(Snake *s, uint8_t x, uint8_t y);


#endif
