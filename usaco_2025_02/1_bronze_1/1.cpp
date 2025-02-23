#include <algorithm>
#include <iostream>

using namespace std;

bool ca[2000][2000];
int d[1000][1000];
int n;
int u;

int getops(int d) {
  switch (d) {
    case 0:
      return 2;

    case 2:
    case -2:
      return 1;
  }
  return 0;
}

int main(int argc, char** argv) {
  cin >> n >> u;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < n; ++c) {
      char p;
      cin >> p;
      ca[r][c] = (p == '#');

      int r1, c1;
      if (r < n / 2) {
        r1 = r;
      } else {
        r1 = n - 1 - r;
      }

      if (c < n / 2) {
        c1 = c;
      } else {
        c1 = n - 1 - c;
      }

      if (ca[r][c]) {
        ++d[r1][c1];
      } else {
        --d[r1][c1];
      }
    }
  }

  int ops = 0;
  for (int r = 0; r < n / 2; ++r) {
    for (int c = 0; c < n / 2; ++c) {
      ops += getops(d[r][c]);
    }
  }
  cout << ops << "\n";

  while (u--) {
    int r, c;
    cin >> r >> c;
    --r;
    --c;

    int r1, c1;
    if (r < n / 2) {
      r1 = r;
    } else {
      r1 = n - 1 - r;
    }
    if (c < n / 2) {
      c1 = c;
    } else {
      c1 = n - 1 - c;
    }

    ops -= getops(d[r1][c1]);
    if (ca[r][c]) {
      d[r1][c1] -= 2;
    } else {
      d[r1][c1] += 2;
    }
    ca[r][c] = !ca[r][c];
    ops += getops(d[r1][c1]);
    cout << ops << "\n";
  }

  return 0;
}