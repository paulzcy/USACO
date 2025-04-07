/*
ID: paulzcy3
TASK: cowtour
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
int x[150];
int y[150];

double dist[150][150];
double max_dist[150];
int belong[150];
double diameter[150];

int main() {
  ofstream fout("cowtour.out");
  ifstream fin("cowtour.in");

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> x[i] >> y[i];
    max_dist[i] = 0;
    belong[i] = -1;
  }
  for (int i = 0; i < n; ++i) {
    fin.ignore();
    for (int j = 0; j < n; ++j) {
      char ch;
      fin.get(ch);
      if (ch == '1') {
        dist[i][j] =
            sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      } else {
        dist[i][j] = 0;
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] > 0 && dist[k][j] > 0 &&
            (dist[i][j] == 0 || dist[i][k] + dist[k][j] < dist[i][j])) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
  int num_p = 0;
  for (int i = 0; i < n; ++i) {
    if (belong[i] == -1) {
      belong[i] = num_p;
      diameter[num_p] = 0;
      ++num_p;
    }
    for (int j = i + 1; j < n; ++j) {
      if (dist[i][j] == 0) continue;

      belong[j] = belong[i];
      if (dist[i][j] > max_dist[i]) max_dist[i] = dist[i][j];
      if (dist[i][j] > max_dist[j]) max_dist[j] = dist[i][j];
      if (dist[i][j] > diameter[belong[i]]) {
        diameter[belong[i]] = dist[i][j];
      }
    }
  }

  double min_diameter = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (belong[i] == belong[j]) continue;
      double new_diameter = max(max_dist[i] + max_dist[j] +
                                    sqrt((x[i] - x[j]) * (x[i] - x[j]) +
                                         (y[i] - y[j]) * (y[i] - y[j])),
                                max(diameter[belong[i]], diameter[belong[j]]));
      if (min_diameter == 0 || new_diameter < min_diameter) {
        min_diameter = new_diameter;
      }
    }
  }

  fout << fixed << min_diameter << '\n';

  return 0;
}
