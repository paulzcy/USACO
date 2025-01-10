/*
ID: paulzcy3
TASK: milk
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("milk.out");
  ifstream fin("milk.in");

  struct Farmer {
    int p;
    int a;
  };
  int n;
  int m;
  Farmer f[5000];

  fin >> n >> m;
  for (int i = 0; i < m; ++i) {
    fin >> f[i].p >> f[i].a;
  }

  sort(f, f + m, [](Farmer l, Farmer r) { return l.p < r.p; });

  int total = 0;
  for (int i = 0; i < m; ++i) {
    if (n <= f[i].a) {
      total += n * f[i].p;
      break;
    }
    n -= f[i].a;
    total += f[i].a * f[i].p;
  }

  fout << total << '\n';

  return 0;
}
