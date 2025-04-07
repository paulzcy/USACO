/*
ID: paulzcy3
TASK: money
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long long ways[10001];

int main() {
  ofstream fout("money.out");
  ifstream fin("money.in");

  int v;
  int n;
  int vs[25];

  fin >> v >> n;
  for (int i = 0; i < v; ++i) {
    fin >> vs[i];
  }
  ways[0] = 1;
  for (int i = 1; i <= n; ++i) {
    ways[i] = 0;
  }

  for (int c = 0; c < v; c++) {
    for (int i = vs[c]; i <= n; ++i) {
      ways[i] += ways[i - vs[c]];
    }
  }
  fout << ways[n] << '\n';

  return 0;
}
