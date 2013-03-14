#include "pskel.inc"

void calculate_solution(void) {
  unsigned N = 28123;
  unsigned ds[N];
  unsigned as[N];
  unsigned ac = 0;
  
  ds[0] = 0;
  for (unsigned i = 1; i <= N; ++i) {
    if (i < ds[i-1]) as[ac++] = i;
    for (unsigned k = 2*i; k <= N; k += i) {
      ds[k-1] += i;
    }
  }

  unsigned sum = 0;
  for (unsigned i = 1; i <= N; ++i) {
    bool na = true;
    for (unsigned x = 0; x < ac && na; ++x) {
      unsigned a = as[x];
      na = ! (a < i && (i - a) < ds[i-a-1]);
    }
    if (na) sum += i;
  }

  printf("Solution = %u\n", sum);
}
