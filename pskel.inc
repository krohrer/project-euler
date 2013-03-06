#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

typedef int64_t num;

#define NUM(v) INT64_C(v)

void print_num(const char *name, num i) {
  printf("%s = %" PRIi64 "\n", name, i);
}

void calculate_solution(void);

int main(int argc, const char *argv[]) {
  calculate_solution();
  return 0;
}
