//
// Created by tycoon on 24.05.2020.
//
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>

size_t max_n_x, max_n_y, max_n_z;
size_t n_x, n_y, n_z;

struct node {
  uint32_t sum;  // сумма в кубе
  uint32_t add;  // сколько нужно прибавить каждому элементу в кубе
  node *son1;
  node *son2;
  node *son3;
  node *son4;
  node *son5;
  node *son6;
  node *son7;
  node *son8;
  node() : sum(0), add(0), son1(nullptr), son2(nullptr), son3(nullptr), son4(nullptr),
  son5(nullptr), son6(nullptr), son7(nullptr), son8(nullptr) {}
};
node * root = nullptr;
#define default node * v, size_t tlX, size_t trX, size_t tlY, size_t trY, size_t tlZ, size_t trZ
#define s1 v->son1
#define s2 v->son2
#define s3 v->son3
#define s4 v->son4
#define s5 v->son5
#define s6 v->son6
#define s7 v->son7
#define s8 v->son8
#define t1 tlX, tmX, tlY, tmY, tlZ, tmZ
#define t2 tlX, tmX, tmY, trY, tlZ, tmZ
#define t3 tmX, trX, tlY, tmY, tlZ, tmZ
#define t4 tmX, trX, tmY, trY, tlZ, tmZ
#define t5 tlX, tmX, tlY, tmY, tmZ, trZ
#define t6 tlX, tmX, tmY, trY, tmZ, trZ
#define t7 tmX, trX, tlY, tmY, tmZ, trZ
#define t8 tmX, trX, tmY, trY, tmZ, trZ
#define tmX ((tlX + trX) / 2)
#define tmY ((tlY + trY) / 2)
#define tmZ ((tlZ + trZ) / 2)
#define mimo (trX <= lX || rX <= tlX || trY <= lY || rY <= tlY || trZ <= lZ || rZ <= tlZ)
#define popal (lX <= tlX && trX <= rX && lY <= tlY && trY <= rY && lZ <= tlZ && trZ <= rZ)
#define mn std::min
#define mx std::max
#define len_cross (mn(rX, trX)-mx(lX, tlX))*(mn(rY, trY)-mx(lY, tlY))*(mn(rZ, trZ)-mx(lZ, tlZ))
uint32_t sum(size_t lX, size_t rX, size_t lY, size_t rY, size_t lZ, size_t rZ, default) {
  if (!v) return 0;
  if (mimo) return 0;
  if (popal) {
    return v->sum
        + v->add * len_cross;
  }
  return v->add * len_cross
      + sum(lX, rX, lY, rY, lZ, rZ, s1, t1) + sum(lX, rX, lY, rY, lZ, rZ, s2, t2)
      + sum(lX, rX, lY, rY, lZ, rZ, s3, t3) + sum(lX, rX, lY, rY, lZ, rZ, s4, t4)
      + sum(lX, rX, lY, rY, lZ, rZ, s5, t5) + sum(lX, rX, lY, rY, lZ, rZ, s6, t6)
      + sum(lX, rX, lY, rY, lZ, rZ, s7, t7) + sum(lX, rX, lY, rY, lZ, rZ, s8, t8);
}
node * add(size_t lX, size_t rX, size_t lY, size_t rY, size_t lZ, size_t rZ, size_t val, default) {
  if (mimo) {
    return v;
  }
  if (!v) v = new node;
  if (popal) {
    v->add += val;
    return v;
  }
  v->sum += val * len_cross;
  s1 = add(lX, rX, lY, rY, lZ, rZ, val, s1, t1);
  s2 = add(lX, rX, lY, rY, lZ, rZ, val, s2, t2);
  s3 = add(lX, rX, lY, rY, lZ, rZ, val, s3, t3);
  s4 = add(lX, rX, lY, rY, lZ, rZ, val, s4, t4);
  s5 = add(lX, rX, lY, rY, lZ, rZ, val, s5, t5);
  s6 = add(lX, rX, lY, rY, lZ, rZ, val, s6, t6);
  s7 = add(lX, rX, lY, rY, lZ, rZ, val, s7, t7);
  s8 = add(lX, rX, lY, rY, lZ, rZ, val, s8, t8);
  return v;
}
int main() {
  std::cin >> n_x >> n_y >> n_z;
  max_n_x = 1;
  while (max_n_x < n_x) max_n_x *= 2;
  max_n_y = 1;
  while (max_n_y < n_y) max_n_y *= 2;
  max_n_z = 1;
  while (max_n_z < n_z) max_n_z *= 2;
  int q;
  std::cin >> q;
  while (q--) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "o") {
      for (size_t i = 0; i < n_x; ++i) {
        for (size_t j = 0; j < n_y; ++j) {
          for (size_t k = 0; k < n_z; ++k) {
            std::cout << sum(i, i + 1, j, j + 1, k,
                k + 1, root, 0, max_n_x, 0, max_n_y, 0, max_n_z);
          }
          std::cout << '\n';
        }
        std::cout << "END OF MATRIX\n";
      }
      continue;
    }
    size_t x1, x2, y1, y2, z1, z2;
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    if (cmd == "a") {
      uint32_t v;
      std::cin >> v;
      root = add(x1, x2, y1, y2, z1, z2, v, root, 0, max_n_x, 0, max_n_y, 0, max_n_z);
    }
    if (cmd == "s") {
      std::cout << sum(x1, x2, y1, y2, z1, z2, root, 0, max_n_x, 0, max_n_y, 0, max_n_z) << '\n';
    }
  }
}
/*
   0 0 0 3 2 4
 7
 a 0 0 0 1 2 3 5
 o
 s 1 1 1 2 2 2
 a 1 1 2 3 2 4 3
 o
 s 0 0 0 2 2 2
 s 0 0 0 3 2 4
 */
