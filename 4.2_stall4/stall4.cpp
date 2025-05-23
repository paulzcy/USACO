/*
ID: paulzcy3
TASK: stall4
LANG: C++
*/
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, m;
bool cap[200][200];
bool assign[200][200];
bool cow[200];
bool stall[200];

int main(int argc, char** argv) {
  ofstream fout("stall4.out");
  ifstream fin("stall4.in");

  fin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int s;
    fin >> s;
    while (s--) {
      int mm;
      fin >> mm;
      --mm;
      cap[i][mm] = true;
    }
  }

  int result = 0;

  struct Q {
    bool stall;
    int id;
    int from;
  };
  vector<Q> queue;
  queue.reserve(m + n);

  bool vc[200];
  bool vs[200];

  while (true) {
    queue.clear();
    for (int i = 0; i < n; ++i) {
      vc[i] = !cow[i];
      if (!cow[i]) queue.push_back({false, i, -1});
    }
    for (int i = 0; i < m; ++i) {
      vs[i] = false;
    }
    bool found = false;
    int head = 0;

    while (head != queue.size()) {
      Q top = queue[head];

      if (top.stall && !stall[top.id]) {
        found = true;
        break;
      }

      if (!top.stall) {
        for (int i = 0; i < m; ++i) {
          if (!vs[i] && cap[top.id][i] && !assign[top.id][i]) {
            queue.push_back({true, i, head});
            vs[i] = true;
          }
        }
      } else {
        for (int i = 0; i < n; ++i) {
          if (!vc[i] && cap[i][top.id] && assign[i][top.id]) {
            queue.push_back({false, i, head});
            vc[i] = true;
          }
        }
      }

      ++head;
    }

    if (!found) break;

    ++result;

    // relax.
    Q curr = queue[head];
    stall[curr.id] = true;
    while (curr.from != -1) {
      Q prev = queue[curr.from];
      if (curr.stall) {
        assign[prev.id][curr.id] = true;
      } else {
        assign[curr.id][prev.id] = false;
      }
      curr = prev;
    }
    cow[curr.id] = true;
  }

  fout << result << '\n';
  return 0;
}