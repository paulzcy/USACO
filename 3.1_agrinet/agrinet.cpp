/*
ID: paulzcy3
TASK: agrinet
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
int dist[100][100];
int d[100];
bool in[100];

int main() {
  ofstream fout("agrinet.out");
  ifstream fin("agrinet.in");

  fin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> dist[i][j];
    }
    d[i] = 2147483647;
    in[i] = false;
  }

  int sum = 0;
  in[0] = true;
  for (int i = 1; i < n; ++i) {
    d[i] = dist[0][i];
  }

  for (int i = 1; i < n; ++i) {
    int min_d = 2147483647;
    int min_j = 0;
    for (int j = 1; j < n; ++j) {
      if (in[j]) continue;
      if (d[j] < min_d) {
        min_d = d[j];
        min_j = j;
      }
    }
    in[min_j] = true;
    sum += min_d;

    for (int j = 1; j < n; ++j) {
      if (in[j]) continue;
      if (dist[min_j][j] < d[j]) {
        d[j] = dist[min_j][j];
      }
    }
  }
  fout << sum << '\n';

  return 0;
}
