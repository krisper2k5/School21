#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define lines 25
#define columns 80
#define min_speed 0.1
#define max_speed 2.0

void print_welcome_page(void);
void input(char *key, float *speed);
void render_game_frame(int **current_generation);
int create_generation(int ***current_generation, int ***next_generation);
void select_matrix(int **matrix);
int count(int **matrix);
int speed_adjustment(char control, int *exit_flag, int speed_change);
void updating_matrices(int **first_matrix, int **second_matrix);
int neighbor_counting(int **first_matrix, int row, int column);
int to_live_or_not_that_is_the_question(int neighbours, int condition);
void replace(int **second_matrix, int **first_matrix);
int check(int **first_matrix, int **second_matrix);
void free_generation(int **first_matrix, int **second_matrix);

int main() {
    int **first_matrix = NULL;
    int **second_matrix = NULL;
    float speed_change = 1.0;
    char exit_flag = 0;

    nodelay(initscr(), 1);
    noecho();

    if (create_generation(&first_matrix, &second_matrix)) {
        select_matrix(first_matrix);

        // основной цикл
        while (exit_flag != 'q') {
            input(&exit_flag, &speed_change);

            usleep(speed_change * 100000);
            clear();
            updating_matrices(first_matrix, second_matrix);

            if (check(first_matrix, second_matrix)) {
                exit_flag = 'q';
            }
            replace(second_matrix, first_matrix);
        }
    }
    free_generation(first_matrix, second_matrix);
    return 0;
}

void select_matrix(int **matrix) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (1 != scanf("%1d", &matrix[i][j]) || (matrix[i][j] != 0 && matrix[i][j] != 1)) {
            }
        }
    }
}

void render_game_frame(int **current_generation) {
    move(0, 0);
    clear();
    printw(
        "#####################################################################"
        "#############\n");
    printw(
        "#                        Type \"a\" to speed up the game.            "
        "              #\n");
    printw(
        "#                       Type \"z\" to speed down the game.           "
        "              #\n");
    printw(
        "#                          Type \"q\" to exit the game.              "
        "              #\n");
    printw(
        "#####################################################################"
        "#############\n");
    for (int y = 0; y < lines; y++) {
        for (int x = -1; x <= columns; x++) {
            if (-1 == x || columns == x) {
                printw("#");
            } else if (current_generation[y][x] == 1) {
                printw("*");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    printw(
        "#####################################################################"
        "#############\n");
    refresh();
}

void updating_matrices(int **first_matrix, int **second_matrix) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            second_matrix[i][j] = to_live_or_not_that_is_the_question(neighbor_counting(first_matrix, i, j),
                                                                      first_matrix[i][j]);
        }
    }
    render_game_frame(second_matrix);
}

int neighbor_counting(int **first_matrix, int row, int column) {
    int neighbours = 0;
    for (int x = row - 1; x <= row + 1; x++) {
        for (int y = column - 1; y <= column + 1; y++) {
            if (x != row || y != column) {
                int neighbour_row = (x + lines) % lines;
                int neighbour_column = (y + columns) % columns;
                neighbours += first_matrix[neighbour_row][neighbour_column];
            }
        }
    }
    return neighbours;
}

int to_live_or_not_that_is_the_question(int neighbours, int condition) {
    if ((neighbours == 2 || neighbours == 3) && condition == 1) {
        return 1;
    } else if (neighbours == 3 && condition == 0) {
        return 1;
    } else {
        return 0;
    }
}

void replace(int **second_matrix, int **first_matrix) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            first_matrix[i][j] = second_matrix[i][j];
        }
    }
}

int check(int **first_matrix, int **second_matrix) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (first_matrix[i][j] != second_matrix[i][j]) return 0;
        }
    }
    return 1;  // матрицы совпадают
}

int create_generation(int ***current_generation, int ***next_generation) {
    int error = 1;
    *current_generation = malloc(lines * columns * sizeof(int) + lines * sizeof(int *));
    *next_generation = malloc(lines * columns * sizeof(int) + lines * sizeof(int *));
    if (NULL == *current_generation || NULL == *next_generation) {
        error = 0;
    } else {
        int *cur_gen_beginning = (int *)(*current_generation + lines);
        int *next_gen_beginning = (int *)(*next_generation + lines);
        for (int i = 0; i < lines; i++) {
            (*current_generation)[i] = cur_gen_beginning + columns * i;
            (*next_generation)[i] = next_gen_beginning + columns * i;
            for (int j = 0; j < columns; j++) {
                (*current_generation)[i][j] = 0;
                (*next_generation)[i][j] = 0;
            }
        }
    }
    return error;
}

void input(char *key, float *speed) {
    char current_char = 0;

    if ((current_char = getch()) == 'q' || current_char == 'Q') {
        *key = 'q';
    } else if (current_char == 'z') {
        if (*speed < max_speed) *speed += min_speed;
    } else if (current_char == 'a') {
        if (*speed > min_speed) *speed -= min_speed;
    }

    while (getch() != ERR) {
    }
}

void free_generation(int **current_generation, int **next_generation) {
    free(current_generation);
    free(next_generation);
}
