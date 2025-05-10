/*
ID: paulzcy3
TASK: fence9
LANG: C++
*/
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long long m, n, p;

int main() {
  ofstream fout("fence9.out");
  ifstream fin("fence9.in");
  fin >> n >> m >> p;

  long long sum = 0;

  long long l = 1;
  long long r = n - 1;
  for (int y = 1; y < m; ++y) {
    // (0, 0), (n, m)
    // mx - ny + 0 = 0;
    {
      int ll = 0;
      int lr = max(n, 1ll);
      int result = m * l - n * y;
      if (result > 0) {
        lr = l;
      } else {
        ll = l;
      }
      while (lr - ll > 1) {
        int mi = (ll + lr) / 2;
        int result = m * mi - n * y;
        if (result > 0) {
          lr = mi;
        } else {
          ll = mi;
        }
      }
      l = lr;
    }

    // (n, m), (p, 0)
    // mx + (p - n)y - mp = 0
    {
      int rl = 0;
      int rr = max(p, n);
      int result = m * r + (p - n) * y - m * p;
      if (result < 0) {
        rl = r;
      } else {
        rr = r;
      }

      while (rr - rl > 1) {
        int mi = (rl + rr) / 2;
        int result = m * mi + (p - n) * y - m * p;
        if (result < 0) {
          rl = mi;
        } else {
          rr = mi;
        }
      }
      r = rl;
    }

    if (l <= r) {
      sum = sum + r - l + 1;
    }
  }

  fout << sum << '\n';

  return 0;
}
