/*
ID: paulzcy3
TASK: range
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int num[250][250];
int sizes[251];

int main() {
  ofstream fout("range.out");
  ifstream fin("range.in");

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin.ignore();
    char c;
    fin >> c;
    num[i][0] = c == '1';

    for (int j = 1; j < n; ++j) {
      fin >> c;
      if (c == '0') {
        num[i][j] = 0;
        continue;
      }

      num[i][j] = num[i][j - 1] + 1;

      int min_num = num[i][j];

      int s = 2;
      for (; i - s + 1 >= 0; ++s) {
        min_num = min(min_num, num[i - s + 1][j]);
        if (min_num < s) break;
      }

      for (int k = 2; k < s; ++k) {
        ++sizes[k];
      }
    }
  }

  for (int i = 2; i <= n && sizes[i] > 0; ++i) {
    fout << i << ' ' << sizes[i] << '\n';
  }

  return 0;
}
