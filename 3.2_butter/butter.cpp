/*
ID: paulzcy3
TASK: butter
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n, p, c;
struct Edge {
  int t;
  int dist;
};
Edge edges[800][800];
int num_edge[800];

int numcow[800];

struct Ele {
  int dist;
  int p;
};
Ele heap[800];
int heap_pos[800];  // -1: not in heap; -2: removed from heap.
int heap_size;

void PushUp(int pos) {
  while (pos != 0) {
    int parent = (pos - 1) / 2;

    if (heap[parent].dist <= heap[pos].dist) break;
    swap(heap[parent], heap[pos]);
    heap_pos[heap[parent].p] = parent;
    heap_pos[heap[pos].p] = pos;

    pos = parent;
  }
}
void PushHeap(Ele ele) {
  heap[heap_size] = ele;
  heap_pos[ele.p] = heap_size;
  PushUp(heap_size);

  ++heap_size;
}

void Heapify(int pos) {
  while (true) {
    int left = pos * 2 + 1;
    int right = pos * 2 + 2;
    int largest = pos;

    if (left < heap_size && heap[left].dist < heap[largest].dist) {
      largest = left;
    }
    if (right < heap_size && heap[right].dist < heap[largest].dist) {
      largest = right;
    }

    if (largest == pos) return;
    swap(heap[pos], heap[largest]);
    heap_pos[heap[largest].p] = largest;
    heap_pos[heap[pos].p] = pos;

    pos = largest;
  }
}
void MakeHeap() {
  for (int pos = (heap_size - 2) / 2; pos >= 0; --pos) {
    Heapify(pos);
  }
}
void PopHead() {
  heap_pos[heap[0].p] = -2;
  --heap_size;
  heap[0] = heap[heap_size];
  heap_pos[heap[0].p] = 0;
  Heapify(0);
}

int main() {
  ofstream fout("butter.out");
  ifstream fin("butter.in");

  fin >> n >> p >> c;
  for (int i = 0; i < n; ++i) {
    int cow;
    fin >> cow;
    ++numcow[cow - 1];
  }
  for (int i = 0; i < c; ++i) {
    int f, t, d;
    fin >> f >> t >> d;
    --f;
    --t;
    if (f == t) continue;
    edges[f][num_edge[f]].t = t;
    edges[f][num_edge[f]].dist = d;
    ++num_edge[f];
    edges[t][num_edge[t]].t = f;
    edges[t][num_edge[t]].dist = d;
    ++num_edge[t];
  }

  int min_d = 2147483647;

  for (int start = 0; start < p; ++start) {
    int sum = 0;
    int cows = numcow[start];

    for (int i = 0; i < p; ++i) {
      heap_pos[i] = -1;
    }
    heap_pos[start] = -2;

    heap_size = num_edge[start];
    for (int i = 0; i < num_edge[start]; ++i) {
      heap[i].p = edges[start][i].t;
      heap[i].dist = edges[start][i].dist;
      heap_pos[heap[i].p] = i;
    }
    MakeHeap();

    while (true) {
      assert(heap_size > 0);
      Ele head = heap[0];
      sum += numcow[head.p] * head.dist;
      cows += numcow[head.p];
      if (cows == n) break;

      // pop head.
      PopHead();

      // add new nodes.
      for (int i = 0; i < num_edge[head.p]; ++i) {
        int pos = heap_pos[edges[head.p][i].t];
        if (pos == -2) continue;

        if (pos == -1) {
          Ele next;
          next.p = edges[head.p][i].t;
          next.dist = head.dist + edges[head.p][i].dist;
          PushHeap(next);
          continue;
        }

        if (head.dist + edges[head.p][i].dist < heap[pos].dist) {
          heap[pos].dist = head.dist + edges[head.p][i].dist;

          PushUp(pos);
        }
      }
    }

    min_d = min(sum, min_d);
  }

  fout << min_d << '\n';

  return 0;
}
