#include "pskel.inc"

const char *zero =
  "zero";

const char *hundred =
  "hundred";

const char *thousand =
  "thousand";

const char *million =
  "million";

const char *ones[9] = {
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

const char *teens[10] = {
  "ten",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eightteen",
  "nineteen"
};

const char *tens[9] = {
  "ten",
  "twenty",
  "thirty",
  "fourty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety",
};

void calculate_solution(void) {
  int s_0 =
    strlen("zero");

  int s_1_9 =
    strlen("one") +
    strlen("two") + 
    strlen("three") +
    strlen("four") +
    strlen("five") +
    strlen("six") +
    strlen("seven") +
    strlen("eight") +
    strlen("nine");

  int s_10_19 =
    strlen("ten") +
    strlen("eleven") +
    strlen("twelve") +
    strlen("thirteen") +
    strlen("fourteen") +
    strlen("fifteen") +
    strlen("sixteen") +
    strlen("seventeen") +
    strlen("eightteen") +
    strlen("nineteen");

  int s_X0_wo_10 =
    strlen("twenty") +
    strlen("thirty") +
    strlen("fourty") +
    strlen("fifty") +
    strlen("sixty") +
    strlen("seventy") +
    strlen("eighty") +
    strlen("ninety");

  int s_1_99 =
    s_1_9 +
    s_10_19 +
    10 * s_X0_wo_10 + 8 * s_1_9;

  int s_X00 =
    s_1_9 +
    strlen("hundred");

  int s_1_999 =
    100 * s_X00
}
