/*
ID: paulzcy3
TASK: ttwo
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

unsigned char visited[100 * 100 * 4 * 4 / 8];

bool Visited(int frow, int fcol, int fdir, int crow, int ccol, int cdir) {
  int id = frow * 10 * 10 * 10 * 4 * 4 +  //
           fcol * 10 * 10 * 4 * 4 +       //
           crow * 10 * 4 * 4 +            //
           ccol * 4 * 4 +                 //
           fdir * 4 + cdir;
  int offset = id / 8;
  unsigned char exp = 1 << (id % 8);
  if (visited[offset] & exp) return true;
  visited[offset] |= exp;
  return false;
}

int main() {
  ofstream fout("ttwo.out");
  ifstream fin("ttwo.in");

  char map[10][10];
  int frow, fcol, crow, ccol;
  int fdir = 0, cdir = 0;
  const int drow[4] = {-1, 0, 1, 0};
  const int dcol[4] = {0, 1, 0, -1};
  for (int i = 0; i < 100 * 100 * 4 * 4 / 8; ++i) {
    visited[i] = 0;
  }

  for (int row = 0; row < 10; ++row) {
    for (int col = 0; col < 10; ++col) {
      fin.get(map[row][col]);
      switch (map[row][col]) {
        case 'F':
          frow = row;
          fcol = col;
          map[row][col] = '.';
          break;
        case 'C':
          crow = row;
          ccol = col;
          map[row][col] = '.';
          break;
      }
    }
    fin.ignore();
  }

  int num_steps = 0;
  while (true) {
    if (Visited(frow, fcol, fdir, crow, ccol, cdir)) {
      fout << "0\n";
      break;
    }

    int nfrow = frow + drow[fdir];
    int nfcol = fcol + dcol[fdir];
    if (nfrow >= 0 && nfrow < 10 && nfcol >= 0 && nfcol < 10 &&
        map[nfrow][nfcol] == '.') {
      frow = nfrow;
      fcol = nfcol;
    } else {
      fdir = (fdir + 1) % 4;
    }

    int ncrow = crow + drow[cdir];
    int nccol = ccol + dcol[cdir];
    if (ncrow >= 0 && ncrow < 10 && nccol >= 0 && nccol < 10 &&
        map[ncrow][nccol] == '.') {
      crow = ncrow;
      ccol = nccol;
    } else {
      cdir = (cdir + 1) % 4;
    }

    ++num_steps;
    if (frow == crow && fcol == ccol) {
      fout << num_steps << '\n';
      break;
    }
  }

  return 0;
}
