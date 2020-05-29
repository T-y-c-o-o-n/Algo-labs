//
// Created by tycoon on 25.05.2020.
//
#include <cstdint>
#include <iostream>
#include <vector>

uint64_t n;
uint64_t const root = 0;
std::vector<uint64_t> depth;
std::vector<std::vector<uint64_t> > jmp;
std::vector<std::vector<uint64_t> > children;
std::vector<uint64_t> log;
std::vector<uint64_t> pow;

uint64_t jump(uint64_t v, uint64_t k) {
  if (jmp[(size_t)v].size() <= k) {
    return root;
  }
  return jmp[(size_t)v][(size_t)k];
}

uint64_t jump_d(uint64_t v, uint64_t d) {
  while (d != 0) {
    uint64_t k = log[(size_t)d];
    v = jump(v, k);
    d -= pow[(size_t)k];
  }
  return v;
}

void dfs(uint64_t p, uint64_t v, uint64_t v_depth) {
//  std::cout << "dfs " << p << ' ' << v << '\n';
  depth[(size_t)v] = v_depth;
  if (v != root) {
    jmp[(size_t)v].resize((size_t)log[(size_t)v_depth] + 3);
    uint64_t u = p;
    for (uint64_t j = 0; j < jmp[(size_t)v].size(); ++j) {
      jmp[(size_t)v][(size_t)j] = u;
      u = jump(u, j);
    }
  } else {
    jmp[(size_t)root].resize(3, root);
  }
  for (auto u : children[(size_t)v]) {
    dfs(v, u, v_depth + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n;
  uint64_t m;
  std::cin >> m;

  log.resize((size_t)std::max(uint64_t(10), n + 9));
  log[1] = 0;
  log[2] = 1;
  for (size_t i = 3; i < log.size(); ++i) {
    log[i] = log[i / 2] + 1;
  }
  pow.resize(32);
  pow[0] = 1;
  pow[1] = 2;
  for (size_t i = 2; i < pow.size(); ++i) {
    pow[i] = pow[i - 1] * 2;
  }

  depth.resize((size_t)n);
  jmp.resize((size_t)n);
  children.resize((size_t)n);
  for (uint64_t v = 1; v < n; ++v) {
    uint64_t p;
    std::cin >> p;
    children[(size_t)p].push_back(v);
  }
  dfs(-1, root, 0);

  std::vector<uint64_t> a;
  a.resize(2 * (size_t)m + 9);
  uint64_t x, y, z;
  std::cin >> a[1] >> a[2] >> x >> y >> z;
  for (size_t i = 3; i < 2 * m + 9; ++i) {
    a[i] = (x * a[i - 2] + y * a[i - 1] + z) % (n);
  }

  uint64_t ans = 0;
  uint64_t res = 0;
  for (size_t i = 1; i <= m; ++i) {
    uint64_t v, u;
//    std::cin >> v >> u;
    v = (a[2 * i - 1] + res) % (n);
    u = a[2 * i];

    if (depth[(size_t)v] < depth[(size_t)u]) std::swap(v, u);
    v = jump_d(v, (depth[(size_t)v] - depth[(size_t)u]));
    if (v == u) {
//      std::cout << u << '\n';
      res = u;
      ans += res;
      continue;
    }
    uint64_t k = jmp[(size_t)v].size();
    while (true) {
      uint64_t v_k = jump(v, k);
      uint64_t u_k = jump(u, k);
      if (v_k == u_k) {
        if (k == 0) {
//          std::cout << v_k << '\n';
          res = v_k;
          ans += res;
          break;
        }
        k--;
      } else {
        v = v_k;
        u = u_k;
      }
    }
  }
  std::cout << ans << '\n';
}
