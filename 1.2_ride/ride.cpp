/*
ID: paulzcy3
TASK: ride
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("ride.out");
  ifstream fin("ride.in");

  char a[7];
  char b[7];

  fin.getline(a, 7);
  fin.getline(b, 7);

  int moda = 1;
  int modb = 1;

  for (char* c = a; *c != 0; ++c) {
    moda = moda * (*c - 'A' + 1) % 47;
  }
  for (char* c = b; *c != 0; ++c) {
    modb = modb * (*c - 'A' + 1) % 47;
  }

  if (moda == modb) {
    fout << "GO\n";
  } else {
    fout << "STAY\n";
  }
  return 0;
}
