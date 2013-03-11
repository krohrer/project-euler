#include "pskel.inc"

void calculate_solution(void) {
  bignat_t *p = bignat_set_unsigned(bignat_new(0), 1);
  bignat_t *t = bignat_new(0);
  bignat_t *f = bignat_new(0);

  for (unsigned i = 1; i <= 100; ++i) {
    bignat_set_unsigned(f, i);
    bignat_mult(t, p, f);
    bignat_swap(t, p);
  }

  bignat_print(p);

  unsigned nd = bignat_count_digits(p);
  unsigned sum = 0;
  for (unsigned i = 0; i < nd; ++i) {
    sum += bignat_get_digit(p, i);
  }
  printf("Solution = %u\n", sum);

  bignat_delete(p);
  bignat_delete(t);
  bignat_delete(f);
}
