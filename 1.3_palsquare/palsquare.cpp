/*
ID: paulzcy3
TASK: palsquare
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
  ofstream fout("palsquare.out");
  ifstream fin("palsquare.in");

  int base;
  fin >> base;
  for (int i = 1; i <= 300; ++i) {
    Num n2 = ToNum(i * i, base);
    bool pal = true;
    for (int j = 0; j * 2 < n2.len; ++j) {
      if (n2.d[j] != n2.d[n2.len - j]) {
        pal = false;
        break;
      }
    }
    if (!pal) continue;

    Num n = ToNum(i, base);

    for (int l = n.len; l >= 0; --l) {
      fout << static_cast<char>((n.d[l] < 10) ? ('0' + n.d[l])
                                              : ('A' + (n.d[l] - 10)));
    }
    fout << ' ';
    for (int l = n2.len; l >= 0; --l) {
      fout << static_cast<char>((n2.d[l] < 10) ? ('0' + n2.d[l])
                                               : ('A' + (n2.d[l] - 10)));
    }
    fout << '\n';
  }

  return 0;
}
