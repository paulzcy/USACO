/*
ID: paulzcy3
TASK: fence6
LANG: C++
*/
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr int MAX = 2147483647;

int main() {
  ofstream fout("fence6.out");
  ifstream fin("fence6.in");

  int n;
  struct Edge {
    int f;
    int t;
    int l;
  };
  Edge edges[100];
  struct Node {
    array<int8_t, 9> name{};
    int dist = MAX;
    vector<int> edges;
  };
  vector<Node> nodes;
  nodes.reserve(100);

  fin >> n;
  for (int i = 0; i < n; ++i) {
    int id;
    int l;
    int n1, n2;
    fin >> id >> l >> n1 >> n2;
    array<int8_t, 9> name1{}, name2{};
    int f = -1, t = -1;

    for (int j = 0; j < n1; ++j) {
      int p;
      fin >> p;
      name1[j] = p;
    }
    name1[n1] = id;
    sort(name1.begin(), name1.begin() + n1 + 1);

    for (int j = 0; j < n2; ++j) {
      int p;
      fin >> p;
      name2[j] = p;
    }
    name2[n2] = id;
    sort(name2.begin(), name2.begin() + n2 + 1);

    for (f = 0; f < nodes.size(); ++f) {
      if (nodes[f].name == name1) break;
    }
    if (f == nodes.size()) {
      nodes.emplace_back();
      Node& node = nodes.back();
      node.name = name1;
      node.edges.reserve(9);
    }
    nodes[f].edges.push_back(i);

    for (t = 0; t < nodes.size(); ++t) {
      if (nodes[t].name == name2) break;
    }
    if (t == nodes.size()) {
      nodes.emplace_back();
      Node& node = nodes.back();
      node.name = name2;
      node.edges.reserve(9);
    }
    nodes[t].edges.push_back(i);

    if (f > t) swap(f, t);
    edges[i] = Edge{f, t, l};
  }

  int min_loop = MAX;
  vector<int> heap;
  heap.reserve(nodes.size());

  for (int to_remove = 0; to_remove < n; ++to_remove) {
    for (Node& node : nodes) {
      node.dist = MAX;
    }

    heap.clear();
    heap.push_back(edges[to_remove].f);
    nodes[edges[to_remove].f].dist = 0;

    auto cmp = [&](int i, int j) { return nodes[i].dist > nodes[j].dist; };

    while (!heap.empty()) {
      int top = heap[0];
      if (top == edges[to_remove].t) {
        min_loop =
            min(min_loop, edges[to_remove].l + nodes[edges[to_remove].t].dist);
        break;
      }
      pop_heap(heap.begin(), heap.end(), cmp);
      heap.pop_back();

      for (int e : nodes[top].edges) {
        if (e == to_remove) continue;
        int t = edges[e].f ^ edges[e].t ^ top;
        int l = edges[e].l;

        if (nodes[top].dist + l < nodes[t].dist) {
          int i = 0;
          while (i < heap.size() && heap[i] != t) ++i;
          if (i == heap.size()) heap.push_back(t);
          nodes[t].dist = nodes[top].dist + l;
          push_heap(heap.begin(), heap.begin() + i + 1, cmp);
        }
      }
    }
  }

  fout << min_loop << '\n';

  return 0;
}
