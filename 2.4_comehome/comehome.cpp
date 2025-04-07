/*
ID: paulzcy3
TASK: comehome
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int ToI(char c) {
  if ('a' <= c && c <= 'z') return c - 'a';
  return c - 'A' + 26;
}

int main() {
  ofstream fout("comehome.out");
  ifstream fin("comehome.in");

  int dist[52][52];
  for (int i = 0; i < 52; ++i) {
    for (int j = 0; j < 52; ++j) {
      if (i == j) {
        dist[i][j] = 0;
      } else {
        dist[i][j] = 100000;
      }
    }
  }
  int p;
  fin >> p;
  for (int i = 0; i < p; ++i) {
    char c;
    int f, t;
    fin.ignore();
    fin.get(c);
    f = ToI(c);
    fin.ignore();
    fin.get(c);
    t = ToI(c);

    int d;
    fin >> d;

    if (f == t) continue;
    if (d >= dist[f][t]) continue;
    dist[f][t] = d;
    dist[t][f] = d;
  }

  for (int k = 0; k < 52; ++k) {
    for (int i = 0; i < 52; ++i) {
      for (int j = 0; j < 52; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  int min = 100000;
  char c;
  for (int i = 26; i < 51; ++i) {
    if (dist[i][51] < min) {
      min = dist[i][51];
      c = 'A' + i - 26;
    }
  }
  fout << c << ' ' << min << '\n';

  return 0;
}
