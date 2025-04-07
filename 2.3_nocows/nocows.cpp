/*
ID: paulzcy3
TASK: nocows
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int num[100][200];

int Cal(int k, int n) {
  if (num[k][n] >= 0) return num[k][n];

  int sum = 0;

  for (int i = 1; i < n - 1; ++i) {
    sum = (sum + Cal(k - 1, i) * Cal(k - 1, n - 1 - i)) % 9901;
  }

  for (int i = 1; i < k - 1; ++i) {
    for (int j = 1; j < n - 1; ++j) {
      sum = (sum + Cal(k - 1, j) * Cal(i, n - 1 - j) * 2) % 9901;
    }
  }

  num[k][n] = sum;
  return sum;
}

int main() {
  ofstream fout("nocows.out");
  ifstream fin("nocows.in");

  int n;
  int k;
  fin >> n >> k;
  for (int i = 0; i <= k; ++i) {
    for (int j = 0; j <= n; ++j) {
      num[i][j] = -1;
    }
  }
  num[1][1] = 1;
  for (int i = 2; i <= k; ++i) {
    num[i][1] = 0;
  }
  for (int i = 2; i <= n; ++i) {
    num[1][i] = 0;
  }

  fout << Cal(k, n) << '\n';

  return 0;
}
