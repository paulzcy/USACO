/*
ID: paulzcy3
TASK: sort3
LANG: C++
*/
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ofstream fout("sort3.out");
  ifstream fin("sort3.in");

  int n;
  int nums[1000];
  int num1 = 0;
  int num2 = 0;
  int num3 = 0;

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> nums[i];
    switch (nums[i]) {
      case 1:
        ++num1;
        break;
      case 2:
        ++num2;
        break;
      case 3:
        ++num3;
        break;
    }
  }

  int num1in2 = 0;
  int num1in3 = 0;
  int num2in1 = 0;
  int num2in3 = 0;
  int num3in1 = 0;
  int num3in2 = 0;

  for (int i = 0; i < num1; ++i) {
    if (nums[i] == 2) {
      ++num2in1;
    } else if (nums[i] == 3) {
      ++num3in1;
    }
  }
  for (int i = num1; i < num1 + num2; ++i) {
    if (nums[i] == 1) {
      ++num1in2;
    } else if (nums[i] == 3) {
      ++num3in2;
    }
  }
  for (int i = num1 + num2; i < n; ++i) {
    if (nums[i] == 1) {
      ++num1in3;
    } else if (nums[i] == 2) {
      ++num2in3;
    }
  }

  int swap12 = min(num1in2, num2in1);
  int swap13 = min(num1in3, num3in1);
  int swap23 = min(num2in3, num3in2);

  num1in2 -= swap12;
  num2in1 -= swap12;
  num1in3 -= swap13;
  num3in1 -= swap13;
  num2in3 -= swap23;
  num3in2 -= swap23;

  fout << swap12 + swap13 + swap23 +
              (num1in2 + num2in1 + num1in3 + num3in1 + num2in3 + num3in2) / 3 *
                  2
       << '\n';

  return 0;
}
