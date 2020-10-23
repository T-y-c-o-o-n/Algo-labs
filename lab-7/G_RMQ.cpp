//

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

const int64_t E_set = int64_t(1e18+9);
struct node {
  int64_t min;
  int64_t add;
  int64_t set;
  node(int64_t val) {
    min = val;
    add = 0;
    set = E_set;
  }
  node() {
    min = INT64_MAX;
    add = 0;
    set = E_set;
  }
};


size_t const MAX_N = 500009;
size_t n_real;  // real length of array
size_t n;  // convenient virtual length of array

static node *tree = new node[MAX_N * 4 + 9];
#define left (2 * v + 1)
#define right (2 * v + 2)
#define t_mid ((tl + tr) / 2)
node const E = {INT64_MAX};  // neutral element of binary operation
bool operator==(node const& a, node const& b) {
  return a.min == b.min && a.add == b.add && a.set == b.set;
}
std::istream& operator>>(std::istream& in, node& a) {
  in >> a.min;
  a.set = E_set;
  a.add = 0;
  return in;
}
std::ostream& operator<<(std::ostream& out, node const& a) {
  if (a == E) {
    out << 'E';
  } else {
    out << a.min;
  }
  return out;
}
node bin_op(node a, node b) {
  return { std::min(a.min, b.min) };
}
void propagate(size_t v, size_t tl, size_t tr) {
  int64_t set = tree[v].set;
  int64_t add = tree[v].add;
  tree[v].set = E_set;
  tree[v].add = 0;
  if (set != E_set) {
    if (tl + 1 < tr) {
      tree[left].min = set;
      tree[right].min = set;
//      if (tree[left].add != 0) propagate(left, tl, t_mid);
//      if (tree[right].add != 0) propagate(right, t_mid, tr);
      tree[left].add = 0;
      tree[right].add = 0;
      tree[left].set = set;
      tree[right].set = set;
    }
  }
  if (add != 0) {
    if (tl + 1 < tr) {
      tree[left].min += add;
      tree[right].min += add;
//      if (tree[left].set != E_set) propagate(left, tl, t_mid);
//      if (tree[right].set != E_set) propagate(right, t_mid, tr);
      tree[left].add += add;
      tree[right].add += add;
    }
  }
}
node min(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
  propagate(v, tl, tr);
  if (r <= tl || tr <= l) return E;
  if (l <= tl && tr <= r) return tree[v];
  return bin_op(min(l, r, v * 2 + 1, tl, t_mid), min(l, r, v * 2 + 2, t_mid, tr));
}
void add(size_t l, size_t r, int64_t val, size_t v, size_t tl, size_t tr) {
  propagate(v, tl, tr);
  if (r <= tl || tr <= l) return;
  if (l <= tl && tr <= r) {
    tree[v].min += val;
    tree[v].add = val;
    return;
  }
  add(l, r, val, 2 * v + 1, tl, t_mid);
  add(l, r, val, 2 * v + 2, t_mid, tr);
  tree[v] = bin_op(tree[2 * v + 1], tree[2 * v + 2]);
}
void set(size_t l, size_t r, int64_t val, size_t v, size_t tl, size_t tr) {
  propagate(v, tl, tr);
//  std::cout << v << " " << tl << " " << tr << '\n';
  if (r <= tl || tr <= l) {
//    puts("nope");
    return;
  }
  if (l <= tl && tr <= r) {
//    puts("here we stop");
    tree[v].min = val;
    tree[v].set = val;
    return;
  }
  set(l, r, val, 2 * v + 1, tl, t_mid);
  set(l, r, val, 2 * v + 2, t_mid, tr);
  tree[v] = bin_op(tree[2 * v + 1], tree[2 * v + 2]);
}
void build(size_t v, size_t tl, size_t tr) {
  if (tl + 1 == tr) {
    if (tl < n_real) {
      std::cin >> tree[v];
    } else {
      tree[v] = E;  // E
    }
    return;
  }
  build(v * 2 + 1, tl, t_mid);
  build(v * 2 + 2, t_mid, tr);
  tree[v] = bin_op(tree[v * 2 + 1], tree[v * 2 + 2]);  // bin-op
}

void out(size_t v, size_t tl, size_t tr) {
  propagate(v, tl, tr);
  if (tl + 1 == tr) {
    std::cout << tree[v] << ' ';
  } else {
    out(v * 2 + 1, tl, t_mid);
    std::cout << tree[v] << ' ';
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
      size_t l, r;
      int64_t x;
      std::cin >> l >> r >> x;
      set(l - 1, r, x, 0, 0, n);
    }
    if (instr == "add") {
      size_t l, r;
      int64_t x;
      std::cin >> l >> r >> x;
      add(l - 1, r, x, 0, 0, n);
    }
    if (instr == "min") {
      size_t l, r;
      std::cin >> l >> r;
      std::cout << min(l - 1, r, 0, 0, n) << '\n';
    }
//    out(0, 0, n);
//    std::cout << '\n';
  }
  return 0;
}
