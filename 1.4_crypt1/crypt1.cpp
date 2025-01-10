/*
ID: paulzcy3
TASK: crypt1
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("crypt1.out");
  ifstream fin("crypt1.in");

  int n;
  int di[10];
  bool has[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> di[i];
    has[di[i]] = true;
  }

  int num = 0;

  for (int ia = 0; ia < n; ++ia) {
    int a = di[ia];
    if (a == 0) continue;

    for (int ib = 0; ib < n; ++ib) {
      int b = di[ib];
      for (int ic = 0; ic < n; ++ic) {
        int c = di[ic];

        int x = a * 100 + b * 10 + c;

        for (int id = 0; id < n; ++id) {
          int d = di[id];
          if (d == 0) continue;
          if (d * x > 999) continue;

          auto in = [&](int k) {
            while (k > 0) {
              if (!has[k % 10]) return false;
              k /= 10;
            }
            return true;
          };
          if (!in(d * x)) continue;

          for (int ie = 0; ie < n; ++ie) {
            int e = di[ie];
            if (e == 0) continue;
            if (e * x > 999) continue;
            if (!in(e * x)) continue;

            if (d * x * 10 + e * x > 9999) continue;
            if (!in(d * x * 10 + e * x)) continue;

            ++num;
          }
        }
      }
    }
  }

  fout << num << '\n';

  return 0;
}
