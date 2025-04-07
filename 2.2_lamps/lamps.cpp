/*
ID: paulzcy3
TASK: lamps
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("lamps.out");
  ifstream fin("lamps.in");

  int n;
  int c;
  fin >> n >> c;

  struct Lamp {
    bool pos;
    bool on[6];
  };
  Lamp lamps[16];
  for (int i = 0; i < 16; ++i) lamps[i].pos = false;

  for (int a1 = 0; a1 <= 1; ++a1) {
    for (int a2 = 0; a2 <= 1; ++a2) {
      for (int a3 = 0; a3 <= 1; ++a3) {
        for (int a4 = 0; a4 <= 1; ++a4) {
          if (a1 + a2 + a3 + a4 > c) continue;
          if ((c - a1 - a2 - a3 - a4) % 2 != 0) continue;

          int e = a1 + (a2 << 1) + (a3 << 2) + (a4 << 3);
          lamps[e].pos = true;
          for (int i = 0; i < 6; ++i) lamps[e].on[i] = true;

          if (a1) {
            for (int i = 0; i < 6; ++i) lamps[e].on[i] = !lamps[e].on[i];
          }
          if (a2) {
            lamps[e].on[0] = !lamps[e].on[0];
            lamps[e].on[2] = !lamps[e].on[2];
            lamps[e].on[4] = !lamps[e].on[4];
          }
          if (a3) {
            lamps[e].on[1] = !lamps[e].on[1];
            lamps[e].on[3] = !lamps[e].on[3];
            lamps[e].on[5] = !lamps[e].on[5];
          }
          if (a4) {
            lamps[e].on[0] = !lamps[e].on[0];
            lamps[e].on[3] = !lamps[e].on[3];
          }
        }
      }
    }
  }

  while (true) {
    int l;
    fin >> l;
    if (l == -1) break;
    for (int i = 0; i < 16; ++i) {
      if (lamps[i].pos && !lamps[i].on[(l - 1) % 6]) lamps[i].pos = false;
    }
  }
  while (true) {
    int l;
    fin >> l;
    if (l == -1) break;
    for (int i = 0; i < 16; ++i) {
      if (lamps[i].pos && lamps[i].on[(l - 1) % 6]) lamps[i].pos = false;
    }
  }

  sort(lamps, lamps + 16, [](Lamp l, Lamp r) {
    if (l.pos > r.pos) {
      return true;
    }
    if (l.pos < r.pos) {
      return false;
    }
    for (int i = 0; i < 6; ++i) {
      if (l.on[i] < r.on[i]) return true;
      if (l.on[i] > r.on[i]) return false;
    }
    return false;
  });

  int num_out;
  for (num_out = 0; num_out < 16 && lamps[num_out].pos; ++num_out) {
    for (int i = 0; i < n / 6; ++i) {
      for (int j = 0; j < 6; ++j) {
        fout << static_cast<char>('0' + lamps[num_out].on[j]);
      }
    }
    for (int j = 0; j < n % 6; ++j) {
      fout << static_cast<char>('0' + lamps[num_out].on[j]);
    }
    fout << '\n';
  }
  if (!num_out) fout << "IMPOSSIBLE\n";

  return 0;
}
