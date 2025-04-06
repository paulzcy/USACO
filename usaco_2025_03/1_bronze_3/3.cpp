#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> ds;
  ds.resize(26);

  int n;
  int q;
  cin >> n >> q;

  for (int i = 0; i < n; ++i) {
    char c;
    cin >> c;
    // cerr << c;
    ds[c - 'a'].push_back(i);
  }
  // cerr << '\n';

  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;

    int64_t result = -1;
    for (int m = 0; m < 26; ++m) {
      // cerr << char{'a' + m} << ' ';
      // Find the first m;
      auto it = std::lower_bound(ds[m].begin(), ds[m].end(), l);
      if (it == ds[m].end()) continue;

      int ll = *it;
      // cerr << ll << " ";

      for (int o = 0; o < 26; ++o) {
        if (m == o) continue;
        // cerr << char{'a' + o} << ' ';

        // Find the last o;
        auto it = std::lower_bound(ds[o].begin(), ds[o].end(), r);
        if (it == ds[o].begin()) continue;
        --it;
        int rr = *it;
        if (rr < ll) continue;
        // cerr << rr << ' ';

        // while (it != ds[o].begin()) {
        //   --it;
        //   int mm = *it;
        //   if (mm < ll) break;
        //   // cerr << mm << ' ';
        //   result = max(result, int64_t{rr - mm} * (mm - ll));
        // }

        // Find the middle o;
        int mm = (ll + rr) / 2;
        it = std::lower_bound(ds[o].begin(), ds[o].end(), mm);
        auto update = [&](int mid) {
          if (mid < ll || mid >= rr) return;
          result = max(result, int64_t{rr - mid} * (mid - ll));
        };
        if (it != ds[o].begin()) {
          auto i2 = prev(it);
          update(*i2);
        }
        update(*it);
        ++it;
        if (it != ds[o].end()) update(*it);
      }
      // cerr << '\n';
    }
    cout << result << '\n';
  }

  return 0;
}
