//
// Created by tycoon on 22.05.2020.
//
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

uint32_t cur = 0, a, b;

uint32_t next_rand_17() {
  cur = cur * a + b;
  return cur >> 15;
}

uint32_t next_rand_24() {
  cur = cur * a + b;
  return cur >> 8;
}

const size_t N = (1 << 17);  // Размер массива
int f[N];
const int M = (1 << 24);  // Диапазон значений [0 ... 2^24)
int global_id = 0;
struct node {
  int id;
  uint32_t cnt;
  node * left;
  node * right;
  node() : id(++global_id), cnt(0), left(nullptr), right(nullptr) {}
  explicit node(uint32_t c) : id(++global_id), cnt(c), left(nullptr), right(nullptr) {}
  node(uint32_t c, node *l, node *r) : id(++global_id), cnt(c), left(l), right(r) {}
};

std::vector< node * > roots;

node * inc(size_t pos, node * v, size_t tl, size_t tr) {
//  if (roots.size() < 10) {
//    std::cout << "INC!!!!! pos : " << pos << "   ID: "  << v->id
//    << "  TL : " << tl << " TR : " << tr << "   cnt here before inc : " << v->cnt
//              << '\n';
//  }
  if (!v) v = new node;
  if (tl + 1 == tr) return new node(v->cnt + 1);
  size_t t_mid = (tl + tr) / 2;
  if (pos < t_mid) {
    node * new_left = inc(pos, v->left, tl, t_mid);
    return new node(v->cnt + 1, new_left, v->right);
  } else {
    node * new_right = inc(pos, v->right, t_mid, tr);
    return new node(v->cnt + 1, v->left, new_right);
  }
}
node * build(size_t tl, size_t tr) {
  if (tl + 1 == tr) return new node;
  size_t t_mid = (tl + tr) / 2;
  node * left = build(tl, t_mid);
  node * right = build(t_mid, tr);
  return new node(0, left, right);
}
void out(node *v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    std::cout << v->id << ' ';
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  out(v->left, tl, t_mid);
  std::cout << v->id << ' ';
  out(v->right, t_mid, tr);
}
void add_point(int y) {
  if (roots.empty()) {
//    puts("ОПАНА");
//    out(root, 0, M);
//    std::cout << "\n\n";
//    node * root = build(0, M);
  node * root = nullptr;
  root = inc(y, root, 0, M);
    roots.push_back(root);
    return;
  }
  roots.push_back(inc(y, roots.back(), 0, M));
}

uint32_t get_sum(size_t l, size_t r, node *v, size_t tl, size_t tr) {
//  std::cout << "get-sum; L : " << l << " R : " << r << "   ID: "  << v->id
//  << "   TL : " << tl << " TR : " << tr << "   cnt here : " << v->cnt << '\n';
  if (!v || /*tl<=*/tr <= l/*<=r*/ || /*l<=*/r <= tl/*<=tr*/) return 0;
  if (l <= tl && tr <= r) return v->cnt;

  size_t t_mid = (tl + tr) / 2;
  return get_sum(l, r, v->left, tl, t_mid) + get_sum(l, r, v->right, t_mid, tr);
}

uint32_t get_cnt(size_t arr_l, size_t arr_r, int32_t x, int32_t y) {
//  puts("first sum :");
  uint32_t res = get_sum(x, y + 1, roots[arr_r], 0, M);
//  puts("second sum :");
  if (arr_l > 0) res -= get_sum(x, y + 1, roots[arr_l - 1], 0, M);
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t q;
  std::cin >> q >> a >> b;
  for (size_t i = 0; i < N; ++i) {
    f[i] = next_rand_24();
//    f[i] = 0;
//    if (roots.size() < 10) {
//      puts("\nNEW INC!\n\n");
//    }
    add_point(f[i]);
  }

//  uint32_t real_ans = 0;
  uint32_t ans = 0;

  for (size_t j = 0; j < q; ++j) {
    size_t l = next_rand_17(), r = next_rand_17();
    if (l > r) std::swap(l, r);
    int x = next_rand_24(), y = next_rand_24();
//    x = 1;
//    y = 1;
    if (x > y) std::swap(x, y);

//    std::cout << "L : " << l << "  R : " << r << "   X : " << x << "  Y : " << y << '\n';
//    uint32_t real_res = 0;
//    for (size_t i = l; i <= r; ++i) {
//      if (x <= f[i] && f[i] <= y) real_res++;
//    }
//    std::cout << "C : " << real_res << '\n';
//    real_ans += real_res;


  uint32_t res = 0;
  res = get_cnt(l, r, x, y);
//    std::cout << "my res : " << res << "\n\n\n";
  ans += res;
  b += res;
}
//  std::cout << "Real ans : " << real_ans << '\n' << "My ans : " << ans << '\n';
  std::cout << ans << '\n';
}
