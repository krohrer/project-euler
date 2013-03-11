#include "pskel.inc"

/*
1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
*/

void calculate_solution(void) {
  int sunday_firsts = 0;
  int day = 0;
  for (int year = 1900; year <= 2000; ++year) {
    for (int month = 1; month <= 12; ++month) {
      day %= 7;
      if (year >= 1901) sunday_firsts += (day == 6 ? 1 : 0);
      switch (month) {
      case 1: case 3: case 5: case 7: case 8: case 10: case 12: day += 31; break;
      case 4: case 6: case 9: case 11: day += 30; break;
      case 2:
	day += 28;
	if (year % 4 == 0) {
	  day += 1;
	}
	if (year % 100 == 0) {
	  day -= 1;
	}
	if (year % 400 == 0) {
	  day += 1;
	}
      }
    }
  }
  printf("Solution = %d\n", sunday_firsts);
}
