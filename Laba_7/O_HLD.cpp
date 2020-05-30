//
// Created by tycoon on 29.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

const int E = +((int) 1e9);
class segment_tree {
#define default  size_t v, size_t tl, size_t tr
#define tm ((tl + tr) / 2)
#define left (v * 2 + 1)
#define right (v * 2 + 2)

 private:
  int *t_min;
  size_t n;
  int min(size_t l, size_t r, default) {
    if (r <= tl || tr <= l) return E;
    if (l <= tl && tr <= r) return t_min[v];
    return std::min(min(l, r, left, tl, tm), min(l, r, right, tm, tr));
  }

 public:
  explicit segment_tree(size_t n_real) {
    n = 1;
    while (n < n_real) n *= 2;
    t_min = new int[n * 2 - 1];
    for (size_t i = 0; i < n * 2 - 1; ++i) t_min[i] = E;
  }
  void set_before_build(size_t pos, int val) const {
    t_min[n - 1 + pos] = val;
  }
  void build() const {
    for (int v = ((int) n) - 2; v >= 0; --v) {
      t_min[v] = std::min(t_min[left], t_min[right]);
    }
  }
  int min(size_t l, size_t r) {
    return min(l, r, 0, 0, n);
  }
  void out() {
    puts("tree: {");
    for (size_t pos = 0; pos < 2 * n - 1; ++pos) {
      cout << "i:" << pos << " val:" << t_min[pos] << "  ";
    }
    puts("\n}");
  }
};

typedef uint32_t v_t;
v_t const root = 1;
v_t const fict = 0;

using std::vector;

vector<vector<v_t> > children;
vector<int> val;

vector<v_t> parent;
vector<uint32_t> size;
vector<uint32_t> depth;
vector<uint32_t> in;
vector<uint32_t> out;

vector<v_t> heavy;
vector<v_t> top;
vector<segment_tree *> path;

bool in_tree(v_t v, v_t p) {
  return (in[p] <= in[v] && out[v] <= out[p]);
}

size_t pos(v_t v) {
  return depth[v] - depth[top[v]];
}

void hld(v_t top_v) {
  v_t v = top_v;
  uint32_t len = 0;
  do {
    for (auto &u : children[v]) {
      if (u != heavy[v]) {
        hld(u);
      }
    }
    top[v] = top_v;
    len++;
    // инициализировать ДО постепенно при нахождении нового ребра V---heavy[V]
    v = heavy[v];
  } while (v != fict);
  // или проинициализировать ДО размера len здесь после нахождения всех рёбер
  path[top_v] = new segment_tree(len);
  v = top_v;
  do {
    path[v] = path[top_v];
    path[v]->set_before_build(pos(v), val[v]);
    v = heavy[v];
  } while (v != fict);
  path[top_v]->build();
}

void dfs(v_t v, v_t p, uint32_t d) {
  static uint32_t t = 0;
  in[v] = t++;

  parent[v] = p;
  size[v] = 1;
  depth[v] = d;
  for (auto &u : children[v]) {
    dfs(u, v, d + 1);
    size[v] += size[u];
  }
  out[v] = t;
  uint32_t max_size = 0;
  heavy[v] = fict;
  for (auto &u : children[v]) {
    if (size[u] > max_size) {
      max_size = size[u];
      heavy[v] = u;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n;
  cin >> n;

  children.resize(n + 1);
  val.resize(n + 1, E);

  parent.resize(n + 1);
  size.resize(n + 1);
  depth.resize(n + 1);
  in.resize(n + 1);
  out.resize(n + 1);

  heavy.resize(n + 1);

  path.resize(n + 1);
  top.resize(n + 1);

  for (v_t v = 2; v <= n; ++v) {
    v_t p;
    int value;
    cin >> p >> value;
    children[p].push_back(v);
    val[v] = value;
  }

  dfs(root, fict, 0);
  hld(root);

  size_t m;
  cin >> m;

  for (size_t i = 0; i < m; ++i) {
    v_t v, u;
    cin >> v >> u;
    int res = E;
    while (!in_tree(u, top[v])) {
      res = std::min(res, path[v]->min(0, pos(v) + 1));
      v = parent[top[v]];
    }
    while (path[v] != path[u]) {
      res = std::min(res, path[u]->min(0, pos(u) + 1));
      u = parent[top[u]];
    }
    if (depth[v] > depth[u]) std::swap(v, u);
    res = std::min(res, path[v]->min(pos(v) + 1, pos(u) + 1));
    cout << res << '\n';
  }
}
