/*
ID: paulzcy3
TASK: ditch
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int cap[200][200];
int flow[200][200];
bool visited[200];
struct Q {
  int node;
  int parent;
  int flow;
  bool positive;
};
Q queue[200];
int head, tail;

int main(int argc, char** argv) {
  ofstream fout("ditch.out");
  ifstream fin("ditch.in");

  fin >> n >> m;

  while (n--) {
    int s, e, c;
    fin >> s >> e >> c;
    cap[s - 1][e - 1] += c;
  }

  int result = 0;

  while (true) {
    bool found = false;
    for (int i = 0; i < m; ++i) visited[i] = false;

    visited[0] = true;
    queue[0] = {0, -1, 2147483647, true};
    head = 0;
    tail = 1;

    while (head != tail) {
      Q top = queue[head];

      if (flow[top.node][m - 1] < cap[top.node][m - 1]) {
        found = true;
        queue[tail] = {
            m - 1, head,
            min(top.flow, cap[top.node][m - 1] - flow[top.node][m - 1]), true};
        break;
      }

      for (int i = 0; i < m; ++i) {
        if (visited[i]) continue;
        if (flow[top.node][i] < cap[top.node][i]) {
          queue[tail] = {i, head,
                         min(top.flow, cap[top.node][i] - flow[top.node][i]),
                         true};
          ++tail;
          visited[i] = true;
        } else if (flow[i][top.node] > 0) {
          queue[tail] = {i, head, min(top.flow, flow[i][top.node]), false};
          ++tail;
          visited[i] = true;
        }
      }

      ++head;
    }

    if (!found) break;

    int flow_inc = queue[tail].flow;
    result += flow_inc;
    // relax.

    Q curr = queue[tail];
    while (curr.parent != -1) {
      Q prev = queue[curr.parent];

      if (curr.positive) {
        flow[prev.node][curr.node] += flow_inc;
      } else {
        flow[curr.node][prev.node] -= flow_inc;
      }
      curr = prev;
    }
  }

  fout << result << '\n';

  return 0;
}
