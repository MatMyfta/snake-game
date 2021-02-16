#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
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
    snake->score = 0;

    s_add(snake, n->x+1, n->y);
    snake->tail->prev = snake->head;
    s_add(snake, n->x+2, n->y);

    game = 1;
}

int s_contains(Snake *s, uint8_t x, uint8_t y) {
    Node *tmp = s->head->next;
    while (tmp != s->tail->next) {
        if (tmp->x == x && tmp->y == y)
            return 1;
        tmp = tmp->next;
    }
    return 0;
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

    if(s_contains(s,x,y) == 1) {
        highscore = ((s->score) >= highscore ? (s->score) : highscore);
        game = 0;
        _graphics_lose(s,x,y);
    }
    else {
        if (x == apple.x && y == apple.y) {
            _graphics_hideApple(&apple);
            s->score += 5;
            init_apple();
        } else {
            _graphics_hideNode(s->tail->x, s->tail->y);
            s->tail = s->tail->prev;
            free(s->tail->next);
            s->tail->next = NULL;
        }
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

