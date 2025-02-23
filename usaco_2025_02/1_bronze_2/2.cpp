#include <algorithm>
#include <iostream>

using namespace std;

int num[200001];
int n;

int main(int argc, char** argv) {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    ++num[a];
  }

  int num_missing = 0;
  for (int i = 0; i <= n; ++i) {
    if (num[i] == 0) {
      cout << num_missing << "\n";
      ++num_missing;
      continue;
    }
    cout << max(num_missing, num[i]) << "\n";
  }
  return 0;
}