/*
ID: paulzcy3
TASK: ariprog
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("ariprog.out");
  ifstream fin("ariprog.in");

  int n, m;
  fin >> n >> m;

  bool bisq[250 * 250 * 2 + 1];

  for (int i = 0; i <= m * m * 2; ++i) {
    bisq[i] = false;
  }

  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= m; ++j) {
      bisq[i * i + j * j] = true;
    }
  }

  bool any = false;

  for (int b = 1; b <= 2 * m * m / (n - 1); ++b) {
    for (int a = 0; a + (n - 1) * b <= 2 * m * m; ++a) {
      bool is_ap = true;
      for (int i = 0; i < n; ++i) {
        if (!bisq[a + i * b]) {
          is_ap = false;
          break;
        }
      }
      if (is_ap) {
        fout << a << ' ' << b << '\n';
        any = true;
      }
    }
  }

  if (!any) fout << "NONE\n";

  return 0;
}
