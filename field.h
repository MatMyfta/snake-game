#ifndef __FIELD_H__
#define __FIELD_H__


#include <ti/devices/msp432p4xx/inc/msp.h>

#define FIELD_SIZE 16
/*
 * the field is a matrix of integers, values in cells are mapped as follows
 *  - 0 means there is nothing
 *  - 1 means there is a piece of snake
 *  - 2 means there is food
 */
#define EMPTY   0
#define SNAKE   1
#define FOOD    2


void f_init(uint8_t **field);


#endif
