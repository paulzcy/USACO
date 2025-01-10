/*
ID: paulzcy3
TASK: barn1
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("barn1.out");
  ifstream fin("barn1.in");

  int m, s, c;
  int gap[200];

  int num_gap = 0;

  fin >> m >> s >> c;

  int cows[200];
  for (int i = 0; i < c; ++i) {
    fin >> cows[i];
  }
  sort(cows, cows + c);

  for (int i = 1; i < c; ++i) {
    if (cows[i] - cows[i - 1] > 1) {
      gap[num_gap] = cows[i] - cows[i - 1] - 1;
      ++num_gap;
    }
  }

  int covered = cows[c - 1] - cows[0] + 1;

  int to_use = min(m - 1, num_gap);
  nth_element(gap, gap + to_use, gap + num_gap, greater<int>());

  for (int i = 0; i < to_use; ++i) {
    covered -= gap[i];
  }
  fout << covered << '\n';

  return 0;
}
