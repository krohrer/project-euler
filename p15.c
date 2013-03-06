#include "pskel.inc"

void calculate_solution(void) {
#define ROWS	20
#define COLS	20
  num g[ROWS+1][COLS+1];

  // Yeah, I was too lazy to find the combinatorial solution to this. problem?
  g[0][0] = 1;
  for (unsigned r = 1; r <= ROWS; ++r) {
    g[r][0] = g[r-1][0];
  }
  for (unsigned c = 1; c <= COLS; ++c) {
    g[0][c] = g[0][c-1];
  }
  for (unsigned r = 1; r <= ROWS; ++r) {
    for (unsigned c = 1; c <= COLS; ++c) {
      g[r][c] = g[r-1][c] + g[r][c-1];
    }
  }

  print_num("Solution", g[COLS][ROWS]);
}
