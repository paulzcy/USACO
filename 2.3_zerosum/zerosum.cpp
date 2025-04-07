/*
ID: paulzcy3
TASK: zerosum
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
char ops[9];

void Dfs(int sum, int num, int last, char op, ostream& fout) {
  int d = last + 1;
  int num1 = num * 10 + d;

  if (d == n) {
    switch (op) {
      case '+':
        sum += num1;
        break;
      case '-':
        sum -= num1;
        break;
    }
    if (sum == 0) {
      for (int i = 1; i <= n - 1; ++i) {
        fout << i << ops[i];
      }
      fout << n << '\n';
    }
    return;
  }

  ops[d] = ' ';
  Dfs(sum, num1, d, op, fout);

  int sum1 = (op == '+') ? (sum + num1) : (sum - num1);
  ops[d] = '+';
  Dfs(sum1, 0, d, '+', fout);

  ops[d] = '-';
  Dfs(sum1, 0, d, '-', fout);
}

int main() {
  ofstream fout("zerosum.out");
  ifstream fin("zerosum.in");

  fin >> n;
  Dfs(0, 0, 0, '+', fout);

  return 0;
}
