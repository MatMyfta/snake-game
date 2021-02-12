#include "snake.h"

/*
 * Initialise snake position
 */
void s_init(Snake *snake) {
    uint8_t initial_x = 2;
    uint8_t initial_y = LCD_SIZE/(RATIO*2);
    Node n = { .x = initial_x, .y = initial_y, .next = (void*)0, .prev = (void*)0 };
    snake->head = &n;
    snake->tail = &n;

    _graphics_drawNode(n.x, n.y);

    s_add(snake, n.x+1, n.y);
    snake->tail->prev = snake->head;
    s_add(snake, n.x+2, n.y);
}

/*
 * moves the snake
 */
void s_move(Snake *s, uint8_t x, uint8_t y) {
    Node h_tmp = { .x = x, .y = y, .next = s->head, .prev = (void*)0};
    Node t_tmp = *(s->tail->prev);

    // move the head
    s->head = &h_tmp;

    // move the tail
    s->tail = &t_tmp;
}

/*
 * Add a node to the snake by adding a new point to the head
 */
void s_add(Snake *s, uint8_t x, uint8_t y) {
    Node tmp = { .x = x, .y = y, .next = s->head, .prev = (void*)0 };
    s->head->prev = &tmp;
    s->head = &tmp;

    _graphics_drawNode(s->head->x, s->head->y);
}
