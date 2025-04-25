/*
ID: paulzcy3
TASK: msquare
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

const unsigned kMask[8] = {
    0x0000000f, 0x000000f0, 0x00000f00, 0x0000f000,
    0x000f0000, 0x00f00000, 0x0f000000, 0xf0000000,
};

int Get(unsigned encoded, int i) { return (encoded >> (i * 4)) & kMask[0]; }

void Set(unsigned& encoded, int i, int n) {
  encoded &= ~kMask[i];
  encoded += n << (i * 4);
}

struct Item {
  unsigned e;
  int from;
  char op;
};

int main() {
  ofstream fout("msquare.out");
  ifstream fin("msquare.in");

  unsigned start;
  unsigned target;
  for (int i = 0; i < 8; ++i) {
    int n;
    fin >> n;
    Set(target, i, n);
    Set(start, i, i + 1);
  }
  if (start == target) {
    fout << 0 << "\n\n";
    return 0;
  }

  vector<Item> queue;
  Item s;
  s.e = start;
  queue.push_back(s);
  int head = 0;
  unordered_set<unsigned> visited;
  visited.insert(start);

  while (true) {
    Item h = queue[head];
    {
      Item ha;
      Set(ha.e, 0, Get(h.e, 7));
      Set(ha.e, 1, Get(h.e, 6));
      Set(ha.e, 2, Get(h.e, 5));
      Set(ha.e, 3, Get(h.e, 4));
      Set(ha.e, 4, Get(h.e, 3));
      Set(ha.e, 5, Get(h.e, 2));
      Set(ha.e, 6, Get(h.e, 1));
      Set(ha.e, 7, Get(h.e, 0));
      ha.from = head;
      ha.op = 'A';
      if (visited.insert(ha.e).second) queue.push_back(ha);
      if (ha.e == target) break;
    }

    {
      Item hb;
      Set(hb.e, 0, Get(h.e, 3));
      Set(hb.e, 1, Get(h.e, 0));
      Set(hb.e, 2, Get(h.e, 1));
      Set(hb.e, 3, Get(h.e, 2));
      Set(hb.e, 4, Get(h.e, 5));
      Set(hb.e, 5, Get(h.e, 6));
      Set(hb.e, 6, Get(h.e, 7));
      Set(hb.e, 7, Get(h.e, 4));
      hb.from = head;
      hb.op = 'B';
      if (visited.insert(hb.e).second) queue.push_back(hb);
      if (hb.e == target) break;
    }

    {
      Item hc;
      hc.e = h.e;
      Set(hc.e, 1, Get(h.e, 6));
      Set(hc.e, 2, Get(h.e, 1));
      Set(hc.e, 5, Get(h.e, 2));
      Set(hc.e, 6, Get(h.e, 5));
      hc.from = head;
      hc.op = 'C';
      if (visited.insert(hc.e).second) queue.push_back(hc);
      if (hc.e == target) break;
    }

    ++head;
  }
  std::string ops;
  for (int i = queue.size() - 1; i != 0; i = queue[i].from) {
    ops.push_back(queue[i].op);
  }

  fout << ops.size() << '\n';
  for (int i = ops.size() - 1; i >= 0; --i) {
    fout << ops[i];
  }
  fout << '\n';

  return 0;
}
