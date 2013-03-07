#include "pskel.inc"

void calculate_solution(void) {
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
    strlen("eighteen") +
    strlen("nineteen");

  int s_X0_wo_10 =
    strlen("twenty") +
    strlen("thirty") +
    strlen("forty") +
    strlen("fifty") +
    strlen("sixty") +

    strlen("seventy") +
    strlen("eighty") +
    strlen("ninety");

  int s_1_99 =
    // one ... nine
    s_1_9 +
    // ten ... nineteen
    s_10_19 +
    // twenty twenty-one ... twenty-nine
    // ...
    // ninety ninety-one ... ninety-nine
    10*s_X0_wo_10 + 8*s_1_9;

  int s_X00 =
    // one hundred ... nine hundred
    s_1_9 +
    9*strlen("hundred");

  int s_1_1000 =
    // Every "X hundred" prefix appears 100 times
    100*s_X00 +
    //Skip "and" if < 100 and skip if last two digits 0
    9*99*strlen("and") +
    // All double digits for each hundred
    10*s_1_99 +
    // "one thousand"
    strlen("one") + strlen("thousand");

  printf("Solution = %d\n", s_1_1000);
}
