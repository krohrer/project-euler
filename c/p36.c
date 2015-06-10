#include "pskel.inc"

bool is_binary_palindrome(unsigned num)
{
  unsigned x = num;
  unsigned x_rev = 0;

  while (0 < x) {
    unsigned d = x & 1;
    x >>= 1;
    x_rev <<= 1;
    x_rev |= d;
  }

  return x_rev == num;
}

bool is_decimal_palindrome(unsigned num)
{
  unsigned x = num;
  unsigned x_rev = 0;

  while (0 < x) {
    unsigned d = x % 10;
    x /= 10;
    x_rev *= 10;
    x_rev += d;
  }

  return x_rev == num;
}

void calculate_solution(void)
{
  unsigned N = 1000*1000;
  unsigned sum = 0;

  for (unsigned i = 1; i < N; ++i) {
    if (is_binary_palindrome(i) && is_decimal_palindrome(i)) {
      sum += i;
    }
  }

  printf("Solution = %d\n", sum);
}
