/*
ID: paulzcy3
TASK: contact
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int a, b, n;
int cnt[12 << 12];

struct Count {
  int cnt;
  int encoded;
} counts[12 << 12];
int num_count = 0;

int main() {
  ofstream fout("contact.out");
  ifstream fin("contact.in");
  fin >> a >> b >> n;

  for (int i = 0; i < (12 << 12); ++i) {
    counts[i].cnt = 0;
  }

  char c;
  int num = 0;
  int bin[13];
  for (int i = a; i <= b; ++i) bin[i] = 0;
  while (fin >> c) {
    switch (c) {
      case '0':
      case '1':
        ++num;
        for (int i = a; i <= b; ++i) {
          bin[i] <<= 1;
          bin[i] &= ((1 << i) - 1);
          bin[i] += (c - '0');
          bin[i] += ((i - 1) << 12);

          if (num >= i) ++cnt[bin[i]];
        }
        break;
    }
  }

  for (int i = a; i <= b; ++i) {
    for (int j = 0; j < (1 << i); ++j) {
      int encoded = ((i - 1) << 12) + j;
      if (cnt[encoded] > 0) {
        counts[num_count].cnt = cnt[encoded];
        counts[num_count].encoded = encoded;
        ++num_count;
      }
    }
  }

  sort(counts, counts + num_count, [](Count l, Count r) {
    if (l.cnt > r.cnt) return true;
    if (l.cnt < r.cnt) return false;
    return l.encoded < r.encoded;
  });
  if (num_count == 0) return 0;

  char buf[13];
  buf[12] = '\0';
  for (int i = 0; i < num_count && n > 0;) {
    int cur = counts[i].cnt;
    fout << cur << '\n';
    int printed = 0;
    for (; i < num_count && counts[i].cnt == cur; ++i) {
      if (printed == 6) {
        fout << '\n';
        printed = 0;
      } else if (printed > 0) {
        fout << ' ';
      }

      int digits = (counts[i].encoded >> 12) + 1;
      int bin = (counts[i].encoded & ((1 << digits) - 1));
      for (int j = 0; j < digits; ++j) {
        buf[11 - j] = '0' + (bin % 2);
        bin = bin / 2;
      }

      fout << (buf + 12 - digits);

      ++printed;
    }
    fout << '\n';
    --n;
  }

  return 0;
}
