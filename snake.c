#include "snake.h"

/*
 * Initialise snake position
 */
void s_init(uint8_t **field, Snake *snake) {
    Node n;             // initial head and tail position
    n.x = FIELD_SIZE/2;     // center
    n.y = 1;                // left
    snake->head = snake->tail = n;

    s_add(field, snake, n.x, n.y+1);
    s_add(field, snake, n.x, n.y+2);
}

/*
 * moves the snake
 */
void s_move(uint8_t **field, Snake *s, uint8_t x, uint8_t y) {
    Node h_tmp = { .x = x, .y = y, .next = &(s->head) };
    Node t_tmp = *(s->tail.next);

    // move the head
    s->head = h_tmp;
    field[x][y] = SNAKE;

    // move the tail
    field[s->tail.x][s->tail.y] = EMPTY;
    s->tail = t_tmp;
}

/*
 * Add a node to the snake by adding a new point to the head
 */
void s_add(uint8_t **field, Snake *s, uint8_t x, uint8_t y) {
    Node tmp = { .x = x, .y = y, .next = &(s->head) };
    s->head = tmp;

    field[x][y] = SNAKE;
}
