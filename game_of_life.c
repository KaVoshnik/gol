#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define ROWS 25
#define COLUMN 80

int **init_world();
void free_world(int **world);
int init_game_field(int **world);
void print_world(int **world);
void fill_matrix(int **world, char *file_name);
int get_live_status(int **world, int rows, int cols);
int neighbors(int **world, int rows, int cols);
int alive(int **world, int rows, int cols);
int dead(int **world, int rows, int cols);
void game_in_progress(int **world, int rows, int cols);

int main() {
    int **world = init_world();
    game_in_progress(world, ROWS, COLUMN);
    free_world(world);
    return 0;
}
void free_world(int **world) {
    for (int i = 0; i < ROWS; i++) {
        free(world[i]);
    }
    free(world);
}
int init_game_field(int **world) {
    int select_map;
    char ch;
    printf("Select premade map [1-5]\n");
    if (scanf("%d%c", &select_map, &ch) == 2 && ch == '\n' && select_map >= 1 && select_map <= 5) {
        if (select_map == 1) {
            fill_matrix(world, "map1.txt");
        }
        if (select_map == 2) {
            fill_matrix(world, "map2.txt");
        }
        if (select_map == 3) {
            fill_matrix(world, "map3.txt");
        }
        if (select_map == 4) {
            fill_matrix(world, "map4.txt");
        }
        if (select_map == 5) {
            fill_matrix(world, "map5.txt");
        }
    } else {
        printf("n/a");
        select_map = -1;
    }
    return select_map;
}
void game_in_progress(int **world, int rows, int cols) {
    if (init_game_field(world) != -1) {
        int game_on = 1;
        initscr();
        cbreak();
        noecho();
        nodelay(stdscr, TRUE);
        int delay = 60;
        while (game_on) {
            char key;
            clear();
            printw("Use i and o to change game speed\nPress q to quit\n");
            napms(delay);
            print_world(world);
            int **new_world = init_world();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    new_world[i][j] = get_live_status(world, i, j);
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    world[i][j] = new_world[i][j];
                }
            }
            free_world(new_world);
            key = getch();
            if (key == 'o' && delay > 20) {
                delay = delay - 10;
            }
            if (key == 'i' && delay < 250) {
                delay = delay + 10;
            }
            if (key == 'q') {
                game_on = 0;
            }
            refresh();
        }
    }
    endwin();
}

void fill_matrix(int **world, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("n/a");
        free_world(world);
        return;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMN; j++) {
            fscanf(file, "%d", &world[i][j]);
        }
    }
    fclose(file);
}

int **init_world() {
    int **world = malloc(ROWS * sizeof(int *));
    for (int i = 0; i < ROWS; i++) {
        world[i] = malloc(COLUMN * sizeof(int));
    }
    return world;
}

void print_world(int **world) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (world[i][j] == 0)
                printf(" ");
            else
                printf("@");
        }
        printf("\n");
    }
}

int get_live_status(int **world, int rows, int cols) {
    int status;
    if (world[rows][cols] == 0) {
        status = alive(world, rows, cols);
    } else {
        status = dead(world, rows, cols);
    }
    return status;
}

int neighbors(int **world, int rows, int cols) {
    int n = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int r = rows + i;
            int c = cols + j;
            if (r < 0) {
                r = ROWS - 1;
            } else if (r >= ROWS) {
                r = 0;
            }
            if (c < 0) {
                c = COLUMN - 1;
            } else if (c >= COLUMN) {
                c = 0;
            }
            if (world[r][c] == 1) {
                n++;
            }
        }
    }
    return n;
}

int alive(int **world, int rows, int cols) {
    int alive = 0;
    int count_n = neighbors(world, rows, cols);
    if (count_n == 3) {
        alive = 1;
    }
    return alive;
}

int dead(int **world, int rows, int cols) {
    int dead = 1;
    int count_n = neighbors(world, rows, cols);
    if (count_n < 2 || count_n > 3) {
        dead = 0;
    }
    return dead;
}