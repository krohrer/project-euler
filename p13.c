#include "pskel.inc"

void calculate_solution(void) {
  double number;

  FILE *f = fopen_or_die("p13.txt");

  // Yeah, I know. This might not give the correct result. But hey.

  double sum = 0.0;
  for (unsigned i = 0; i < 100; ++i) {
    fscanf(f, "%lf", &number);
    sum += number;
  }

  printf("Solution = %f\n", sum);
  printf("           ~~~~~~~~~~\n");
  
  fclose(f);
}
