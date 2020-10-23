//
// Created by tycoon on 23.05.2020.
//
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <iostream>
uint32_t pow2[10], log2[200];

size_t N, M;
struct rect {
  int64_t x1, y1, x2, y2;
  rect(int64_t a, int64_t b, int64_t c, int64_t d) : x1(a), y1(b), x2(c), y2(d) {}
  rect() : x1(0), y1(0), x2(0), y2(0) {}
};
std::istream& operator>>(std::istream &in, rect &a) {
  std::cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
  if (a.x2 < a.x1) std::swap(a.x1, a.x2);
  if (a.y2 < a.y1) std::swap(a.y1, a.y2);
  return in;
}
std::ostream& operator<<(std::ostream &out, rect &a) {
  std::cout << '{' << a.x1 << ' ' << a.y1 << ' ' << a.x2 << ' ' << a.y2 << '}';
  return out;
}
rect sparse_table[130][130][10][10];
int64_t min(int64_t a, int64_t b, int64_t c, int64_t d) {
  return std::min(std::min(a, b), std::min(c, d));
}
int64_t max(int64_t a, int64_t b, int64_t c, int64_t d) {
  return std::max(std::max(a, b), std::max(c, d));
}
int64_t min(int64_t a, int64_t b) {
  return std::min(a, b);
}
int64_t max(int64_t a, int64_t b) {
  return std::max(a, b);
}
rect q_op(rect &a, rect &b, rect &c, rect &d) {
  return {max(a.x1, b.x1, c.x1, d.x1), max(a.y1, b.y1, c.y1, d.y1),
          min(a.x2, b.x2, c.x2, d.x2), min(a.y2, b.y2, c.y2, d.y2)};
}
rect bin_op(rect &a, rect &b) {
  return {max(a.x1, b.x1), max(a.y1, b.y1),
          min(a.x2, b.x2), min(a.y2, b.y2)};
}
void build() {
  for (size_t lg = 1; lg <= log2[M] + 1; ++lg) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (j + pow2[lg] <= M) {
          sparse_table[i][j][0][lg] =
              bin_op(sparse_table[i][j][0][lg-1],
                     sparse_table[i][j+pow2[lg-1]][0][lg-1]);
        }
      }
    }
  }
  for (size_t k1 = 1; k1 <= log2[N] + 1; k1++) {
    for (size_t i = 0; i < N; i++) {
      for (size_t k2 = 0; k2 <= log2[M] + 1; k2++) {
        for (size_t j = 0; j < M; j++) {
          if ((i + pow2[k1] <= N) && (j + pow2[k2] <= M)) {
            sparse_table[i][j][k1][k2] =
                bin_op(sparse_table[i][j][k1-1][k2],
                    sparse_table[i + pow2[k1-1]][j][k1-1][k2]);
          }
        }
      }
    }
  }
}
int64_t query(size_t D, size_t L, size_t U, size_t R) {
  size_t k1 = log2[U-D];
  size_t k2 = log2[R-L];
  rect ans1 = sparse_table[D][L][k1][k2];
  rect ans2 = sparse_table[U-pow2[k1]][L][k1][k2];
  rect ans3 = sparse_table[D][R-pow2[k2]][k1][k2];
  rect ans4 = sparse_table[U-pow2[k1]][R-pow2[k2]][k1][k2];
  rect res = q_op(ans1, ans2, ans3, ans4);
  if (res.x2 < res.x1 || res.y2 < res.y1) return 0;
  return (res.x2 - res.x1) * (res.y2 - res.y1);
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin.tie(nullptr);
  std::cin >> N >> M;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      std::cin >> sparse_table[i][j][0][0];
    }
  }

  pow2[0] = 1;  // степени двойки
  for (int i = 1; i < 10; ++i) {
    pow2[i] = pow2[i-1] * 2;
  }
  log2[0] = -1;  // логарифмы
  log2[1] = 0;
  log2[2] = 1;
  int pnt = 2;
  for (int i = 3; i < 200; ++i) {
    if (pnt * 2 == i) {
      log2[i] = log2[i-1] + 1;
      pnt *= 2;
    } else {
      log2[i] = log2[i-1];
    }
  }

  build();

  int64_t ans = 0;
  int64_t Q, A, B, v;
  std::cin >> Q;
  std::cin >> A >> B >> v;
  const auto mod = (int64_t)(1e9 + 7);
  for (size_t k = 0; k < Q; ++k) {
    size_t r1, c1, r2, c2;
    v = (A * v + B) % mod;
    r1 = static_cast<size_t>(v) % N;
    v = (A * v + B) % mod;
    c1 = static_cast<size_t>(v) % M;
    v = (A * v + B) % mod;
    r2 = static_cast<size_t>(v) % N;
    v = (A * v + B) % mod;
    c2 = static_cast<size_t>(v) % M;
//    std::cin >> r1 >> c1 >> r2 >> c2;
    if (r2 < r1) std::swap(r1, r2);
    if (c2 < c1) std::swap(c1, c2);
    ans = (ans + query(r1, c1, r2 + 1, c2 + 1)) % mod;
  }
  std::cout << ans << '\n';
}
/*
2 3
0 0 14 18   6 11 25 23   9 5 13 15
15 9 5 17   6 25 12 11   16 16 7 14
 */
