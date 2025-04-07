/*
ID: paulzcy3
TASK: sprime
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int n;
int primes[10000];
int nump = 0;

bool IsPrime(int p) {
  if (p == 0 || p == 1) return false;
  for (int i = 0; i < nump && primes[i] * primes[i] <= p; ++i) {
    if (p % primes[i] == 0) return false;
  }
  return true;
}

void Dfs(int d, int num, ostream& fout) {
  for (int i = 0; i < 10; ++i) {
    int next = num * 10 + i;
    if (IsPrime(next)) {
      if (d == n) {
        fout << next << '\n';
      } else {
        Dfs(d + 1, next, fout);
      }
    }
  }
}

int main() {
  ofstream fout("sprime.out");
  ifstream fin("sprime.in");

  fin >> n;

  int e = 1;
  for (int i = 0; i < n; ++i) e *= 10;
  for (int p = 2; p * p <= e; ++p) {
    if (IsPrime(p)) {
      primes[nump] = p;
      ++nump;
    }
  }

  Dfs(1, 0, fout);

  return 0;
}
