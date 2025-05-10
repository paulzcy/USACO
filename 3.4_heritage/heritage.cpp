/*
ID: paulzcy3
TASK: heritage
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

char in[27];
char pre[27];

void Handle(int inl, int inr, int pl, int pr, ostream& fout) {
  if (inl == inr) return;
  if (inl + 1 == inr) {
    fout << in[inl];
    return;
  }

  char c = pre[pl];
  int i = inl;
  while (in[i] != c) ++i;
  Handle(inl, i, pl + 1, pl + 1 + i - inl, fout);
  Handle(i + 1, inr, pl + 1 + i - inl, pr, fout);
  fout << c;
}

int main() {
  ofstream fout("heritage.out");
  ifstream fin("heritage.in");

  fin >> in >> pre;
  int l = 0;
  while (in[l] != '\0') ++l;

  Handle(0, l, 0, l, fout);

  fout << '\n';

  return 0;
}
