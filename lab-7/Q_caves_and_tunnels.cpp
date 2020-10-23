//
// Created by tycoon on 30.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

class segment_tree {
#define default  size_t v, size_t tl, size_t tr
#define tm ((tl + tr) / 2)
#define left (v * 2 + 1)
#define right (v * 2 + 2)
  const int E = -((int)1e9);

 private:
  int *t_max;
  size_t n;
  int max(size_t l, size_t r, default) {
    if (r <= tl || tr <= l) return E;
    if (l <= tl && tr <= r) return t_max[v];
    return std::max(max(l, r, left, tl, tm), max(l, r, right, tm, tr));
  }
  void inc(size_t pos, int val, default) const {
    if (pos < tl || tr <= pos) return;
    if (tl + 1 == tr) {
      t_max[v] += val;
      return;
    }
    inc(pos, val, left, tl, tm);
    inc(pos, val, right, tm, tr);
    t_max[v] = std::max(t_max[left], t_max[right]);
  }

 public:
  explicit segment_tree(size_t n_real) {
    n = 1;
    while (n < n_real) n *= 2;
    t_max = new int[n * 2 - 1];
    for (size_t i = 0; i < n * 2 - 1; ++i) t_max[i] = E;
    for (size_t pos = 0; pos < n_real; ++pos) {
      t_max[n - 1 + pos] = 0;
    }
    for (int v = (int)n - 2; v >= 0; --v) {
      t_max[v] = std::max(t_max[left], t_max[right]);
    }
  }
  void set_before_build(size_t pos, int val) const {
    t_max[n - 1 + pos] = val;
  }
  void build() const {
    for (int v = ((int) n) - 2; v >= 0; --v) {
      t_max[v] = std::max(t_max[left], t_max[right]);
    }
  }
  void inc(size_t pos, int val) {
    inc(pos, val, 0, 0, n);
  }
  int max(size_t l, size_t r) {
    return max(l, r + 1, 0, 0, n);
  }
  void out() {
    puts("tree: {");
    for (size_t pos = 0; pos < 2 * n - 1; ++pos) {
      cout << "i:" << pos << " val:" << t_max[pos] << "  ";
    }
    puts("\n}");
  }
};

typedef uint32_t v_t;
v_t const root = 1;
v_t const fict = 0;

using std::vector;

vector<vector<v_t> > edges;
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
    for (auto &u : edges[v]) {
      if (u != parent[v] && u != heavy[v]) {
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
    v = heavy[v];
  } while (v != fict);
//  cout << top_v << ":\n";
//  path[top_v] -> out();
}

void dfs(v_t v, v_t p, uint32_t d) {
  static uint32_t t = 0;
  in[v] = t++;

  parent[v] = p;
  size[v] = 1;
  depth[v] = d;
  for (auto &u : edges[v]) {
    if (u == p) continue;
    dfs(u, v, d + 1);
    size[v] += size[u];
  }
  out[v] = t;
  uint32_t max_size = 0;
  heavy[v] = fict;
  for (auto &u : edges[v]) {
    if (u == p) continue;
    if (size[u] > max_size) {
      max_size = size[u];
      heavy[v] = u;
    }
  }
}

int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(nullptr);
//  std::cout.tie(nullptr);

  size_t n;
  cin >> n;

  edges.resize(n + 1);
  val.resize(n + 1, 0);

  parent.resize(n + 1);
  size.resize(n + 1);
  depth.resize(n + 1);
  in.resize(n + 1);
  out.resize(n + 1);

  heavy.resize(n + 1);

  path.resize(n + 1);
  top.resize(n + 1);

  for (size_t i = 1; i < n; ++i) {
    v_t v, u;
    cin >> v >> u;
    edges[v].push_back(u);
    edges[u].push_back(v);
  }

  dfs(root, fict, 0);
  hld(root);

  size_t m;
  cin >> m;

  std::string cmd;
  for (size_t i = 0; i < m; ++i) {
    cin >> cmd;
    if (cmd == "I") {
      v_t v;
      int value;
      cin >> v >> value;
      val[v] += value;
      path[v]->inc(pos(v), value);
    }
    if (cmd == "G") {
      v_t v, u;
      cin >> v >> u;
      int res = std::max(val[v], val[u]);
      while (!in_tree(u, top[v])) {
//        cout << v << ' ' << u << ' ' << top[v] << '\n';
        res = std::max(res, path[v] -> max(0, pos(v)));
        v = parent[top[v]];
      }
      while (path[v] != path[u]) {
//        cout << v << ' ' << u << ' ' << top[u] << '\n';
        res = std::max(res, path[u] -> max(0, pos(u)));
        u = parent[top[u]];
      }
      if (depth[v] > depth[u]) std::swap(v, u);
      res = std::max(res, path[v] -> max(pos(v), pos(u)));
      cout << res << '\n';
    }
  }
}
