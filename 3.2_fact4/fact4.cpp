/*
ID: paulzcy3
TASK: fact4
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int min_c[10001];

int main() {
  ofstream fout("fact4.out");
  ifstream fin("fact4.in");

  int n;
  fin >> n;

  int num2 = 0;
  int d = 1;
  for (int i = 1; i <= n; ++i) {
    int j = i;
    for (; j % 2 == 0; j = j / 2) ++num2;
    for (; j % 5 == 0; j = j / 5) --num2;
    d = (d * j) % 10;
  }

  for (int i = 0; i < num2; ++i) {
    d = (d * 2) % 10;
  }
  fout << d << '\n';

  return 0;
}
