/*
ID: paulzcy3
TASK: spin
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bitset<360> open[5];
int speed[5];
int at[5];

int main() {
  ofstream fout("spin.out");
  ifstream fin("spin.in");

  for (int i = 0; i < 5; ++i) {
    fin >> speed[i];
    at[i] = 0;

    int n;
    fin >> n;
    for (int j = 0; j < n; ++j) {
      int s, e;
      fin >> s >> e;
      for (int k = 0; k <= e; ++k) {
        open[i].set((s + k) % 360);
      }
    }
  }
  for (int now = 0;; ++now) {
    for (int d = 0; d < 360; ++d) {
      bool all = true;
      for (int i = 0; i < 5; ++i) {
        if (!open[i].test((d + 360 - at[i]) % 360)) {
          all = false;
          break;
        }
      }
      if (all) {
        fout << now << '\n';
        return 0;
      }
    }

    bool all = true;
    for (int i = 0; i < 5; ++i) {
      at[i] = (at[i] + speed[i]) % 360;
      if (at[i] != 0) all = false;
    }
    if (all) {
      fout << "none\n";
      break;
    }
  };

  return 0;
}
