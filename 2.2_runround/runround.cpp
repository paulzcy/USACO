/*
ID: paulzcy3
TASK: runround
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

char digits[10];
int len = 0;
bool appear[10];

void Increment(int d) {
  int i = digits[d] - '0' + 1;
  while (i < 10 && appear[i]) ++i;

  if (i < 10) {
    digits[d] = '0' + i;
    appear[i] = true;

    int next = 1;
    for (int j = d + 1; j < len; ++j) {
      while (appear[next]) ++next;
      digits[j] = '0' + next;
      appear[next] = true;
      ++next;
    }
  } else if (d > 0) {
    --d;
    appear[digits[d] - '0'] = false;
    Increment(d);
  } else {
    ++len;
    for (int j = 0; j < len; ++j) {
      digits[j] = '0' + j + 1;
      appear[j + 1] = true;
    }
    digits[len] = '\0';
    for (int j = len + 1; j < 10; ++j) {
      appear[j] = false;
    }
  }
}

int main() {
  ofstream fout("runround.out");
  ifstream fin("runround.in");

  fin.getline(digits, 10);
  while (digits[len]) ++len;

  for (int i = 0; i < 10; ++i) appear[i] = false;

  // unique number >= digits.
  int d;
  for (d = 0; d < len; ++d) {
    if (appear[digits[d] - '0']) break;
    appear[digits[d] - '0'] = true;
  }
  if (d < len) {
    Increment(d);
  } else {
    appear[digits[len - 1] - '0'] = false;
    Increment(len - 1);
  }

  while (true) {
    // If run around break;
    bool visited[9];
    for (int i = 0; i < len; ++i) visited[i] = false;
    int num_v = 0;
    int cur = 0;

    while (true) {
      visited[cur] = true;
      ++num_v;

      cur = (cur + (digits[cur] - '0')) % len;
      if (visited[cur]) break;
    };

    if (num_v == len && cur == 0) break;

    //  Next unique number.
    appear[digits[len - 1] - '0'] = false;
    Increment(len - 1);
  }

  fout << digits << '\n';

  return 0;
}
