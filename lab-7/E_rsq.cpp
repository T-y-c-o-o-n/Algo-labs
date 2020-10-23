//
// Created by tycoon on 18.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

size_t const MAX_N = 500009;
size_t n_real;  // real length of array
size_t n;  // convenient virtual length of array
static int64_t *t_sum = new int64_t[MAX_N * 4 + 9];
int64_t const E = 0;  // neutral element of binary operation

int64_t bin_op(int64_t a, int64_t b) {
  return a + b;
}
int64_t find(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
  if (r <= tl || tr <= l) {
    return E;  // E
  }
  if (l <= tl && tr <= r) {
    return t_sum[v];
  }
  size_t t_mid = (tl + tr) / 2;
  return bin_op(sum(l, r, v * 2 + 1, tl, t_mid), sum(l, r, v * 2 + 2, t_mid, tr));  // bin-op
}
void set(size_t pos, int64_t val, size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    t_sum[v] = val;
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  if (pos < t_mid) {
    set(pos, val, v * 2 + 1, tl, t_mid);
  } else {
    set(pos, val, v * 2 + 2, t_mid, tr);
  }
  t_sum[v] = bin_op(t_sum[v * 2 + 1], t_sum[v * 2 + 2]);  // bin-op
}

void build(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    if (tl < n_real) {
      std::cin >> t_sum[v];
    } else {
      t_sum[v] = E;  // E
    }
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  build(v * 2 + 1, tl, t_mid);
  build(v * 2 + 2, t_mid, tr);
  t_sum[v] = bin_op(t_sum[v * 2 + 1], t_sum[v * 2 + 2]);  // bin-op
}

void out(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    std::cout << t_sum[v] << ' ';
  } else {
    size_t t_mid = (tl + tr) / 2;
    out(v * 2 + 1, tl, t_mid);
    std::cout << t_sum[v] << ' ';
    out(v * 2 + 2, t_mid, tr);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n_real;
  n = 1;
  while (n < n_real) {
    n *= 2;
  }
  build(0, 0, n);
  std::string instr;
  while (std::cin >> instr) {
    if (instr == "set") {
      size_t i;
      int64_t x;
      std::cin >> i >> x;
      set(i - 1, x, 0, 0, n);
    }
    if (instr == "sum") {
      size_t l, r;
      std::cin >> l >> r;
      std::cout << sum(l - 1, r, 0, 0, n) << '\n';
    }
  }
  return 0;
}
