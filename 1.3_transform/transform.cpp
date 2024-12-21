/*
ID: paulzcy3
TASK: transform
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Cord {
  int row;
  int col;
};

char before[10][10];
char after[10][10];
int n;

Cord Rotate90(Cord in) {
  Cord out;
  out.row = in.col;
  out.col = n - 1 - in.row;
  return out;
}
Cord Rotate180(Cord in) { return Rotate90(Rotate90(in)); }
Cord Rotate270(Cord in) { return Rotate90(Rotate180(in)); }
Cord Reflection(Cord in) {
  Cord out;
  out.row = in.row;
  out.col = n - 1 - in.col;
  return out;
}
Cord Comb1(Cord in) { return Reflection(Rotate90(in)); }
Cord Comb2(Cord in) { return Reflection(Rotate180(in)); }
Cord Comb3(Cord in) { return Reflection(Rotate270(in)); }
Cord Identity(Cord in) { return in; }

bool Match(Cord (*transform)(Cord in)) {
  Cord in;
  for (in.row = 0; in.row < n; ++in.row) {
    for (in.col = 0; in.col < n; ++in.col) {
      Cord out = transform(in);
      if (after[out.row][out.col] != before[in.row][in.col]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ofstream fout("transform.out");
  ifstream fin("transform.in");

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin.ignore();
    for (int j = 0; j < n; ++j) {
      fin.get(before[i][j]);
    }
  }
  for (int i = 0; i < n; ++i) {
    fin.ignore();
    for (int j = 0; j < n; ++j) {
      fin.get(after[i][j]);
    }
  }

  if (Match(&Rotate90)) {
    fout << "1\n";
  } else if (Match(&Rotate180)) {
    fout << "2\n";
  } else if (Match(&Rotate270)) {
    fout << "3\n";
  } else if (Match(&Reflection)) {
    fout << "4\n";
  } else if (Match(&Comb1) || Match(&Comb2) || Match(&Comb3)) {
    fout << "5\n";
  } else if (Match(Identity)) {
    fout << "6\n";
  } else {
    fout << "7\n";
  }

  return 0;
}
