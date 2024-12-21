/*
ID: paulzcy3
TASK: beads
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("beads.out");
  ifstream fin("beads.in");

  int n;
  fin >> n;
  fin.ignore();

  char beads[350];
  for (int i = 0; i < n; ++i) {
    fin.get(beads[i]);
  }

  int max = 2;

  for (int b = 0; b < n; ++b) {
    char c = beads[b];
    int r = 1;
    for (; r < n; ++r) {
      int i = (b + r) % n;
      if (beads[i] == 'w') continue;
      if (c == 'w') {
        c = beads[i];
        continue;
      }
      if (c != beads[i]) break;
    }
    if (r == n) {
      max = n;
      break;
    }
    --r;

    c = beads[(b + n - 1) % n];
    int l = n - 2;
    for (; l > r; --l) {
      int i = (b + l) % n;
      if (beads[i] == 'w') continue;
      if (c == 'w') {
        c = beads[i];
        continue;
      }
      if (c != beads[i]) break;
    }
    ++l;

    int beads = r + 1 + (n - l);
    if (beads > max) max = beads;
  }

  fout << max << "\n";
  return 0;
}
