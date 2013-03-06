#include "pskel.inc"

/*--------------------------------------------------------------------------*/

unsigned triangle(unsigned i) {
  return i*(i-1)/2;
}

void calculate_solution(void) {
  unsigned T = 500;
  psieve *S = alloca(sizeof(psieve));
  psieve_init(S, 10000);

  pfactors *F1 = alloca(sizeof(pfactors));
  pfactors *F2 = alloca(sizeof(pfactors));

  unsigned i = 3;
  pfactors_init(F2, i++, S);

  unsigned product = 0;
  for (; product <= T; ++i) {
    //F2 is already initialized for i-1
    pfactors_init(F1, i, S);

    product = F1->V[0] + F2->V[0];
    unsigned k = 1;
    for (k = 1; k < F2->count; ++k) {
      product *= F1->V[k] + F2->V[k] + 1;
    }
    for (; k < F1->count; ++k) {
      product *= F1->V[k] + 1;
    }
    if (F1->is_prime || F2->is_prime) {
      product *= 2;
    }

    if (product > T) {
      printf("Product = %u, i = %u\n", product, i);
      pfactors_dump(F1, S);
      pfactors_dump(F2, S);
    }

    pfactors_destroy(F2);
    memcpy(F2, F1, sizeof(pfactors));
  }
  --i;

  pfactors_destroy(F2);
  psieve_destroy(S);

  printf("Solution = %d\n", triangle(i));
}
