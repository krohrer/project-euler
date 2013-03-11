#include <stdio.h>
#include <stdbool.h>

int main(int argc, const char *argv[]) {
  int digits[7];
  int product;
  int palin = 0;

  for (int i = 999; i > 99; --i) {
    for (int k = i; k > 99; --k) {
      product = i * k;
      int N = 0;
      for (int p = product; p > 0; p /= 10) {
	digits[N++] = (p % 10);
      }
      for (int i = 0; i*2 <= N; ++i) {
	if (digits[i] != digits[N-1-i]) {
	  goto not_palindrome;
	}
      }
      if (palin < product) palin = product;
    not_palindrome: continue;
    }
  }
 done:
  printf("Solution = %d", palin);
  return 0;
}
