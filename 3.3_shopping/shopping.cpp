/*
ID: paulzcy3
TASK: shopping
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

int s;
int n[99];
int code[99][5];
int num[99][5];
int dprice[99];

int b;
array<int, 5> k;  // num
int p[5];         // price per

int best[6 * 6 * 6 * 6 * 6];
bool BetterPrice(const array<int, 5>& remaining, int price) {
  int e = 0;
  for (int i = 0; i < b; ++i) {
    e = e * 6 + remaining[i];
  }
  if (best[e] == 0 || price < best[e]) {
    best[e] = price;
    return true;
  } else {
    return false;
  }
}

int Enumerate(int num_s, array<int, 5> remaining, int price) {
  if (num_s == s) {
    for (int i = 0; i < b; ++i) {
      price += remaining[i] * p[i];
    }
    return price;
  }

  int min_price = Enumerate(num_s + 1, remaining, price);

  bool has_remaining = true;
  while (true) {
    for (int i = 0; i < n[num_s]; ++i) {
      remaining[code[num_s][i]] -= num[num_s][i];
      if (remaining[code[num_s][i]] < 0) {
        has_remaining = false;
        break;
      }
    }
    if (!has_remaining) break;
    price += dprice[num_s];
    if (!BetterPrice(remaining, price)) continue;
    min_price = min(min_price, Enumerate(num_s + 1, remaining, price));
  }

  return min_price;
}

int main() {
  ofstream fout("shopping.out");
  ifstream fin("shopping.in");

  fin >> s;
  for (int i = 0; i < s; ++i) {
    fin >> n[i];
    for (int j = 0; j < n[i]; ++j) {
      fin >> code[i][j] >> num[i][j];
    }
    fin >> dprice[i];
  }
  fin >> b;
  int c[5];  // code
  for (int i = 0; i < b; ++i) {
    fin >> c[i] >> k[i] >> p[i];
  }
  for (int i = 0; i < s; ++i) {
    for (int j = 0; j < n[i]; ++j) {
      int pro = 0;
      while (code[i][j] != c[pro]) ++pro;
      code[i][j] = pro;
    }
  }

  fout << Enumerate(0, k, 0) << '\n';

  return 0;
}
