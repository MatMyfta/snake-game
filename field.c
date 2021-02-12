#include "field.h"

/*
 * initialize the field with 0
 */
void f_init(uint8_t **field) {
    uint8_t i,j;

    for (i = 0; i < FIELD_SIZE; i++)
        for (j = 0; j < FIELD_SIZE; j++)
            field[i][j] = EMPTY;
}
