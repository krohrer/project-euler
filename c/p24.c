#include "pskel.inc"

void calculate_solution(void) {
  unsigned N = 10;
  unsigned fac[N];
  unsigned nums[N];

  unsigned p = 1;
  for (unsigned i = 1; i <= N; ++i) {
    p *= i;
    fac[N-i] = p;
    nums[i-1] = i-1;
  }

  unsigned ith = 1000*1000;
  --ith; // Zero based
  if (ith > fac[0]) die("Not nearly enough permutations");

  for (unsigned i = 1; i < N; ++i) {
    unsigned skip = ith / fac[i];
    ith %= fac[i];
    unsigned t = nums[i+skip-1];
    for (unsigned k = skip; k > 0; --k) {
      nums[i+k-1] = nums[i+k-2];
    }
    nums[i-1] = t;
  }
  printf("Solution = ");
  for (unsigned k = 0; k < N; ++k) {
    printf("%u", nums[k]);
  }
  printf("\n");
}
