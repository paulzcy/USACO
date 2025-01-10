/*
ID: paulzcy3
TASK: wormhole
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
struct Wormhole {
  int x;
  int y;
};
Wormhole wh[12];
int p[12];
int sum = 0;

int RightOf(int w) {
  int min_w = -1;
  for (int i = 0; i < n; ++i) {
    if (i == w) continue;
    if (p[i] == -1) continue;
    if (wh[i].y == wh[w].y && wh[i].x > wh[w].x) {
      if (min_w == -1 || wh[i].x < wh[min_w].x) {
        min_w = i;
      }
    }
  }
  return min_w;
}

bool IsLoop(int w) {
  int next = w;
  while (true) {
    next = RightOf(next);
    if (next == -1) return false;
    next = p[next];
    if (next == w) return true;
  }
}

void Find(int d) {
  int l = 0;
  while (p[l] != -1) ++l;

  for (int r = l + 1; r < n; ++r) {
    if (p[r] != -1) continue;

    p[l] = r;
    p[r] = l;

    if (d + 2 == n) {
      for (int i = 0; i < n; ++i) {
        if (IsLoop(i)) {
          ++sum;
          break;
        }
      }
    } else {
      Find(d + 2);
    }

    p[r] = -1;
  }
  p[l] = -1;
}

int main() {
  ofstream fout("wormhole.out");
  ifstream fin("wormhole.in");

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> wh[i].x >> wh[i].y;
    p[i] = -1;
  }

  Find(0);
  fout << sum << '\n';

  return 0;
}
