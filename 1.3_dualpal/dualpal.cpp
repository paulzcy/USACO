/*
ID: paulzcy3
TASK: dualpal
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Num {
  int len;
  int d[17];
};

Num ToNum(int i, int b) {
  Num r;
  r.len = 0;

  while (true) {
    r.d[r.len] = i % b;
    i /= b;
    if (i == 0) break;
    ++r.len;
  }

  return r;
}
int main() {
  ofstream fout("dualpal.out");
  ifstream fin("dualpal.in");

  int n;
  int s;
  fin >> n >> s;

  while (n > 0) {
    ++s;

    int pals = 0;
    for (int b = 2; b <= 10 && pals < 2; ++b) {
      Num n = ToNum(s, b);

      bool pal = true;
      for (int j = 0; j * 2 < n.len; ++j) {
        if (n.d[j] != n.d[n.len - j]) {
          pal = false;
          break;
        }
      }
      if (pal) ++pals;
    }
    if (pals < 2) continue;

    fout << s << '\n';
    --n;
  }

  return 0;
}
