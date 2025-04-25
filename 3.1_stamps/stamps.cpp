/*
ID: paulzcy3
TASK: stamps
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int min_c[10001];

int main() {
  ofstream fout("stamps.out");
  ifstream fin("stamps.in");

  int k, n;
  fin >> k >> n;

  int stamp[50];
  for (int i = 0; i < n; ++i) fin >> stamp[i];

  min_c[0] = 0;
  int cont = 1;

  for (;; ++cont) {
    min_c[cont % 10001] = 2147483647;
    for (int i = 0; i < n; ++i) {
      if (cont >= stamp[i]) {
        min_c[cont % 10001] = min(min_c[cont % 10001],
                                  min_c[(cont + 10001 - stamp[i]) % 10001] + 1);
      }
    }
    if (min_c[cont % 10001] > k) break;
  }

  fout << cont - 1 << '\n';

  return 0;
}
