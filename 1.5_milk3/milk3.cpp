/*
ID: paulzcy3
TASK: milk3
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool pos[21][21][21];

struct Jar {
  int cur;
  int max;
};

bool Pour(Jar x, Jar y, Jar* newx, Jar* newy) {
  if (x.cur == 0 || y.cur == y.max) return false;
  *newx = x;
  *newy = y;

  int p = min(x.cur, y.max - y.cur);
  newx->cur -= p;
  newy->cur += p;
  return true;
}

void Dfs(Jar a, Jar b, Jar c) {
  if (pos[a.cur][b.cur][c.cur]) return;
  pos[a.cur][b.cur][c.cur] = true;

  Jar newa, newb, newc;
  if (Pour(a, b, &newa, &newb)) Dfs(newa, newb, c);
  if (Pour(a, c, &newa, &newc)) Dfs(newa, b, newc);
  if (Pour(b, c, &newb, &newc)) Dfs(a, newb, newc);
  if (Pour(b, a, &newb, &newa)) Dfs(newa, newb, c);
  if (Pour(c, a, &newc, &newa)) Dfs(newa, b, newc);
  if (Pour(c, b, &newc, &newb)) Dfs(a, newb, newc);
}

int main() {
  ofstream fout("milk3.out");
  ifstream fin("milk3.in");

  Jar a, b, c;
  fin >> a.max >> b.max >> c.max;
  a.cur = 0;
  b.cur = 0;
  c.cur = c.max;

  for (int i = 0; i <= a.max; ++i) {
    for (int j = 0; j <= b.max; ++j) {
      for (int k = 0; k <= c.max; ++k) {
        pos[i][j][k] = false;
      }
    }
  }
  Dfs(a, b, c);

  bool first = true;
  int start = 0;
  if (c.max > b.max) start = c.max - b.max;
  for (int j = start; j <= c.max; ++j) {
    if (!pos[0][c.max - j][j]) continue;

    if (first) {
      first = false;
    } else {
      fout << ' ';
    }
    fout << j;
  }
  fout << '\n';

  return 0;
}
