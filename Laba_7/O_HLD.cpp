//
// Created by tycoon on 29.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

const int E = (int) 1e9;
#define default  size_t v, size_t tl, size_t tr
#define tm ((tl + tr) / 2)
#define left (v * 2 + 1)
#define right (v * 2 + 2)
struct path {  // Segment Tree actually
  int * t_min;
  size_t n;
  explicit path(size_t n_real) {
    n = 1;
    while (n < n_real) n *= 2;
    t_min = new int[n * 2 + 3];
    for (size_t i = 0; i < n; ++i) t_min[i] = E;
  }
  void set_before_build(size_t pos, int val) {
    t_min[n - 1 + pos] = val;
  }
  void build() {
    for (size_t v = n - 2; ; --v) {
      t_min[v] = std::min(t_min[left], t_min[right]);
      if (v == 0) return;
    }
  }
  int min(size_t l, size_t r, default) {
    if (r <= tl || tr <= l) return E;
    if (l <= tl && tr <= r) return t_min[v];
    return std::min(min(l, r, left, tl, tm), min(l, r, right, tm, tr));
  }
};

typedef uint32_t v_t;

std::vector< std::vector<v_t> > children;
std::vector<uint32_t> size;
std::vector<uint32_t> depth;
//std::vector<uint32_t> pos;
std::vector<v_t> top;
std::vector<v_t> heavy;
std::vector<v_t> parent;
std::vector<path *> tree;

size_t pos(v_t v) {
  return depth[v] - depth[top[v]];
}

void build_tree(v_t top_v) {
  v_t v = top_v;
  uint32_t len = 0;
  while (heavy[v] != -1) {
    v = heavy[v];
    top[v] = top_v;
    // инициализировать ДО постепенно при нахождении нового ребра V---p[V]
    len++;
  }
  // или проинициализировать ДО размера len здесь после нахождения всех рёбер
  tree[top_v] = new path(len);
  v_t u = top_v;
  while (u != v) {

    u = heavy[v];
  }
}

void dfs(v_t v, v_t p, uint32_t d) {
  depth[v] = d;
  parent[v] = p;
  size[v] = 1;
//  if (children[v].empty()) return;
  for (auto &u : children[v]) {
    dfs(u, v, d + 1);
    size[v] += size[u];
  }
  uint32_t max_size = 0;
  heavy[v] = -1;
  for (auto &u : children[v]) {
    if (size[u] > max_size) {
      max_size = size[u];
      heavy[v] = u;
    }
  }
  for (auto &u : children[v]) {
    if (u != heavy[v]) {
      build_tree(u);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n;
}
