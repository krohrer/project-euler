#include "pskel.inc"

void calculate_solution(void) {
  num N = 2*1000*1000;

  {
    // P[i] : is i possibly prime?
    size_t size = sizeof(bool) * N;
    bool *P = malloc(size);
    num sum = 0;
    memset(P, true, size);

    for (num i = 2; i < N; ++i) {
      if (P[i]) {
	// Mark multiples as not prime
	for (num k = 2*i; k < N; k += i) {
	  P[k] = false;
	}
      }
    }

    for (num i = 2; i < N; ++i) {
      if (P[i]) {
	sum += i;
      }
    }

    print_num("Solution", sum);

    free(P);
  }
}
