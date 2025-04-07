/*
ID: paulzcy3
TASK: prefix
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("prefix.out");
  ifstream fin("prefix.in");

  char pri[200][10];
  int len[201];
  int num = 0;
  len[num] = 0;
  for (bool done = false; !done;) {
    char c;
    fin.get(c);
    switch (c) {
      case '\n':
      case ' ':
        ++num;
        len[num] = 0;
        break;
      case '.':
        done = true;
        fin.ignore();
        break;
      default:
        pri[num][len[num]] = c;
        ++len[num];
    }
  }

  struct Next {
    unsigned char pri;
    char l;
  };
  Next matching[2000];
  int num_match = num;
  for (int i = 0; i < num; ++i) {
    matching[i].pri = i;
    matching[i].l = 0;
  }

  int num_c = 0;
  int prefix = 0;

  for (char c; fin.get(c);) {
    // cout << num_c << ' ' << static_cast<int>(c) << '\n';
    if (c == '\n') continue;
    ++num_c;

    int new_match = 0;
    bool need_new = false;

    for (int i = 0; i < num_match; ++i) {
      if (pri[matching[i].pri][matching[i].l] != c) continue;
      ++matching[i].l;

      if (matching[i].l == len[matching[i].pri]) {
        need_new = true;
      } else {
        matching[new_match] = matching[i];
        ++new_match;
      }
    }

    num_match = new_match;
    if (need_new) {
      prefix = num_c;
      for (int i = 0; i < num; ++i) {
        matching[num_match + i].pri = i;
        matching[num_match + i].l = 0;
      }
      num_match += num;
    }
  }

  fout << prefix << '\n';

  return 0;
}
