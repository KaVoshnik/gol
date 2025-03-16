#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLUMN 80

int **init_world();
void print_world(int **world);
int get_live_status(int **world, int rows, int cols);
int alive(int **world, int rows, int cols);
int dead(int **world, int rows, int cols);
void read_point_neighbors(int **world, int rows, int cols);
int count_live_neighbors();
void next_gen();
void copy_world();
int keyinp(); // this fix(input keyboard)

int main() {
  int **world = init_world();
  print_world(world);

  free(world);
  return 0;
}

int **init_world() {
  int **world = malloc(ROWS * COLUMN * sizeof(int) + ROWS * sizeof(int *));
  int *line = (int *)(world + ROWS);
  int input;

  for (int i = 0; i < ROWS; i++) {
    world[i] = line + i * COLUMN;
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMN; j++) {
      scanf("%d", &input);
      world[i][j] = input;
    }
  }

  return world;
}

void print_world(int **world) { 
  for (int i = 0; i < ROWS; ++i) {
    if (world[i][0] == 0)
        printf(" ");
    else
        printf("o");
    for (int j = 1; j < COLUMN; ++j) {
        if (world[i][j] == 0)
            printf(" ");
        else
            printf("o");
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

// void read_point_neighbors(int **world, int rows, int cols) {} 