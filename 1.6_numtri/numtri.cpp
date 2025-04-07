/*
ID: paulzcy3
TASK: numtri
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("numtri.out");
  ifstream fin("numtri.in");

  int r;
  fin >> r;

  int max = 0;
  int buf1[1000];
  int buf2[1000];

  int* sum = buf1;
  int* pre = buf2;

  fin >> pre[0];
  max = pre[0];

  for (int i = 2; i <= r; ++i) {
    int num;
    fin >> num;

    sum[0] = pre[0] + num;
    if (sum[0] > max) max = sum[0];

    for (int j = 1; j < i - 1; ++j) {
      fin >> num;
      sum[j] = std::max(pre[j - 1], pre[j]) + num;
      if (sum[j] > max) max = sum[j];
    }

    fin >> num;
    sum[i - 1] = pre[i - 2] + num;
    if (sum[i - 1] > max) max = sum[i - 1];

    int* tmp = pre;
    pre = sum;
    sum = tmp;
  }

  fout << max << '\n';
  return 0;
}
