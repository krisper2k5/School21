    #include <stdio.h>

    #define FIELD_WIDTH 80
    #define FIELD_HEIGHT 25
    #define PADDLE_SIZE 3
    #define WINNING_SCORE 21
    #define PADDLE_LEFT_X 10
    #define PADDLE_RIGHT_X (FIELD_WIDTH - 11)

    void clear_and_draw(int paddle_left_y, int paddle_right_y, int ball_x, int ball_y, int score_left,
                        int score_right) {
        /* Очистка терминала, и перенос поля в левый верхний угол */
        printf("\033[2J\033[H");

        /*  Верхняя линия */
        for (int x = 0; x < FIELD_WIDTH; x++) {
            printf("-");
        }
        printf("\n");

        /* Отрисовка основного поля */
        for (int y = 1; y < FIELD_HEIGHT - 1; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                if (x == 0 || x == FIELD_WIDTH - 1) {
                    printf(" ");
                } else if (x == ball_x && y == ball_y) {
                    printf("O");
                } else if (x == PADDLE_LEFT_X &&
                        (y == paddle_left_y - 1 || y == paddle_left_y || y == paddle_left_y + 1)) {
                    printf("|");
                } else if (x == PADDLE_RIGHT_X &&
                        (y == paddle_right_y - 1 || y == paddle_right_y || y == paddle_right_y + 1)) {
                    printf("|");
                } else if (x == FIELD_WIDTH / 2 && y % 2 == 0) {
                    printf(":");
                } else if (y == 1) {
                    if (x == FIELD_WIDTH / 2 - 3) {
                        printf("%d", score_left);
                    } else if (x == FIELD_WIDTH / 2 + 2) {
                        printf("%d", score_right);
                    } else {
                        printf(" ");
                    }
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        /* Нижнаяя граница */
        for (int x = 0; x < FIELD_WIDTH; x++) {
            printf("-");
        }
        printf("\n");
    }

    int main(void) {
        int paddle_left_y = FIELD_HEIGHT / 2;
        int paddle_right_y = FIELD_HEIGHT / 2;
        int ball_x = FIELD_WIDTH / 2;
        int ball_y = FIELD_HEIGHT / 2;
        int ball_dx = 1;
        int ball_dy = 1;
        int score_left = 0;
        int score_right = 0;

        while (1) {
            clear_and_draw(paddle_left_y, paddle_right_y, ball_x, ball_y, score_left, score_right);

            if (score_left >= WINNING_SCORE) {
                printf("Player on the LEFT wins!\n");
                break;
            }
            if (score_right >= WINNING_SCORE) {
                printf("Player on the RIGHT wins!\n");
                break;
            }

            int input = getchar();

            if (input == 'A' || input == 'a') {
                if (paddle_left_y > 2) {
                    paddle_left_y = paddle_left_y - 1;
                }
            } else if (input == 'Z' || input == 'z') {
                if (paddle_left_y < FIELD_HEIGHT - 3) {
                    paddle_left_y = paddle_left_y + 1;
                }
            }

            if (input == 'K' || input == 'k') {
                if (paddle_right_y > 2) {
                    paddle_right_y = paddle_right_y - 1;
                }
            } else if (input == 'M' || input == 'm') {
                if (paddle_right_y < FIELD_HEIGHT - 3) {
                    paddle_right_y = paddle_right_y + 1;
                }
            } else if (input == ' ') {
                /* Пропуск хода */
            }

            /* Обновление позиции мячика */
            ball_x = ball_x + ball_dx;
            ball_y = ball_y + ball_dy;

            /* Отскок от нижней или верхней ракетки */
            if (ball_y <= 1 || ball_y >= FIELD_HEIGHT - 2) {
                ball_dy = -ball_dy;
            }

            /* Отскок от левой ракетки */
            if (ball_x == PADDLE_LEFT_X + 1 &&
                (ball_y == paddle_left_y - 1 || ball_y == paddle_left_y || ball_y == paddle_left_y + 1)) {
                ball_dx = -ball_dx;
            }

            /* Отскок от правой ракетки */
            if (ball_x == PADDLE_RIGHT_X - 1 &&
                (ball_y == paddle_right_y - 1 || ball_y == paddle_right_y || ball_y == paddle_right_y + 1)) {
                ball_dx = -ball_dx;
            }

            /* ГОЛ!!! */
            if (ball_x <= 0) {
                score_right = score_right + 1;
                ball_x = FIELD_WIDTH / 2;
                ball_y = FIELD_HEIGHT / 2;
                ball_dx = 1;
                if (ball_dy == 0) ball_dy = 1;
            } else if (ball_x >= FIELD_WIDTH - 1) {
                score_left = score_left + 1;
                ball_x = FIELD_WIDTH / 2;
                ball_y = FIELD_HEIGHT / 2;
                ball_dx = -1;
                if (ball_dy == 0) ball_dy = 1;
            }
        }
        return 0;
    }
