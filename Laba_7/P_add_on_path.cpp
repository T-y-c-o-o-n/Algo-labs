//
// Created by tycoon on 30.05.2020.
//

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

const int E = 0;
class segment_tree {
#define default size_t v, size_t tl, size_t tr
#define mimo (r <= tl || tr <= l)
#define popal (l <= tl && tr <= r)
#define tm ((tl + tr) / 2)
#define left (v * 2 + 1)
#define right (v * 2 + 2)

 private:
  int64_t *t_sum;
  int64_t *t_add;
  size_t n;
  void add(size_t l, size_t r, int64_t val, default) {
    if (mimo) return;
    if (popal) {
      t_add[v] += val;
      return;
    }
    add(l, r, val, left, tl, tm);
    add(l, r, val, right, tm, tr);
  }
  int64_t get(size_t pos, default) {
    if (pos < tl || tr <= pos) return E;
    if (tl + 1 == tr) return t_sum[v] + t_add[v];
    return get(pos, left, tl, tm) + get(pos, right, tm, tr) + t_add[v];
  }

 public:
  explicit segment_tree(size_t n_real) {
    n = 1;
    while (n < n_real) n *= 2;
    t_sum = new int64_t[n * 2 - 1];
    t_add = new int64_t[n * 2 - 1];
    for (size_t i = 0; i < n * 2 - 1; ++i) {
      t_sum[i] = E;
      t_add[i] = E;
    }
    for (size_t pos = 0; pos < n_real; ++pos) {
      t_sum[n - 1 + pos] = 0;
      t_add[n - 1 + pos] = 0;
    }
    for (int v = (int)n - 2; v >= 0; --v) {
      t_sum[v] = t_sum[left] + t_sum[right];
      t_add[v] = 0;
    }
  }
  void set_before_build(size_t pos, int val) const {
    t_sum[n - 1 + pos] = val;
  }
  void build() const {
    for (int v = ((int) n) - 2; v >= 0; --v) {
      t_sum[v] = t_sum[left] + t_sum[right];
      t_add[v] = 0;
    }
  }
  int64_t get(size_t pos) {
    return get(pos, 0, 0, n);
  }
  void add(size_t l, size_t r, int64_t val) {
    add(l, r, val, 0, 0, n);
  }
  void out() {
    puts("tree: {");
    for (size_t pos = 0; pos < 2 * n - 1; ++pos) {
      cout << "i:" << pos << " val:" << t_sum[pos] << "  ";
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
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

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
    if (cmd == "?") {
      v_t v;
      cin >> v;
      cout << path[v] -> get(pos(v)) << '\n';
    }
    if (cmd == "+") {
      v_t v, u;
      int64_t inc;
      cin >> v >> u >> inc;
      while (!in_tree(u, top[v])) {
        path[v] -> add(0, pos(v) + 1, inc);
        v = parent[top[v]];
      }
      while (path[v] != path[u]) {
        path[u] -> add(0, pos(u) + 1, inc);
        u = parent[top[u]];
      }
      if (depth[v] > depth[u]) std::swap(v, u);
      path[v] -> add(pos(v), pos(u) + 1, inc);
    }
  }
}

