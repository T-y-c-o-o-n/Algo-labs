//
// Created by tycoon on 23.05.2020.
//
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>

struct line {
  int X, Y_D, Y_U;
  bool open;
  line(int L, int D, int U, bool o) : X(L), Y_D(D), Y_U(U), open(o) {}
};
bool comp(line const &a, line const &b) {
  if (a.X == b.X) return a.open && !b.open;
  return a.X < b.X;
}
std::vector<line> lines;
struct node {
  int max;
  int add;
  node() : max(0), add(0) {}
};
int const M = (1 << 20);  // 1 048 576
node * tree = new node[2 * M * 4 + 9];
#define left (2 * v + 1)
#define right (2 * v + 2)
#define tm ((tl + tr) / 2)
#define default size_t v, int tl, int tr

void propagate(default) {
  int add = tree[v].add;
  tree[v].add = 0;
  if (tl + 1 <= tr) {
    tree[left].max += add;
    tree[right].max += add;
    tree[left].add += add;
    tree[right].add += add;
  }
}
void inc(int l, int r, int val, default) {
//  printf("INC!! v:%zu  tl:%i  tr:%i\n", v, tl, tr);
  propagate(v, tl, tr);
  if (r <= tl || tr <= l) {
//    puts("failed here 1");
    return;
  }
  if (l <= tl && tr <= r) {
    tree[v].max += val;
    tree[v].add += val;
//    puts("succesufully updated!");
//    printf("MAX :%i    ADD :%i \n", tree[v].max, tree[v].add);
    return;
  }
  inc(l, r, val, left, tl, tm);
  inc(l, r, val, right, tm, tr);
  tree[v].max = std::max(tree[left].max, tree[right].max);
}
int get_Y_max(default) {
  if (tl + 1 == tr) return tl;
  if (tree[left].max > tree[right].max) return get_Y_max(left, tl, tm);
  return get_Y_max(right, tm, tr);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    lines.emplace_back(x1, y1, y2, true);
    lines.emplace_back(x2, y1, y2, false);
  }
  std::sort(lines.begin(), lines.end(), comp);


  int cnt = 0, x = 0, y = 0;
  for (line &l : lines) {
//    printf("line -- x:%i  y1:%i  y2:%i  open:%i\n", l.X, l.Y_D, l.Y_U, l.open);
    if (l.open) {
//      printf("args: l:%i  r:%i  val:%i  v:%d  tl:%d  tr:%d\n", l.Y_D, l.Y_U, 1, 0,  -M,  M);
      inc(l.Y_D, l.Y_U + 1, 1, 0,  -M,  M);
    } else {
      if (tree[0].max > cnt) {
//        puts("update");
        x = l.X;
        y = get_Y_max(0, -M, M);
        cnt = tree[0].max;
//        printf("cnt : %i   x : %i   y : %i\n", cnt, x, y);
      }
      inc(l.Y_D, l.Y_U + 1, -1, 0, -M, M);
    }
  }
  std::cout << cnt << '\n' << x << ' ' << y << '\n';
}
