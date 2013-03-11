#include <stdio.h>

int main(int argc, const char *argv[]) {
  int sum = 0;
  for (int i = 1; i < 1000; ++i) {
    if (i % 5 == 0 || i % 3 == 0) {
      sum += i;
    }
  }
  printf("Solution: %d\n", sum);
  return 0;
}
