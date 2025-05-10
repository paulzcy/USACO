/*
ID: paulzcy3
TASK: nuggets
LANG: C++
*/
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
int num[10];
bool possible[257];

int Gcd(int a, int b) {
  while (true) {
    if (a % b == 0) return b;
    int t = a % b;
    a = b;
    b = t;
  }
}

int main() {
  ofstream fout("nuggets.out");
  ifstream fin("nuggets.in");

  fin >> n;
  int gcd = 0;
  for (int i = 0; i < n; ++i) {
    fin >> num[i];
    gcd = Gcd(gcd, num[i]);
  }
  if (gcd > 1) {
    fout << "0\n";
    return 0;
  }

  int max_i = 0;
  sort(num, num + n);

  possible[0] = true;
  for (int i = 0;; ++i) {
    if (!possible[i % 257]) {
      max_i = i;
      continue;
    }
    for (int j = 0; j < n; ++j) {
      possible[(i + num[j]) % 257] = true;
    }
    bool all = true;
    for (int j = 1; j < num[0] && all; ++j) {
      all = possible[(i + j) % 257];
    }
    if (all) break;
    possible[i % 257] = false;
  }

  fout << max_i << '\n';
  return 0;
}
