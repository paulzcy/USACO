/*
ID: paulzcy3
TASK: hamming
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n, b, d;

int dist[256];
int words[64];

bool Dfs(int depth) {
  for (int i = words[depth - 1] + 1; i < (1 << b); ++i) {
    bool bad = false;
    for (int j = 0; j < depth; ++j) {
      if (dist[i ^ words[j]] < d) {
        bad = true;
        break;
      }
    }
    if (bad) continue;
    words[depth] = i;
    if (depth == n - 1) return true;
    if (Dfs(depth + 1)) return true;
  }
  return false;
}

int main() {
  ofstream fout("hamming.out");
  ifstream fin("hamming.in");

  fin >> n >> b >> d;
  if (n == 1) {
    fout << "0\n";
    return 0;
  }

  for (int i = 0; i < (1 << b); ++i) {
    int cnt = 0;
    for (int j = i; j > 0; j /= 2) cnt += j % 2;
    dist[i] = cnt;
  }
  words[0] = 0;
  Dfs(1);

  for (int i = 0; i < n; ++i) {
    if (i % 10 != 0) {
      fout << ' ';
    } else if (i > 0) {
      fout << '\n';
    }
    fout << words[i];
  }
  fout << '\n';

  return 0;
}
