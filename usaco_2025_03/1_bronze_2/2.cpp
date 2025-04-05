#include <iostream>
#include <map>

using namespace std;

int main() {
  int t;
  int n;
  cin >> t;
  map<int, int> cnt;
  while (t--) {
    cnt.clear();
    cin >> n;
    while (n--) {
      int b;
      cin >> b;
      ++cnt[b];
    }
    int sum = 0;
    for (const auto& p : cnt) {
      // cerr << p.first << " " << p.second << "\n";
      if (p.second >= 2) sum += 2;
    }
    auto back = *cnt.rbegin();
    if (back.second < 2) {
      sum += 1;
    } else {
      sum -= 1;
    }
    cout << sum << '\n';
  }
  return 0;
}
