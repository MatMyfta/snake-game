#ifndef __SNAKE_H__
#define __SNAKE_H__


#include <ti/devices/msp432p4xx/inc/msp.h>
#include "field.h"

enum SnakeDirection {UP,LF,DW,RT};

typedef struct Node {
    uint8_t x;
    uint8_t y;
    struct Node *next;
}Node;

typedef struct Snake {
    Node head;
    Node tail;
}Snake;


void s_init(uint8_t **field, Snake *s);
void s_move(uint8_t **field, Snake *s, uint8_t x, uint8_t y);
void s_add(uint8_t **field, Snake *s, uint8_t x, uint8_t y);


#endif
