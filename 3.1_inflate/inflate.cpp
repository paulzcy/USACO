/*
ID: paulzcy3
TASK: inflate
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int max_p[10001];

int main() {
  ofstream fout("inflate.out");
  ifstream fin("inflate.in");

  int m, n;
  fin >> m >> n;
  for (int i = 0; i <= m; ++i) max_p[i] = 0;

  int p;
  int mi;
  fin >> p >> mi;
  for (int i = 1; i * mi <= m; ++i) {
    max_p[i * mi] = i * p;
  }

  int result = m / mi * p;

  for (int i = 1; i < n; ++i) {
    fin >> p >> mi;

    for (int j = mi; j <= m; ++j) {
      max_p[j] = max(max_p[j], max_p[j - mi] + p);
      result = max(result, max_p[j]);
    }
  }

  fout << result << '\n';
  return 0;
}
