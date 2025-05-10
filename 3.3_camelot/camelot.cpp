/*
ID: paulzcy3
TASK: camelot
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int dist[840][840];
int knights[840];
int num_knights;
int r, c;
int kr, kc;

int queue[840];
int head, tail;

const int kDr[] = {-2, -1, 1, 2, -2, -1, 1, 2};
const int kDc[] = {-1, -2, 2, 1, 1, 2, -2, -1};

int E(int ir, int ic) { return ir * c + ic; }

int main() {
  ofstream fout("camelot.out");
  ifstream fin("camelot.in");

  fin >> r >> c;
  char col;
  int row;
  fin.ignore();
  fin >> col >> row;

  kr = row - 1;
  kc = col - 'A';

  while (fin >> col >> row) {
    int krow = row - 1;
    int kcol = col - 'A';
    knights[num_knights] = E(krow, kcol);
    ++num_knights;
  }

  if (num_knights == 0) {
    fout << "0\n";
    return 0;
  }

  for (int i = 0; i < r * c; ++i) {
    for (int j = 0; j < r * c; ++j) {
      dist[i][j] = 850;
    }
  }

  for (int ir = 0; ir < r; ++ir) {
    for (int ic = 0; ic < c; ++ic) {
      int e = E(ir, ic);
      dist[e][e] = 0;
      queue[0] = e;
      head = 0;
      tail = 1;

      while (head != tail) {
        int eh = queue[head];
        ++head;
        for (int i = 0; i < 8; ++i) {
          int jr = eh / c + kDr[i];
          int jc = eh % c + kDc[i];
          if (jr < 0 || jr >= r || jc < 0 || jc >= c) continue;
          int ej = E(jr, jc);
          if (dist[e][ej] != 850) continue;

          dist[e][ej] = dist[e][eh] + 1;
          queue[tail] = ej;
          ++tail;
        }
      }
    }
  }

  int min_move = 2147483647;
  // Destination is i.
  for (int ir = 0; ir < r; ++ir) {
    for (int ic = 0; ic < c; ++ic) {
      int knight_moves = 0;
      for (int j = 0; j < num_knights; ++j) {
        knight_moves += dist[E(ir, ic)][knights[j]];
      }
      if (knight_moves > min_move) continue;

      // Move king to j.
      for (int jr = 0; jr < r; ++jr) {
        for (int jc = 0; jc < c; ++jc) {
          int moves2 =
              knight_moves + max(abs(kr - jr), abs(kc - jc));  // king moves;
          if (moves2 > min_move) continue;

          for (int k = 0; k < num_knights; ++k) {
            int moves = moves2 - dist[E(ir, ic)][knights[k]] +
                        dist[knights[k]][E(jr, jc)] +
                        dist[E(jr, jc)][E(ir, ic)];
            min_move = min(moves, min_move);
            if (min_move == 1) {
              cout << min_move << ' ' << ir << ' ' << ic << ' ' << jr << ' '
                   << jc << '\n';
            }
          }
        }
      }
    }
  }
  fout << min_move << '\n';

  return 0;
}
