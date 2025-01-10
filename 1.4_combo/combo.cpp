/*
ID: paulzcy3
TASK: combo
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int cov(int l, int r, int n) {
  int dist = min(min(abs(l - r), l + n - r), r + n - l);
  if (dist < 5) {
    return 5 - dist;
  } else {
    return 0;
  }
}

int main() {
  ofstream fout("combo.out");
  ifstream fin("combo.in");

  int n;
  int a, b, c, x, y, z;
  fin >> n >> a >> b >> c >> x >> y >> z;

  if (n <= 5) {
    fout << n * n * n << '\n';
    return 0;
  }

  fout << 5 * 5 * 5 + 5 * 5 * 5 - cov(a, x, n) * cov(b, y, n) * cov(c, z, n)
       << '\n';

  return 0;
}
