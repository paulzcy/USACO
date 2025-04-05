#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> wins;  // wins[i] logs all symbols that win i;
vector<int> tmp;
int count_intersect(int l, int r) {
  tmp.clear();
  std::set_intersection(wins[l].begin(), wins[l].end(), wins[r].begin(),
                        wins[r].end(), back_inserter(tmp));
  return tmp.size();
}

int main() {
  int n, m;

  cin >> n >> m;
  wins.resize(n);

  char c;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      cin >> c;
      if (c == 'W') {
        wins[j].push_back(i);
      } else if (c == 'L') {
        wins[i].push_back(j);
      }
    }
  }

  for (auto& v : wins) {
    sort(v.begin(), v.end());
  }

  int s1, s2;

  for (int i = 0; i < m; ++i) {
    cin >> s1 >> s2;
    int s = count_intersect(s1 - 1, s2 - 1);
    cout << s * n * 2 - s * s << '\n';
  }
  return 0;
}
