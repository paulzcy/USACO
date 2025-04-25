/*
ID: paulzcy3
TASK: humble
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Ele {
  int num;
  int used;
};

int p[100];
Ele heap[100000];

int main() {
  ofstream fout("humble.out");
  ifstream fin("humble.in");

  int k;
  int n;
  fin >> k >> n;
  for (int i = 0; i < k; ++i) {
    fin >> p[i];
  }
  std::sort(p, p + k);

  int heap_size = 1;
  heap[0].num = p[0];
  heap[0].used = 0;

  auto cmp = [](Ele l, Ele r) { return l.num > r.num; };

  for (; n > 1; --n) {
    Ele top = heap[0];
    pop_heap(heap, heap + heap_size, cmp);
    --heap_size;

    if (2147483647 / top.num >= p[top.used]) {
      heap[heap_size].num = top.num * p[top.used];
      heap[heap_size].used = top.used;
      ++heap_size;
      push_heap(heap, heap + heap_size, cmp);
    }

    if (top.used < k - 1 &&
        2147483647 / (top.num / p[top.used]) >= p[top.used + 1]) {
      heap[heap_size].num = top.num / p[top.used] * p[top.used + 1];
      heap[heap_size].used = top.used + 1;
      ++heap_size;
      push_heap(heap, heap + heap_size, cmp);
    }
  }
  fout << heap[0].num << '\n';

  return 0;
}
