#include "pskel.inc"

void calculate_solution(void) {
  for (int i = 1; i < 998; ++i) {
    for (int k = i + 1; k < 999; ++k) {
      int a = i;
      int b = k - a;
      int c = 1000 - b - a;
      if (a < b && b < c && a*a + b*b == c*c) {
	printf("a,b,c = %d,%d,%d\n", a,b,c);
	printf("Solution = %d\n", a*b*c);
      }
    }
  }
}
