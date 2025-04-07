/*
ID: paulzcy3
TASK: maze1
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Cord {
  int row;
  int col;
};
Cord C(int row, int col) {
  Cord c;
  c.row = row;
  c.col = col;
  return c;
}
const Cord kDelta[] = {C(-1, 0), C(0, 1), C(1, 0), C(0, -1)};
const int kNorth = 0;
const int kEast = 1;
const int kSouth = 2;
const int kWest = 3;

int w, h;
int wall[100][38];
int dist[100][38];
Cord queue[100 * 38 + 2];
int head = 0;
int tail = 0;

void ReadHorizontalWall(istream& fin, int row) {
  fin.ignore();  // linewrap.
  char c;
  for (int i = 0; i < w; ++i) {
    fin.ignore();  // '+'
    fin.get(c);
    if (c == ' ') {
      if (row == 0) {
        dist[row][i] = 1;
        wall[row][i] |= (1 << kNorth);
        queue[tail] = C(row, i);
        ++tail;
      } else if (row == h) {
        dist[row - 1][i] = 1;
        wall[row - 1][i] |= (1 << kSouth);
        queue[tail] = C(row - 1, i);
        ++tail;
      }
      continue;
    }

    if (row < h) wall[row][i] |= (1 << kNorth);
    if (row > 0) wall[row - 1][i] |= (1 << kSouth);
  }
  fin.ignore();  // '+'.
}
void ReadVerticalWall(istream& fin, int row) {
  char c;
  fin.ignore();  // linewrap.
  fin.get(c);

  if (c == ' ') {
    dist[row][0] = 1;
    queue[tail] = C(row, 0);
    ++tail;
  }
  wall[row][0] |= (1 << kWest);

  for (int i = 0; i < w; ++i) {
    fin.ignore();
    fin.get(c);

    if (c == ' ') {
      if (i == w - 1) {
        dist[row][i] = 1;
        queue[tail] = C(row, i);
        ++tail;
        wall[row][i] |= (1 << kEast);
      }
      continue;
    }
    wall[row][i] |= (1 << kEast);
    if (i < w - 1) {
      wall[row][i + 1] |= (1 << kWest);
    }
  }
}

int main() {
  ofstream fout("maze1.out");
  ifstream fin("maze1.in");

  fin >> w >> h;

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      wall[i][j] = 0;
      dist[i][j] = -1;
    }
  }

  for (int i = 0; i < h; ++i) {
    ReadHorizontalWall(fin, i);
    ReadVerticalWall(fin, i);
  }
  ReadHorizontalWall(fin, h);
  int max_dist = 1;

  while (head != tail) {
    Cord q = queue[head];
    ++head;

    for (int dir = 0; dir < 4; ++dir) {
      if (wall[q.row][q.col] & (1 << dir)) continue;
      int row = q.row + kDelta[dir].row;
      int col = q.col + kDelta[dir].col;
      if (dist[row][col] == -1) {
        dist[row][col] = dist[q.row][q.col] + 1;
        max_dist = max(max_dist, dist[row][col]);
        queue[tail] = C(row, col);
        ++tail;
      }
    }
  }

  fout << max_dist << '\n';

  return 0;
}
