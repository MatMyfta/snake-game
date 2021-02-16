#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

extern uint8_t highscore;
extern uint8_t game;

typedef struct Node {
    uint8_t x;
    uint8_t y;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Snake {
    Node *head;
    Node *tail;
    uint16_t score;
}Snake;

void s_init(Snake *s);
void s_move(Snake *s, uint8_t x, uint8_t y);
void s_add(Snake *s, uint8_t x, uint8_t y);


#endif
