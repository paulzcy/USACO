/*
ID: paulzcy3
TASK: ratios
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int t[3];
int m[3][3];

int main() {
  ofstream fout("ratios.out");
  ifstream fin("ratios.in");

  for (int i = 0; i < 3; ++i) {
    fin >> t[i];
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      fin >> m[i][j];
    }
  }

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 100; ++k) {
        if (i == 0 && j == 0 && k == 0) continue;

        int t2[3];
        for (int l = 0; l < 3; ++l) {
          t2[l] = i * m[0][l] + j * m[1][l] + k * m[2][l];
        }

        bool bad = false;
        int d = 0;
        for (int l = 0; l < 3; ++l) {
          if (t[l] == 0) {
            if (t2[l] != 0) {
              bad = true;
              break;
            }
          } else {
            if (t2[l] == 0 || t2[l] % t[l] != 0) {
              bad = true;
              break;
            }
            if (d == 0) {
              d = t2[l] / t[l];
            } else if (t2[l] / t[l] != d) {
              bad = true;
              break;
            }
          }
        }

        if (bad) continue;

        fout << i << ' ' << j << ' ' << k << ' ' << d << '\n';
        return 0;
      }
    }
  }
  fout << "NONE\n";

  return 0;
}
