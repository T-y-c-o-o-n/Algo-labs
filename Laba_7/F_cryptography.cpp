//
// Created by tycoon on 18.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

struct matrix {
  int64_t val[2][2];
  matrix(int64_t a11, int64_t a12, int64_t a21, int64_t a22) {
    val[0][0] = a11;
    val[0][1] = a12;
    val[1][0] = a21;
    val[1][1] = a22;
  }
  matrix() {
    val[0][0] = val[1][1] = 0;
    val[0][1] = val[1][0] = 0;
  }
};

std::ostream& operator<<(std::ostream& out, matrix m) {
  out << m.val[0][0] << ' ' << m.val[0][1] << '\n';
  out << m.val[1][0] << ' ' << m.val[1][1] << '\n';
  return out;
}
std::istream& operator>>(std::istream& in, matrix& m) {
  int64_t a, b, c, d;
  std::cin >> a >> b >> c >> d;
  m = matrix(a, b, c, d);
  return in;
}

size_t const MAX_N = 500009;
size_t n_real;  // real length of array
size_t n;  // convenient virtual length of array
matrix *t_prod = new matrix[MAX_N * 4 + 9];
matrix const E(1, 0, 0, 1);  // Нейтральный элемент бинарной операции
int64_t mod;

matrix bin_op(matrix a, matrix b) {
  return {(a.val[0][0] * b.val[0][0] + a.val[0][1] * b.val[1][0]) % mod,
          (a.val[0][0] * b.val[0][1] + a.val[0][1] * b.val[1][1]) % mod,
      (a.val[1][0] * b.val[0][0] + a.val[1][1] * b.val[1][0]) % mod,
      (a.val[1][0] * b.val[0][1] + a.val[1][1] * b.val[1][1]) % mod};
}
matrix prod(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
  if (r <= tl || tr <= l) {
    return E;  // E
  }
  if (l <= tl && tr <= r) {
    return t_prod[v];
  }
  size_t t_mid = (tl + tr) / 2;
  return bin_op(prod(l, r, v * 2 + 1, tl, t_mid), prod(l, r, v * 2 + 2, t_mid, tr));  // bin-op
}
void set(size_t pos, matrix val, size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    t_prod[v] = val;
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  if (pos < t_mid) {
    set(pos, val, v * 2 + 1, tl, t_mid);
  } else {
    set(pos, val, v * 2 + 2, t_mid, tr);
  }
  t_prod[v] = bin_op(t_prod[v * 2 + 1], t_prod[v * 2 + 2]);  // bin-op
}

void build(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    if (tl < n_real) {
      std::cin >> t_prod[v];
    } else {
      t_prod[v] = E;  // E
    }
    return;
  }
  size_t t_mid = (tl + tr) / 2;
  build(v * 2 + 1, tl, t_mid);
  build(v * 2 + 2, t_mid, tr);
  t_prod[v] = bin_op(t_prod[v * 2 + 1], t_prod[v * 2 + 2]);  // bin-op
}

void out(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    std::cout << t_prod[v] << ' ';
  } else {
    size_t t_mid = (tl + tr) / 2;
    out(v * 2 + 1, tl, t_mid);
    std::cout << t_prod[v] << ' ';
    out(v * 2 + 2, t_mid, tr);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t m;
  std::cin >> mod >> n_real >> m;
  n = 1;
  while (n < n_real) {
    n *= 2;
  }
  build(0, 0, n);
  for (size_t i = 0; i < m; ++i) {
    size_t l, r;
    std::cin >> l >> r;
    std::cout << prod(l - 1, r, 0, 0, n) << '\n';
  }
  return 0;
}
