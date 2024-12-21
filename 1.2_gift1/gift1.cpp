/*
ID: paulzcy3
TASK: gift1
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int find(char (*names)[15], int n, char* name) {
  for (int i = 0; i < n; ++i) {
    char* l = names[i];
    char* r = name;

    while (true) {
      if (*l != *r) break;
      if (*l == '\0') return i;
      ++l;
      ++r;
    }
  }

  return -1;
}

int main() {
  ofstream fout("gift1.out");
  ifstream fin("gift1.in");

  char names[10][15];
  int bal[10];

  int n;
  fin >> n;
  fin.ignore();
  for (int i = 0; i < n; ++i) {
    bal[i] = 0;
    fin.getline(names[i], 15);
  }
  for (int i = 0; i < n; ++i) {
    char from[15];
    fin.getline(from, 15);
    int money;
    int people;
    fin >> money >> people;
    fin.ignore();

    if (people == 0) continue;

    bal[find(names, n, from)] -= money / people * people;
    for (int j = 0; j < people; ++j) {
      char to[15];
      fin.getline(to, 15);

      bal[find(names, n, to)] += money / people;
    }
  }

  for (int i = 0; i < n; ++i) {
    fout << names[i] << " " << bal[i] << "\n";
  }

  return 0;
}
