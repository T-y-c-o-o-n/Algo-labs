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
static int32_t *t_park = new int32_t[MAX_N * 4 + 9];
int32_t const E = -1;  // neutral element of binary operation

int32_t bin_op(int32_t a, int32_t b) {
  return a == E ? b : a;
}
int32_t find(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
  if (r <= tl || tr <= l) {
    return E;  // E
  }
  if (l <= tl && tr <= r) {
    return t_park[v];
  }
  size_t t_mid = (tl + tr) / 2;
  return bin_op(find(l, r, v * 2 + 1, tl, t_mid), find(l, r, v * 2 + 2, t_mid, tr));  // bin-op
}
void park_or_unpark(size_t pos, size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    if (t_park[v] == -1) {
      t_park[v] = tl;
    } else {
      t_park[v] = -1;
    }
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  if (pos < t_mid) {
    park_or_unpark(pos, v * 2 + 1, tl, t_mid);
  } else {
    park_or_unpark(pos, v * 2 + 2, t_mid, tr);
  }
  t_park[v] = bin_op(t_park[v * 2 + 1], t_park[v * 2 + 2]);  // bin-op
}

void build(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    if (tl < n_real) {
      t_park[v] = tl;
    } else {
      t_park[v] = E;  // E
    }
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  build(v * 2 + 1, tl, t_mid);
  build(v * 2 + 2, t_mid, tr);
  t_park[v] = bin_op(t_park[v * 2 + 1], t_park[v * 2 + 2]);  // bin-op
}

void out(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    std::cout << t_park[v] << ' ';
  } else {
    size_t t_mid = (tl + tr) / 2;
    out(v * 2 + 1, tl, t_mid);
    std::cout << t_park[v] << ' ';
    out(v * 2 + 2, t_mid, tr);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t m;
  std::cin >> n_real >> m;
  n = 1;
  while (n < n_real) {
    n *= 2;
  }
  build(0, 0, n);
  for (size_t i = 0; i < m; ++i) {
    std::string instr;
    std::cin >> instr;
    if (instr == "exit") {
      size_t x;
      std::cin >> x;
      park_or_unpark(x - 1, 0, 0, n);
    }
    if (instr == "enter") {
      int32_t pos;
      std::cin >> pos;
      pos = find(pos - 1, n_real, 0, 0, n);
      if (pos == -1) pos = find(0, n_real, 0, 0, n);
      park_or_unpark(pos, 0, 0, n);
      std::cout << pos + 1 << '\n';
    }
  }
  return 0;
}
