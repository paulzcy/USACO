#include <algorithm>
#include <iostream>

using namespace std;

int t;
int n, k;
int s[100];
// pos[from][to][k statements]: 0 - not calcualted, 1 - impossible, 2 - possible
int pos[100][101][4];

bool Possible(int l, int r, int k);

bool impl(int l, int r, int k) {
  // cerr << "Impl " << l << " " << r << " " << k << "\n";
  if (k == 1) {
    for (int i = l + 1; i < r; ++i) {
      if (s[i] != s[l]) return false;
    }
    return true;
  }

  int len = r - l;
  if (len <= k) return true;

  // Break down [l, r) to loops of length rr.
  for (int rr = 1; rr <= len; ++rr) {
    if (len % rr != 0) continue;
    bool repeat = true;
    for (int i = 1; i < len / rr; ++i) {
      for (int j = 0; j < rr; ++j) {
        if (s[l + j] != s[l + i * rr + j]) {
          repeat = false;
          break;
        }
      }
      if (!repeat) break;
    }
    // cerr << "Loop: " << l << " " << r << " " << rr << " " << repeat << "\n";
    if (!repeat) continue;

    for (int m = l + 1; m < l + rr; ++m) {
      for (int kk = 1; kk < k; ++kk) {
        if (Possible(l, m, kk) && Possible(m, l + rr, k - kk)) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Possible(int l, int r, int k) {
  if (pos[l][r][k] == 0) {
    pos[l][r][k] = 1 + impl(l, r, k);
  }
  // cerr << "---" << l << " " << r << " " << k << " " << pos[l][r][k] << "\n";
  return pos[l][r][k] == 2;
}

int main(int argc, char** argv) {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
      cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        for (int kk = 1; kk <= k; ++kk) {
          pos[i][j][kk] = 0;
        }
      }
    }
    bool possible = false;
    for (int kk = 1; kk <= k; ++kk) {
      if (Possible(0, n, kk)) {
        possible = true;
        break;
      }
    }
    cout << (possible ? "YES\n" : "NO\n");
  }
  return 0;
}
