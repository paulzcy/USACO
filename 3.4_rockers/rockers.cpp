/*
ID: paulzcy3
TASK: rockers
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

int n, t, m;
int mm[21][21];  // mm[i][j]: If > 0, the minimal minutes used in the last disk
                 // when including i songs and j disks, so far.

int main() {
  ofstream fout("rockers.out");
  ifstream fin("rockers.in");

  fin >> n >> t >> m;

  for (int d = 0; d <= m; ++d) {
    mm[0][d] = 0;
    for (int s = 1; s <= n; ++s) {
      mm[s][d] = t + 1;
    }
  }

  // mm[s][d] = min(m[s][d],
  //                m[s - 1][d] + l,   m[s-1][d] + l <= t
  //                l)                 m[s-1][d-1] possible

  int songs = 0;
  for (int i = 1; i <= n; ++i) {
    int l;
    fin >> l;

    for (int s = i; s >= 1; --s) {
      for (int d = m; d >= 1; --d) {
        int minutes = mm[s - 1][d] + l;
        if (minutes <= t) {
          mm[s][d] = min(mm[s][d], minutes);
          songs = max(songs, s);
        }

        if (mm[s - 1][d - 1] <= t && l <= t) {
          mm[s][d] = min(mm[s][d], l);
          songs = max(songs, s);
        }
      }
    }
  }

  fout << songs << '\n';

  return 0;
}
