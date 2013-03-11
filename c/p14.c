#include "pskel.inc"

void calculate_solution(void) {
  unsigned N = 1000*1000;
  size_t size = sizeof(unsigned) * N;
  unsigned *L = malloc(sizeof(unsigned) * N);
  memset(L, 0, size);

  unsigned max_l = 0;
  unsigned max_i = 0;

  L[0] = 1;
  for (unsigned i = 1; i <= N; ++i) {
    unsigned l = 1;
    unsigned s = i;
    while (s != 1) {
      if (s % 2 == 0) s /= 2; else s = 3*s + 1;
      if (s <= N && L[s-1] > 0) {
	l += L[s-1];
	break;
      }
      ++l;
    }
    L[i-1] = l;

    if (l > max_l) {
      max_l = l;
      max_i = i;
    }
  }
  printf("Solution: collatz(%u) = %u\n", max_i, max_l);
}
