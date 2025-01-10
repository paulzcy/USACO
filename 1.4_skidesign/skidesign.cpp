/*
ID: paulzcy3
TASK: skidesign
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("skidesign.out");
  ifstream fin("skidesign.in");

  int n;
  int hill[1000];
  int min = 10000;
  int max = -1;

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> hill[i];
    if (hill[i] < min) min = hill[i];
    if (hill[i] > max) max = hill[i];
  }

  int min_cost = 2147483647;
  if (min + 17 >= max) min_cost = 0;
  for (int l = min; l + 17 <= max; ++l) {
    int cost = 0;
    int h = l + 17;

    for (int i = 0; i < n; ++i) {
      if (hill[i] < l) {
        cost += (l - hill[i]) * (l - hill[i]);
      } else if (hill[i] > h) {
        cost += (hill[i] - h) * (hill[i] - h);
      }
    }
    if (cost < min_cost) min_cost = cost;
  }

  fout << min_cost << '\n';
  return 0;
}
