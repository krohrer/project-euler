#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

typedef int64_t num;

#define NUM(v) INT64_C(v)

void print_num(const char *name, num i) {
  printf("%s = %" PRIi64 "\n", name, i);
}

int main(int argc, const char *argv[]) {
  num N = 10001;

  {
    num *P = malloc(sizeof(num) * N);
    num lastP = 0;
    P[0] = 2;

    /* Iteratively check all numbers i in range [2,sqrt_N] for
       primeness. Add prime numbers to P. */
    num c = 0;
    printf("Calculating primes");
    for (num i = 2; lastP < N; ++i) {
      /* Check against all previous primes */
      for (num k = 0; k <= lastP; ++k) {
	if (++c % (10*1000*1000) == 0) { printf("."); fflush(stdout); }
	/* If divisible by prime, not prime by def. */
	if (i % P[k] == 0) goto not_prime;
     }
      /* Add number as it is prime. */
      P[++lastP] = i;
    not_prime: (void)0;
    }
    printf("DONE\n");

    print_num("Solution", P[N-1]);

    free(P);
  }

  return 0;
}
