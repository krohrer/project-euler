#include "pskel.inc"

void calculate_solution(void) {
  int diff = 0;
  for (int i = 1; i <= 100; ++i) {
    for (int k = i + 1; k <= 100; ++k) {
      diff += 2*i*k;
    }
  }
  printf("Solution = %d\n", diff);
}
