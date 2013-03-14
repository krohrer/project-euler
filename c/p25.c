#include "pskel.inc"

void calculate_solution(void) {
  bignat_t *f1 = bignat_new(0);
  bignat_t *f2 = bignat_new(0);
  bignat_t *f3 = bignat_new(0);

  bignat_set_unsigned(f1, 1);
  bignat_set_unsigned(f2, 1);

  unsigned i = 2;
  do {
    bignat_add(f3, f1, f2);
    bignat_swap(f1, f2);
    bignat_swap(f2, f3);
    ++i;
  } while (bignat_count_digits(f2) < 1000);

  bignat_print(f2);

  printf("Solution = %u\n", i);

  bignat_delete(f1);
  bignat_delete(f2);
  bignat_delete(f3);
}
