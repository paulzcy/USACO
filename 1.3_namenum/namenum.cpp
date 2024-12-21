/*
ID: paulzcy3
TASK: namenum
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("namenum.out");
  ifstream fin("namenum.in");
  ifstream dict("dict.txt");

  char target[13];
  fin.getline(target, 13);
  int size = 0;
  while (target[size] != '\0') ++size;

  int map[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6,
                 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};

  bool any_match = false;
  char name[13];
  while (dict.getline(name, 13)) {
    bool match = true;
    int i;
    for (i = 0; name[i] != '\0'; ++i) {
      if (i == size) {
        match = false;
        break;
      }
      if ('0' + map[name[i] - 'A'] != target[i]) {
        match = false;
        break;
      }
    }

    if (i == size && match) {
      any_match = true;
      fout << name << '\n';
    }
  }

  if (!any_match) {
    fout << "NONE\n";
  }
  if (!dict.eof()) return 1;

  return 0;
}
