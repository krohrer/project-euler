#include "pskel.inc"

typedef struct {
  unsigned i;
  unsigned d;
} candidate_t;

int candidate_sort_fn(candidate_t *c1, candidate_t *c2) {
  return c1->d - c2->d;
}

void calculate_solution(void) {
  /*
    Let d(n) be defined as the sum of proper divisors of n (numbers
    less than n which divide evenly into n).  If d(a) = b and d(b) =
    a, where a <> b, then a and b are an amicable pair and each of a
    and b are called amicable numbers.

    For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11,
    20, 22, 44, 55 and 110; therefore d(220) = 284. The proper
    divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

    Evaluate the sum of all the amicable numbers under 10000.

    Solution sketch:

    ds[1..9999]
    for i = 1..9999:
      Find prime factors of i
      Calculate 


   */
  const unsigned N = 300;

  psieve *P = alloca(sizeof(psieve));
  psieve_init(P,N);

  candidate_t C[N];

  // Calculate number of divisors
  for (unsigned i = 2; i < N; ++i) {
    pfactors* F = alloca(sizeof(pfactors));
    pfactors_init(F, i, P);

    unsigned product;
    if (F->is_prime) {
      product = 2;
    }
    else {
      product = 1;
      for (unsigned k = 0; k < F->count; ++k) {
	product *= F->V[k] + 1;
      }
    }
    
    C[i-2].i = i;
    C[i-2].d = product;

    pfactors_destroy(F);
  }

  
  for (unsigned i = 0; i < N-2; ++i) {
    printf("d(%u) = %u\n", C[i].i, C[i].d);
  }

  qsort(C, N-2, sizeof(candidate_t), (int(*)(const void*, const void*))candidate_sort_fn);

  /*
  for (unsigned i = 0; i < N-2; ++i) {
    printf("d(%u) = %u\n", C[i].i, C[i].d);
  }
  */

  psieve_destroy(P);
}
