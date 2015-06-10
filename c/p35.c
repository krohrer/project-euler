#include "pskel.inc"

typedef enum {
  MAYBE = 0,
  YES = 1,
  NO = -1
} ternary;

void digits_from_int(uint8_t digits[], unsigned d, unsigned num)
{
  for (unsigned k = 0; k < d; ++k) {
    digits[k] = num % 10;
    num /= 10;
  }
}

unsigned digits_to_int(uint8_t digits[], unsigned d)
{
  unsigned num = 0;
  for (unsigned k = 1; k <= d; ++k) {
    num = 10*num + digits[d-k];
  }
  return num;
}

void digits_shift(uint8_t digits[], unsigned d)
{
  uint8_t tmp = digits[0];
  for (unsigned k = 1; k < d; ++k) {
    digits[k-1] = digits[k];
  }
  digits[d-1] = tmp;
}

void calculate_solution(void)
{
  unsigned D = 6;
  unsigned N = 1000*1000;
  uint8_t digits[D];

  psieve* S = alloca(sizeof(psieve));
  psieve_init(S, N);

  int8_t* lookup = malloc(sizeof(int8_t) * N);
  for (unsigned i = 2; i < N; ++i) {
    lookup[i] = psieve_contains(S, i) ? MAYBE : NO;
  }
  
  unsigned d = 1;
  unsigned n = 10;

  unsigned count = 0;

  for (unsigned i = 2; i < N; ++i) {
    if (i == n) {
      n *= 10;
      ++d;
    }
    if (lookup[i] == YES) {
      ++count;
    }
    else if (lookup[i] == MAYBE) {
      bool is_circular = true;
      digits_from_int(digits, d, i);
      for (unsigned k = 1; k < d; ++k) {
    	digits_shift(digits, d);
    	int j = digits_to_int(digits, d);
    	if (lookup[j] == NO) {
    	  is_circular = false;
    	}
    	else if (lookup[j] == YES) {
    	  break;
    	}
      }
      if (is_circular) {
    	lookup[i] = YES;
    	++count;
      }
      else {
    	lookup[i] = NO;
      }
    }
  }

  printf("Solution = %d\n", count);

  psieve_destroy(S);
}
