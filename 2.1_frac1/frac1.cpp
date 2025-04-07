/*
ID: paulzcy3
TASK: frac1
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Frac {
  int x;
  int y;
};
Frac F(int x, int y) {
  Frac f;
  f.x = x;
  f.y = y;
  return f;
}
int Comp(Frac l, Frac r) { return l.x * r.y - l.y * r.x; }

int main() {
  ofstream fout("frac1.out");
  ifstream fin("frac1.in");

  Frac fracs[159 * 160 / 2 + 2];

  int n;
  fin >> n;

  int nf = 2;
  fracs[0] = F(0, 1);
  fracs[1] = F(1, 1);

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      fracs[nf] = F(j, i);
      ++nf;
    }
  }
  stable_sort(fracs, fracs + nf, [](Frac l, Frac r) { return Comp(l, r) < 0; });

  fout << fracs[0].x << '/' << fracs[0].y << '\n';
  for (int i = 1; i < nf; ++i) {
    if (Comp(fracs[i], fracs[i - 1]) != 0) {
      fout << fracs[i].x << '/' << fracs[i].y << '\n';
    }
  }

  return 0;
}
