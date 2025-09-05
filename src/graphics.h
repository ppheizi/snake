#ifndef GRAPHICS_H
#define GRAPHICS_H
#define cols 80
#define rows 24
#include "logic.h"

// прототипы функций
void init_graphics();
void draw_borders(int score);
void draw_snake(struct snake *snake);
void draw_apple(struct apple *apple);
void endup_game();

#endif