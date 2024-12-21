/*
ID: paulzcy3
TASK: friday
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("friday.out");
  ifstream fin("friday.in");

  int n;
  fin >> n;

  int days[7] = {0, 0, 0, 0, 0, 0, 0};  // 0 -> Sat

  const int days_per_month[] = {31 /* Dec */, 31, 0,  31, 30, 31,
                                30,           31, 31, 30, 31, 30};

  int weekday = 4; /* Dec 13, 1989 Wed*/
  for (int i = 0; i < n; ++i) {
    for (int m = 0; m < 12; ++m) {
      if (m != 2) {
        weekday = (weekday + days_per_month[m]) % 7;
      } else {
        int year = 1900 + i;
        bool leap = (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
        weekday = (weekday + (leap ? 29 : 28)) % 7;
      }
      ++days[weekday];
    }
  }
  fout << days[0];
  for (int i = 1; i < 7; ++i) fout << " " << days[i];
  fout << "\n";

  return 0;
}
