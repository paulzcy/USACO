/*
ID: paulzcy3
TASK: game1
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Result {
  int first;
  int second;
};
Result result[100][100];

int board[100];

int main() {
  ofstream fout("game1.out");
  ifstream fin("game1.in");

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> board[i];
  }

  for (int i = 0; i < n; ++i) {
    result[i][0].first = board[i];
    result[i][0].second = 0;
  }

  for (int l = 1; l < n; ++l) {
    for (int i = 0; i + l < n; ++i) {
      if (board[i] + result[i + 1][l - 1].second >
          board[i + l] + result[i][l - 1].second) {
        result[i][l].first = board[i] + result[i + 1][l - 1].second;
        result[i][l].second = result[i + 1][l - 1].first;
      } else {
        result[i][l].first = board[i + l] + result[i][l - 1].second;
        result[i][l].second = result[i][l - 1].first;
      }
    }
  }

  fout << result[0][n - 1].first << ' ' << result[0][n - 1].second << '\n';

  return 0;
}
