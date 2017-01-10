#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define CELL_IS_ALIVE 1
#define CELL_IS_DEAD 0
#define CELL_DOES_NOT_EXIST -1
#define FUNCTION_SUCCEEDED 0
#define SECONDS_TO_SLEEP 83333
#define MAX_NUMBER_OF_NEIGHBORS 4

static int board[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};

typedef struct {
  int x;
  int y;
} tTuple;

typedef struct {
  int right;
  int left;
  int above;
  int above_right;
  int above_left;
  int below;
  int below_left;
  int below_right;
} tNeighbors;

int is_valid_x(int x) {
  return x < SCREEN_WIDTH && x >= 0;
}

int is_valid_y(int y) {
  return y < SCREEN_HEIGHT && y >= 0;
}

int populate_tuples(tTuple * tuples, int arg_count, char *args[]) {
  int number_of_integers = arg_count - 1;
  int tupleIndex = 0;
  for (int i = 1; i < (number_of_integers); i+=2) {
      tTuple tuple;
      int x = atoi(args[i]);
      int y = atoi(args[i + 1]);
      if (!is_valid_x(x) || !is_valid_y(y)) {
        return 1;
      }
      tuple.x = x;
      tuple.y = y;
      tuples[tupleIndex] = tuple;
      tupleIndex++;
  }
  return 0;
}

void print_raw_board() {
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    printf("\nRow %d: ", i);
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      printf("%d ", board[i][j]);
    }
  }
}

void print_cell(int x, int y) {
  int cell = board[y][x];
  if (cell == CELL_IS_ALIVE) {
    printf("0");
  }
  else {
    printf(" ");
  }
}

void print_board() {
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    printf("\n");
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      print_cell(i, j);
    }
  }
}

int get_right_neighbor(int x, int y) {
  if (x + 1 < SCREEN_WIDTH) {
    return board[y][x + 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_left_neighbor(int x, int y) {
  if (x - 1 >= 0) {
    return board[y][x - 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_above_neighbor(int x, int y) {
  if (y - 1 >= 0) {
    return board[y - 1][x];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_below_neighbor(int x, int y) {
  if (y + 1 < SCREEN_HEIGHT) {
    return board[y + 1][x];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_above_right_neighbor(int x, int y) {
  if (y - 1 >= 0 && x + 1 < SCREEN_WIDTH) {
    return board[y - 1][x + 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_above_left_neighbor(int x, int y) {
  if (y - 1 >= 0 && x - 1 >= 0) {
    return board[y - 1][x - 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_below_right_neighbor(int x, int y) {
  if (y + 1 < SCREEN_HEIGHT && x + 1 < SCREEN_WIDTH) {
    return board[y + 1][x + 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

int get_below_left_neighbor(int x, int y) {
  if (y + 1 < SCREEN_HEIGHT && x - 1 >= 0) {
    return board[y + 1][x - 1];
  }
  else {
    return CELL_DOES_NOT_EXIST;
  }
}

tNeighbors get_neighbors(int x, int y) {
    tNeighbors neighbors;
    neighbors.right = get_right_neighbor(x, y);
    neighbors.left = get_left_neighbor(x, y);
    neighbors.above = get_above_neighbor(x, y);
    neighbors.below = get_below_neighbor(x, y);
    neighbors.below_left = get_below_left_neighbor(x, y);
    neighbors.below_right = get_below_right_neighbor(x, y);
    neighbors.above_right = get_above_right_neighbor(x, y);
    neighbors.above_left = get_above_left_neighbor(x, y);
    return neighbors;
}

int get_number_of_alive_neighbors(int x, int y) {
  tNeighbors neighbors = get_neighbors(x, y);
  int count = 0;
  if (neighbors.right == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.left == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.above == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.below == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.below_right == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.below_left == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.above_right == CELL_IS_ALIVE) {
    count ++;
  }
  if (neighbors.above_left == CELL_IS_ALIVE) {
    count ++;
  }
  return count;
}

void update_cell(int x, int y) {
  int cell = board[x][y];
  int number_of_alive_neighbors = get_number_of_alive_neighbors(x, y);
  if (cell == CELL_IS_ALIVE) {
    if (number_of_alive_neighbors == 0 || number_of_alive_neighbors == 1) {
      board[x][y] = CELL_IS_DEAD;
    }
    else if (number_of_alive_neighbors == 2 || number_of_alive_neighbors == 3) {
      // LIVE ON!
    }
    else if (number_of_alive_neighbors == 4) {
      board[x][y] = CELL_IS_DEAD;
    }
  }
  else {
    if (number_of_alive_neighbors == 3) {
      board[x][y] = CELL_IS_ALIVE;
    }
  }
}

void update_board() {
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      update_cell(i, j);
    }
  }
}

int at_least_one_cell_is_alive() {
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WIDTH; j++) {
      int cell = board[i][j];
      if (cell == CELL_IS_ALIVE) {
        return 1;
      }
    }
  }
  return 0;
}

int main( int arg_count, char *args[] )  {
    // Get args
    int number_of_integers = arg_count - 1;
    int number_of_tuples = number_of_integers / 2;
    if( number_of_integers % 2 != 0) {
        printf("There must be an even number of arguments\n");
        return 1;
    }

    // Parse/validate args
    tTuple *tuples = (tTuple*) malloc(sizeof(tTuple) * number_of_tuples);
    int success = populate_tuples(tuples, arg_count, args);
    if (success != FUNCTION_SUCCEEDED) {
      printf("One of your coordinates is out of range. The board size is %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
      return 1;
    }

    // Initialize board
    for (int i = 0; i < number_of_tuples; i++) {
        tTuple tuple = tuples[i];
        printf("(%d, %d)", tuple.x, tuple.y);
        board[tuple.y][tuple.x] = CELL_IS_ALIVE;
    }
    print_board();
    usleep(SECONDS_TO_SLEEP);
    while(1) {
      printf("\n===============================================================================================");
      if (!at_least_one_cell_is_alive()) {
        printf("\nNo cells are alive. Terminating program");
        return 0;
      }
      update_board();
      print_board();
      usleep(SECONDS_TO_SLEEP);
    }
    return 0;
}