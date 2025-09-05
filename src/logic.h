#ifndef LOGIC_H
#define LOGIC_H
#define max_length 1920
#define max_apple 1918
#define apple_delay 10

// структура локации по координатам
struct location {
    int i;
    int j;
};

// структура змейки
struct snake {
    struct location body[max_length];
    int length;
    int direction;
};

// структура яблока
struct apple {
    struct location coords;
    int last_spawn;
};

// прототипы функций
void game();
void screen_wrapping(struct snake *snake);
void snake_move(struct snake *snake);
void apple_appierence(struct apple *apple, struct snake *snake);
struct location looking_for_free_position(struct snake *snake);
int position_is_free(int i, int j, struct snake *snake);
int snake_eats_apple(struct snake *snake, struct apple *apple, int *score);

#endif