#include "pskel.inc"

/*

We shall say that an n-digit number is pandigital if it makes use of
all the digits 1 to n exactly once; for example, the 5-digit number,
15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 x 186 = 7254,
containing multiplicand, multiplier, and product is 1 through 9
pandigital.

Find the sum of all products whose multiplicand/multiplier/product
identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to
only include it once in your sum.
*/


bool is_pandigital_fragment(unsigned n,
			    unsigned dmask_in,
			    unsigned *dmask_out,
			    unsigned *digits_out)
{
  *dmask_out = dmask_in;
  *digits_out = 0;
  for (unsigned rem = n; 0 < rem; rem /= 10) {
    unsigned d = rem % 10;
    unsigned dflag = 1 << d;
    if (0 < (*dmask_out & dflag)) return false;
    *dmask_out |= dflag;
    ++*digits_out;
  }
  *dmask_out |= dmask_in;
  return true;
}

int compare_unsigned(unsigned *u, unsigned *v) {
  return *u - *v;
}

void calculate_solution(void) {
  /* If two digits a & b have n and m digits respecitively, then the
     product p = a * b has at least n+m-1 digits, and n+m digits at
     most. */
  /* a goes up to 3 digits, b is always greater than a and terminates
     as soon as the product is greater than the greatest 9 digit
     number with different digits. */
  const unsigned zero_mask = 1;
  const unsigned all_digits_mask = 0x3FF; // 0b1111111110

  struct {
    unsigned count;
    unsigned capacity;
    unsigned *data;
  } products = { 0 };
  products.capacity = 10;
  products.data = malloc(products.capacity * sizeof(unsigned));

  for (unsigned a = 2; a <= 999; ++a) {
    unsigned a_dmask;
    unsigned a_digits;
    if ( ! is_pandigital_fragment(a, zero_mask, &a_dmask, &a_digits)) {
      continue; // Has zero in it.
    }

    // b is always greater than a, thus we never have duplicates
    for (unsigned b = a + 1; true; ++b) {
      unsigned b_dmask;
      unsigned b_digits;
      if ( ! is_pandigital_fragment(b, a_dmask, &b_dmask, &b_digits))
	continue;

      if (a_digits + b_digits + (a_digits + b_digits) < 9)
	continue; // Too few digits

      if (9 < a_digits + b_digits + (a_digits + b_digits - 1))
	break; // Too many digits, exit inner loop

      unsigned p = a * b;
      unsigned p_dmask;
      unsigned p_digits;
      if ( ! is_pandigital_fragment(p, b_dmask, &p_dmask, &p_digits))
	continue;

      if (9 < a_digits + b_digits + p_digits)
	break; // Too many digits, exit inner loop

      if (9 == a_digits + b_digits + p_digits &&
	  p_dmask == all_digits_mask) {
	if (products.capacity <= ++products.count) {
	  products.capacity *= 2;
	  products.data = realloc(products.data, sizeof(unsigned)*products.capacity);
	}
	products.data[products.count-1] = p;
      }
    }
  }

  qsort(products.data, products.count, sizeof(unsigned), (void*)&compare_unsigned);

  unsigned sum = 0;
  for (unsigned i = 0; i < products.count; ++i) {
    if (0 == i || products.data[i-1] != products.data[i]) {
      sum += products.data[i];
    }
  }
  printf("Solution = %d\n", sum);

  free(products.data);
}
