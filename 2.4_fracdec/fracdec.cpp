/*
ID: paulzcy3
TASK: fracdec
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int digit[100000];
int appear[100000];
int w = 0;

void Put(ostream& fout, char c) {
  if (w == 76) {
    w = 0;
    fout << '\n';
  }
  fout << c;
  ++w;
}

int main() {
  ofstream fout("fracdec.out");
  ifstream fin("fracdec.in");

  int n, d;
  fin >> n >> d;
  fout << n / d;

  int r = n / d;
  while (r > 0) {
    r /= 10;
    ++w;
  }
  if (w == 0) w = 1;

  Put(fout, '.');
  n = n % d;

  for (int i = 0; i < d; ++i) {
    appear[i] = -1;
  }

  int l = 0;
  while (n != 0 && appear[n] == -1) {
    appear[n] = l;
    n *= 10;
    digit[l] = n / d;
    n = n % d;
    ++l;
  }

  if (n == 0) {
    for (int i = 0; i < l; ++i) {
      Put(fout, '0' + digit[i]);
    }
    if (l == 0) Put(fout, '0');
  } else {
    for (int i = 0; i < appear[n]; ++i) {
      Put(fout, '0' + digit[i]);
    }
    Put(fout, '(');
    for (int i = appear[n]; i < l; ++i) {
      Put(fout, '0' + digit[i]);
    }
    Put(fout, ')');
  }

  fout << '\n';

  return 0;
}
