#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include "pico/stdlib.h"

extern void init_oled_display();
extern void zerar_display(uint8_t *buffer);
extern void desenhar_display(uint8_t *buffer);
extern void score_gamer(uint8_t *buffer);

#endif