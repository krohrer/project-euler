#include "pskel.inc"

const char* ones[9] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"
};

const char* teens[10] = {
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
};

const char* tens_wo_10[8] = {
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
};

void calculate_solution(void) {
  int sum = 0;
  for (int h = 0; h <= 9; ++h) {
    for (int i = 0; i <= 99; ++i) {
      if (h > 0) {
	sum += printf("%s hundred ", ones[h-1]) - 2;
	if (i > 0) {
	  sum += printf("and ") - 1;
	}
      }
      if (i > 0) {
	if (i < 10) {
	  sum += printf("%s", ones[i-1]);
	}
	else if (i < 20) {
	  sum += printf("%s", teens[i-10]);
	}
	else {
	  int t = i / 10;
	  int o = i % 10;
	  if (o > 0) {
	    sum += printf("%s-%s", tens_wo_10[t-2], ones[o-1]) - 1;
	  }
	  else {
	    sum += printf("%s", tens_wo_10[t-2]);
	  }
	}
      }
      puts("");
    }
  }
  sum += printf("one thousand") - 1;
  puts("\n");

  printf("Solution = %d\n", sum);
}
