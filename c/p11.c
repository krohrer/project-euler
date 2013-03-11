#include "pskel.inc"

void calculate_solution(void) {
  int R = 20;
  int C = 20;
  int g[24][24] = {0};

  FILE *f = fopen("p11.txt", "r");
  if (f == NULL) die("Could not open file.");
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      if (fscanf(f, "%d", &g[r][c]) != 1) die("Invalid input");
    }
  }
  fclose(f);

  int max = 0;
  int p;

  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      p  = g[r  ][c];
      p *= g[r+1][c];
      p *= g[r+2][c];
      p *= g[r+3][c];
      if (p > max) max = p;

      p  = g[r][c  ];
      p *= g[r][c+1];
      p *= g[r][c+2];
      p *= g[r][c+3];
      if (p > max) max = p;

      p  = g[r  ][c  ];
      p *= g[r+1][c+1];
      p *= g[r+2][c+2];
      p *= g[r+3][c+3];
      if (p > max) max = p;

      p  = g[r  ][c+3];
      p *= g[r+1][c+2];
      p *= g[r+2][c+1];
      p *= g[r+3][c  ];
      if (p > max) max = p;
    }
  }
  printf("Solution = %d\n", max);
}
