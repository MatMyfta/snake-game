#include "snake.h"
#include "graphics.h"
#include <stdlib.h>

/*
 * Initialise snake position
 */
void s_init(Snake *snake) {
    uint8_t initial_x = 2;
    uint8_t initial_y = LCD_SIZE/(RATIO*2);

    Node *n = malloc(sizeof(Node));
    n->x = initial_x;
    n->y = initial_y;
    n->next = NULL;
    n->prev = NULL;

    snake->head = n;
    snake->tail = n;

    s_add(snake, n->x+1, n->y);
    snake->tail->prev = snake->head;
    s_add(snake, n->x+2, n->y);
}

/*
 * moves the snake
 */
void s_move(Snake *s, uint8_t x, uint8_t y) {
    if (x == MAX_RANGE) x = MIN_RANGE+1;
    if (x == MIN_RANGE) x = MAX_RANGE-1;
    if (y == MAX_RANGE) y = MIN_RANGE+1;
    if (y == MIN_RANGE) y = MAX_RANGE-1;
    s_add(s,x,y);

    _graphics_drawNode(x,y);

    if (x == apple.x && y == apple.y) {
        _graphics_hideApple(&apple);
        init_apple();
    } else {
        _graphics_hideNode(s->tail->x, s->tail->y);
        s->tail = s->tail->prev;
        free(s->tail->next);
        s->tail->next = NULL;
    }
}

/*
 * Add a node to the snake by adding a new point to the head
 */
void s_add(Snake *s, uint8_t x, uint8_t y) {
    Node *tmp = malloc(sizeof(Node));
    tmp->x = x;
    tmp->y = y;
    tmp->next = s->head;
    tmp->prev = NULL;

    s->head->prev = tmp;
    s->head = tmp;
}

void deinit(Snake *s) {
    Node *tmp = s->head;
    while(tmp) {
        Node *p = tmp;
        tmp = tmp->next;
        free(p);
    }
}

