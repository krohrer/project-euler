#include "pskel.inc"

void calculate_solution(void) {
  unsigned N = 1000;
  unsigned digits = N/3; // Approx.
  uint8_t D[digits];
  memset(D, 0, sizeof(uint8_t)*digits);

  D[0] = 2;
  for (unsigned i = 1; i < N; ++i) {
    unsigned C = 0;
    for (unsigned k = 0; k < digits; ++k) {
      unsigned S = 2*D[k] + C;
      D[k] = S % 10;
      C = S / 10;
    }
  }
  unsigned sum = 0;
  for (unsigned i = 0; i < digits; ++i) {
    sum += D[i];
  }
  printf("Solution = %u\n", sum);
}
