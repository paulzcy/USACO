/*
ID: paulzcy3
TASK: pprime
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int primes[10000];
int nump = 0;

bool IsPrime(int p) {
  for (int i = 0; i < nump && primes[i] * primes[i] <= p; ++i) {
    if (p % primes[i] == 0) return false;
  }
  return true;
}

int Pal(int i) {
  int p = i % 10;
  int exp = 1;

  while (true) {
    i /= 10;
    if (i == 0) break;

    int d = i % 10;
    p *= 10;
    exp *= 100;
    p += exp * d + d;
  }
  return p;
}

int main() {
  ofstream fout("pprime.out");
  ifstream fin("pprime.in");

  int a;
  int b;
  fin >> a >> b;

  int p = 2;
  while (p * p <= b) {
    bool prime = true;
    for (int i = 0; i < nump; ++i) {
      if (p % primes[i] == 0) {
        prime = false;
        break;
      }
    }
    if (prime) {
      primes[nump] = p;
      ++nump;
    }
    ++p;
  }

  if (a <= 5 && b >= 5) fout << "5\n";
  if (a <= 7 && b >= 7) fout << "7\n";
  if (a <= 11 && b >= 11) fout << "11\n";

  // Even length palindrome is divisible by 11.
  int i = 10;
  int pa = Pal(i);

  while (pa < a) {
    ++i;
    pa = Pal(i);
  }
  while (pa <= b) {
    if (IsPrime(pa)) fout << pa << '\n';
    ++i;
    pa = Pal(i);
  }

  return 0;
}
