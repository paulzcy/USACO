/*
ID: paulzcy3
TASK: kimbits
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

unsigned int kC[32][32];    // C(i, j)
unsigned int kSum[32][32];  // Number of length-i strings that has [0, j] '1's

int main() {
  ofstream fout("kimbits.out");
  ifstream fin("kimbits.in");

  int n, l;
  unsigned int ii;
  fin >> n >> l >> ii;

  kC[0][0] = 1;
  for (int i = 1; i < n; ++i) {
    kC[i][0] = 1;
    for (int j = 1; j <= i && j <= l; ++j) {
      kC[i][j] = kC[i - 1][j - 1] + ((j <= i - 1) ? kC[i - 1][j] : 0);
    }
  }

  for (int i = 0; i < n; ++i) {
    kSum[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      kSum[i][j] = kC[i][j] + kSum[i][j - 1];
    }
  }

  for (int e = n; e >= 1; --e) {
    // The number of strings whose len = e-1 and has <=`l` '1's.
    unsigned int num = kSum[e - 1][min(e - 1, l)];
    // If ii > num, this digit must be '1'.
    if (ii > num) {
      fout << '1';
      // Now we have one less '1' and `num` less strings to count.
      ii = ii - num;
      --l;
    } else {
      fout << '0';
    }
  }

  fout << '\n';

  return 0;
}
