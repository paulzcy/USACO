/*
ID: paulzcy3
TASK: holstein
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int v;
short need[25];
int g;
short provide[15][25];

bool found = false;

struct State {
  short has[25];
  char vitamin[15];
  char scoops;
};
State queue[1 << 15];

int main() {
  ofstream fout("holstein.out");
  ifstream fin("holstein.in");
  fin >> v;
  for (int i = 0; i < v; ++i) fin >> need[i];

  fin >> g;
  for (int i = 0; i < g; ++i) {
    for (int j = 0; j < v; ++j) {
      fin >> provide[i][j];
    }
  }

  queue[0].scoops = 0;
  for (int i = 0; i < v; ++i) queue[0].has[i] = 0;
  int head = 0;
  int tail = 1;

  while (true) {
    int next = (queue[head].scoops == 0)
                   ? 0
                   : (queue[head].vitamin[queue[head].scoops - 1] + 1);

    for (int i = next; i < g; ++i) {
      queue[tail] = queue[head];
      queue[tail].vitamin[queue[tail].scoops] = i;
      ++queue[tail].scoops;
      bool good = true;
      for (int j = 0; j < v; ++j) {
        queue[tail].has[j] = queue[head].has[j] + provide[i][j];
        if (queue[tail].has[j] < need[j]) good = false;
      }

      if (good) {
        fout << static_cast<int>(queue[tail].scoops);
        for (int k = 0; k < queue[tail].scoops; ++k) {
          fout << " " << static_cast<int>(queue[tail].vitamin[k]) + 1;
        }
        fout << '\n';
        return 0;
      }

      ++tail;
    }

    ++head;
  }
  return 0;
}
