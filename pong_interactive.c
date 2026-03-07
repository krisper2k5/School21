#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define WIN_SCORE 21
#define LEFT_PADDLE_X 10
#define RIGHT_PADDLE_X (WIDTH - 11)
#define FRAME_DELAY 200

/* Отрисовка поля */
void draw_field(int left_y, int right_y, int ball_x, int ball_y, int left_score, int right_score) {
    clear();

    /* Верхняя граница */
    for (int x = 0; x < WIDTH; x++) mvaddch(0, x, '-');

    /* Основная часть поля */
    for (int y = 1; y < HEIGHT - 1; y++) {
        for (int x = 0; x < WIDTH; x++) {
            /* Боковые границы */
            if (x == 0 || x == WIDTH - 1) {
                mvaddch(y, x, ' ');
            }
            /* Мяч */
            else if (x == ball_x && y == ball_y) {
                mvaddch(y, x, 'O');
            }
            /* Левая ракетка */
            else if (x == LEFT_PADDLE_X && (y == left_y - 1 || y == left_y || y == left_y + 1)) {
                mvaddch(y, x, '|');
            }
            /* Правая ракетка */
            else if (x == RIGHT_PADDLE_X && (y == right_y - 1 || y == right_y || y == right_y + 1)) {
                mvaddch(y, x, '|');
            }
            /* Центральная линия */
            else if (x == WIDTH / 2 && y % 2 == 0) {
                mvaddch(y, x, ':');
            }
            /* Счёт */
            else if (y == 1) {
                if (x == WIDTH / 2 - 3)
                    mvaddch(y, x, '0' + left_score % 10);
                else if (x == WIDTH / 2 + 2)
                    mvaddch(y, x, '0' + right_score % 10);
                else
                    mvaddch(y, x, ' ');
            }
            /* Пустое место */
            else {
                mvaddch(y, x, ' ');
            }
        }
    }

    /* Нижняя граница */
    for (int x = 0; x < WIDTH; x++) mvaddch(HEIGHT - 1, x, '-');

    /* Вывод счёта  */
    mvprintw(1, WIDTH / 2 - 3, "%d", left_score);
    mvprintw(1, WIDTH / 2 + 2, "%d", right_score);

    refresh();
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    timeout(FRAME_DELAY);
    curs_set(0);

    int left_y = HEIGHT / 2;
    int right_y = HEIGHT / 2;

    /* Позиция и направление мяча */
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int dx = 1;
    int dy = 1;

    /* Счёт */
    int left_score = 0;
    int right_score = 0;

    while (1) {
        draw_field(left_y, right_y, ball_x, ball_y, left_score, right_score);

        if (left_score >= WIN_SCORE) {
            mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "LEFT PLAYER WINS!");
            refresh();
            break;
        }
        if (right_score >= WIN_SCORE) {
            mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "RIGHT PLAYER WINS!");
            refresh();
            break;
        }

        int key = getch();

        if (key == 'A' || key == 'a') {
            if (left_y > 2) left_y--;
        } else if (key == 'Z' || key == 'z') {
            if (left_y < HEIGHT - 3) left_y++;
        }

        if (key == 'K' || key == 'k') {
            if (right_y > 2) right_y--;
        } else if (key == 'M' || key == 'm') {
            if (right_y < HEIGHT - 3) right_y++;
        }

        /* Движение мяча */
        ball_x += dx;
        ball_y += dy;

        /* Отскок от верха и низа */
        if (ball_y <= 1 || ball_y >= HEIGHT - 2) dy = -dy;

        /* Отскок от левой ракетки */
        if (ball_x == LEFT_PADDLE_X + 1 &&
            (ball_y == left_y - 1 || ball_y == left_y || ball_y == left_y + 1)) {
            dx = -dx;
        }

        /* Отскок от правой ракетки */
        if (ball_x == RIGHT_PADDLE_X - 1 &&
            (ball_y == right_y - 1 || ball_y == right_y || ball_y == right_y + 1)) {
            dx = -dx;
        }

        /* Гол */
        if (ball_x <= 0) {
            right_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dx = 1;
            if (dy == 0) dy = 1;
        } else if (ball_x >= WIDTH - 1) {
            left_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            dx = -1;
            if (dy == 0) dy = 1;
        }
    }

    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 12, "Press any key to exit...");
    refresh();
    timeout(-1);
    getch();
    endwin();

    return 0;
}
