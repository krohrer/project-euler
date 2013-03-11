#include <stdio.h>

int main(int argc, const char *argv[]) {
  // 53 bits should be enough
  unsigned s1 = 1;
  unsigned s2 = 2;
  double sum = 0;

  while (s1 < 4*1000*1000) {
    unsigned s = s2 + s1;
    if (s1 % 2 == 0) {
      sum += s1;
    }
    s1 = s2;
    s2 = s;
  }
  printf("Solution: %.0f\n", sum);
  return 0;
}
