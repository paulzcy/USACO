/*
ID: paulzcy3
TASK: subset
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("subset.out");
  ifstream fin("subset.in");

  int n;
  fin >> n;
  if (n * (n + 1) / 2 % 2 != 0) {
    fout << "0\n";
    return 0;
  }

  long long ways[39 * 40 / 2 / 2 + 1];
  for (int i = 1; i <= n * (n + 1) / 2 / 2; ++i) {
    ways[i] = 0;
  }
  ways[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = n * (n + 1) / 2 / 2; j - i >= 0; --j) {
      ways[j] += ways[j - i];
    }
  }

  fout << ways[n * (n + 1) / 2 / 2] / 2 << '\n';
  return 0;
}
