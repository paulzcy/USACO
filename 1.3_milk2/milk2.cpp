/*
ID: paulzcy3
TASK: milk2
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("milk2.out");
  ifstream fin("milk2.in");

  int n;
  fin >> n;
  struct Milk {
    int start;
    int end;
  };
  Milk milk[5000];
  for (int i = 0; i < n; ++i) {
    fin >> milk[i].start >> milk[i].end;
  }

  sort(milk, milk + n, [](const Milk& l, const Milk& r) {
    if (l.start < r.start) return true;
    if (l.start > r.start) return false;
    return l.end < r.end;
  });

  int max_milk = milk[0].end - milk[0].start;
  int max_idle = 0;

  int current = 0;
  for (int i = 1; i < n; ++i) {
    if (milk[i].start > milk[current].end) {
      int idle = milk[i].start - milk[current].end;
      if (idle > max_idle) max_idle = idle;
      current = i;
      continue;
    }

    if (milk[i].end > milk[current].end) {
      milk[current].end = milk[i].end;
      max_milk = max(max_milk, milk[current].end - milk[current].start);
    }
  }

  fout << max_milk << " " << max_idle << "\n";

  return 0;
}
