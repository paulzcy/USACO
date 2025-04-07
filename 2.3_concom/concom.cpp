/*
ID: paulzcy3
TASK: concom
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int own[100][100];
bool control[100][100];
int ctlown[100][100];

void Update(int x, int y) {
  for (int i = 0; i < 100; ++i) {
    if (i == x) continue;
    ctlown[x][i] += own[y][i];
    if (!control[x][i] && ctlown[x][i] > 50) {
      control[x][i] = true;
      Update(x, i);
    }
  }
}

int main() {
  ofstream fout("concom.out");
  ifstream fin("concom.in");

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      own[i][j] = 0;
      control[i][j] = false;
      ctlown[i][j] = 0;
    }
  }

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    int x, y, p;
    fin >> x >> y >> p;
    own[x - 1][y - 1] = p;
    ctlown[x - 1][y - 1] = p;
  }

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (i != j && own[i][j] > 50 && !control[i][j]) {
        control[i][j] = true;
        Update(i, j);
      }
    }
  }

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (i != j && control[i][j]) {
        fout << (i + 1) << ' ' << (j + 1) << '\n';
      }
    }
  }

  return 0;
}
