#include "graphics.h"

void graphics_loadField(Graphics_Context *context, uint8_t **field) {
    const uint8_t RATIO = (uint8_t) (LCD_SIZE/FIELD_SIZE);
    uint8_t i,j;
    for (i=0; i<FIELD_SIZE; i++) {
        for (j=0; j<FIELD_SIZE; j++) {
            if (field[i][j] == SNAKE) {
                const Graphics_Rectangle grect = { i*RATIO, j*RATIO, (i+1)*RATIO-1, (j+1)*RATIO-1 };
                Graphics_fillRectangle(context,&grect);
            }
        }
    }
}
