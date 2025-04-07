/*
ID: paulzcy3
TASK: preface
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("preface.out");
  ifstream fin("preface.in");

  int n;
  fin >> n;
  enum {
    kI,
    kV,
    kX,
    kL,
    kC,
    kD,
    kM,
    kMax,
  };
  const char kLetter[kMax] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  int num[kMax] = {0, 0, 0, 0, 0, 0, 0};

  for (int i = 1; i <= n; ++i) {
    int x = i;
    while (x >= 1000) {
      x -= 1000;
      ++num[kM];
    }
    if (x >= 900) {
      x -= 900;
      ++num[kC];
      ++num[kM];
    } else if (x >= 500) {
      x -= 500;
      ++num[kD];
      num[kC] += x / 100;
      x = x - x / 100 * 100;
    } else if (x >= 400) {
      x -= 400;
      ++num[kD];
      ++num[kC];
    } else {
      num[kC] += x / 100;
      x = x - x / 100 * 100;
    }

    if (x >= 90) {
      x -= 90;
      ++num[kX];
      ++num[kC];
    } else if (x >= 50) {
      x -= 50;
      ++num[kL];
      num[kX] += x / 10;
      x = x - x / 10 * 10;
    } else if (x >= 40) {
      x -= 40;
      ++num[kX];
      ++num[kL];
    } else {
      num[kX] += x / 10;
      x = x - x / 10 * 10;
    }

    if (x >= 9) {
      ++num[kI];
      ++num[kX];
    } else if (x >= 5) {
      x -= 5;
      ++num[kV];
      num[kI] += x;
    } else if (x >= 4) {
      ++num[kI];
      ++num[kV];
    } else {
      num[kI] += x;
    }
  }

  for (int i = 0; i < kMax; ++i) {
    if (num[i] > 0) {
      fout << kLetter[i] << ' ' << num[i] << '\n';
    }
  }

  return 0;
}
