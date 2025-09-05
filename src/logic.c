#include "logic.h"

#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"

// функция всей игры
void game() {
    init_graphics();
    int score = 0;
    struct snake snake;
    struct apple apple;
    snake.body[0].i = rows / 2;
    snake.body[0].j = cols / 2;
    snake.length = 1;
    apple.coords.i = -1;
    apple.coords.j = -1;
    apple.last_spawn = time(NULL);
    int game_over = 0;

    while (!game_over) {
        int move = getch();
        move = tolower(move);
        if (move != ERR) {
            if (move == KEY_UP || move == 'w' || move == KEY_DOWN || move == 's' || move == KEY_RIGHT ||
                move == 'd' || move == KEY_LEFT || move == 'a') {
                snake.direction = move;
            }
        }
        clear();
        draw_borders(score);
        snake_move(&snake);
        apple_appierence(&apple, &snake);
        screen_wrapping(&snake);
        if (snake_eats_apple(&snake, &apple, &score)) {
            apple.last_spawn = time(NULL);
        }
        draw_apple(&apple);
        draw_snake(&snake);

        refresh();
        napms(130);
    }
    endup_game();
}

// завёртывает поле, змейка не выйдет за границы экрана
void screen_wrapping(struct snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        if (snake->body[i].i >= rows - 1) {
            snake->body[i].i = 1;
        } else if (snake->body[i].i <= 0) {
            snake->body[i].i = rows - 2;
        }
        if (snake->body[i].j >= cols - 1) {
            snake->body[i].j = 1;
        } else if (snake->body[i].j <= 0) {
            snake->body[i].j = cols - 2;
        }
    }
}

// движения змейки. можно управлять стрелками и wasd
void snake_move(struct snake *snake) {
    int old_i[snake->length], old_j[snake->length];

    for (int i = 0; i < snake->length; i++) {
        old_i[i] = snake->body[i].i;
        old_j[i] = snake->body[i].j;
    }

    switch (snake->direction) {
        case KEY_UP:
            (snake->body[0].i)--;
            break;
        case 'w':
            (snake->body[0].i)--;
            break;
        case KEY_DOWN:
            (snake->body[0].i)++;
            break;
        case 's':
            (snake->body[0].i)++;
            break;
        case KEY_RIGHT:
            (snake->body[0].j)++;
            break;
        case 'd':
            (snake->body[0].j)++;
            break;
        case KEY_LEFT:
            (snake->body[0].j)--;
            break;
        case 'a':
            (snake->body[0].j)--;
            break;
        default:
            break;
    }

    for (int i = 1; i < snake->length; i++) {
        snake->body[i].i = old_i[i - 1];
        snake->body[i].j = old_j[i - 1];
    }
}

// выбирает случайные координаты для спавна яблока
void apple_appierence(struct apple *apple, struct snake *snake) {
    static int initialized = 0;
    time_t current_time = time(NULL);

    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    if ((apple->coords.i == -1 && apple->coords.j == -1) || current_time - apple->last_spawn >= apple_delay) {
        do {
            apple->coords.i = (rand() % (rows - 2)) + 1;
            apple->coords.j = (rand() % (cols - 2)) + 1;
        } while (!position_is_free(apple->coords.i, apple->coords.j, snake));
            apple->last_spawn = current_time;
    }
}

// проверяет, свободны ли координаты, съела ли змея яблоко
int position_is_free(int i, int j, struct snake *snake) {
    int flag = 1;
    for (int index = 0; index < snake->length && flag; index++) {
        if (i == snake->body[index].i && j == snake->body[index].j) {
            flag = 0;
        }
    }
    return flag;
}

// ищет свободные координаты
struct location looking_for_free_position(struct snake *snake) {
    struct location free;
    free.i = -1;
    free.j = -1;
    int flag = 0;
    for (int i = 1; i < rows - 2 && !flag; i++) {
        for (int j = 1; j < cols - 2 && !flag; j++) {
            if (position_is_free(i, j, snake)) {
                free.i = i;
                free.j = j;
                flag = 1;
            }
        }
    }
    return free;
}

// определяет, съела ли змея яблоко
int snake_eats_apple(struct snake *snake, struct apple *apple, int *score) {
    int flag = 0;
    if (snake->body[0].i == apple->coords.i && snake->body[0].j == apple->coords.j) {
        snake->length++;
        snake->body[snake->length - 1].i = snake->body[snake->length - 2].i;
        snake->body[snake->length - 1].j = snake->body[snake->length - 2].j;
        apple->coords.i = -1;
        apple->coords.j = -1;
        apple->last_spawn = time(NULL);
        (*score)++;
        flag = 1;
    }
    return flag;
}