/*
ID: paulzcy3
TASK: fence
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int fence[500][500];
int degree[500];
int result[1025];
int n = 0;

void Recurse(int i) {
  for (int j = 0; j < 500; ++j) {
    int& f = fence[min(i, j)][max(i, j)];
    if (f == 0) continue;
    --f;
    Recurse(j);
  }
  result[n] = i;
  ++n;
}

int main() {
  ofstream fout("fence.out");
  ifstream fin("fence.in");

  int f;
  fin >> f;
  for (int i = 0; i < f; ++i) {
    int x, y;
    fin >> x >> y;
    --x;
    --y;
    ++degree[x];
    ++degree[y];
    ++fence[min(x, y)][max(x, y)];
  }

  int start = -1;
  int min = -1;
  for (int i = 0; i < 500; ++i) {
    if (degree[i] > 0 && min == -1) min = i;
    if (degree[i] % 2 && start == -1) {
      start = i;
      break;
    }
  }
  if (start == -1) start = min;

  Recurse(start);

  for (int i = n - 1; i >= 0; --i) {
    fout << result[i] + 1 << '\n';
  }

  return 0;
}
