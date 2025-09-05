#include "graphics.h"

#include <ncurses.h>

// инициализирует ncurses и отрисовывает поле
void init_graphics() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    draw_borders(0);

    refresh();
}

// отрисовывает границы поля
void draw_borders(int score) {
    mvprintw(0, 0, "+");
    mvprintw(0, cols - 1, "+");
    mvprintw(rows - 1, 0, "+");
    mvprintw(rows - 1, cols - 1, "+");
    mvprintw(rows, 0, "Snake score: %d", score);
    for (int i = 1; i < cols - 1; i++) {
        mvprintw(0, i, "-");
        mvprintw(rows - 1, i, "-");
    }
    for (int j = 1; j < rows - 1; j++) {
        mvprintw(j, 0, "|");
        mvprintw(j, cols - 1, "|");
    }

    refresh();
}

// отрисовывает змейку
void draw_snake(struct snake *snake) {
    mvprintw(snake->body[0].i, snake->body[0].j, "@");

    for (int index = 1; index < snake->length; index++) {
        mvprintw(snake->body[index].i, snake->body[index].j, "#");
    }

    refresh();
}

// отрисовывает яблоко
void draw_apple(struct apple *apple) {
    if (apple->coords.i >= 1 && apple->coords.i <= rows - 1 && apple->coords.j >= 1 && apple->coords.j <= cols - 1) {
        mvprintw(apple->coords.i, apple->coords.j, "O");
    }
}

// сворачивает ncurses и игру
void endup_game() { endwin(); }