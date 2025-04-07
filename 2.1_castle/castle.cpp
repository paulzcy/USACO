/*
ID: paulzcy3
TASK: castle
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int kWest = 1;
const int kNorth = 2;
const int kEast = 4;
const int kSouth = 8;

int m, n;
int wall[50][50];
int room[50][50];
int num_rooms = 0;
int sizes[50 * 50];

void Dfs(int row, int col) {
  if (!(wall[row][col] & kWest)) {
    if (room[row][col - 1] == -1) {
      room[row][col - 1] = num_rooms;
      ++sizes[num_rooms];
      Dfs(row, col - 1);
    }
  }

  if (!(wall[row][col] & kNorth)) {
    if (room[row - 1][col] == -1) {
      room[row - 1][col] = num_rooms;
      ++sizes[num_rooms];
      Dfs(row - 1, col);
    }
  }

  if (!(wall[row][col] & kEast)) {
    if (room[row][col + 1] == -1) {
      room[row][col + 1] = num_rooms;
      ++sizes[num_rooms];
      Dfs(row, col + 1);
    }
  }

  if (!(wall[row][col] & kSouth)) {
    if (room[row + 1][col] == -1) {
      room[row + 1][col] = num_rooms;
      ++sizes[num_rooms];
      Dfs(row + 1, col);
    }
  }
}

int main() {
  ofstream fout("castle.out");
  ifstream fin("castle.in");

  int max_size = 0;

  fin >> m >> n;
  for (int row = 0; row < n; ++row) {
    for (int col = 0; col < m; ++col) {
      fin >> wall[row][col];
      room[row][col] = -1;
    }
  }

  for (int row = 0; row < n; ++row) {
    for (int col = 0; col < m; ++col) {
      if (room[row][col] != -1) continue;
      room[row][col] = num_rooms;
      sizes[num_rooms] = 1;
      Dfs(row, col);
      if (sizes[num_rooms] > max_size) max_size = sizes[num_rooms];
      ++num_rooms;
    }
  }

  fout << num_rooms << '\n' << max_size << '\n';

  int max_comb = 0;
  int max_row;
  int max_col;
  char w;

  for (int col = 0; col < m; ++col) {
    for (int row = n - 1; row >= 0; --row) {
      if (row > 0 && room[row][col] != room[row - 1][col] &&
          sizes[room[row][col]] + sizes[room[row - 1][col]] > max_comb) {
        max_comb = sizes[room[row][col]] + sizes[room[row - 1][col]];
        max_row = row;
        max_col = col;
        w = 'N';
      }

      if (col < m - 1 && room[row][col] != room[row][col + 1] &&
          sizes[room[row][col]] + sizes[room[row][col + 1]] > max_comb) {
        max_comb = sizes[room[row][col]] + sizes[room[row][col + 1]];
        max_row = row;
        max_col = col;
        w = 'E';
      }
    }
  }
  fout << max_comb << '\n'
       << (max_row + 1) << ' ' << (max_col + 1) << ' ' << w << '\n';

  return 0;
}
