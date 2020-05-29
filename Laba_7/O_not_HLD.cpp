//
// Created by tycoon on 25.05.2020.
//
#include <cstdint>
#include <iostream>
#include <vector>
#include <cassert>

typedef uint32_t v_t;
typedef std::pair<int, v_t> piv;

v_t const root = 1;
std::vector<std::vector<v_t> > jmp;
std::vector<std::vector<int> > jmp_min;
std::vector<int> val;
std::vector<v_t> depth;
std::vector<uint32_t> log;
std::vector<uint32_t> pow;

v_t jump(v_t v, uint32_t k) {
  if (jmp[v].size() <= k) {
    return root;
  }
  return jmp[v][k];
}

v_t jump_d(v_t v, uint32_t d) {
  while (d != 0) {
    uint32_t k = log[d];
    v = jump(v, k);
    d -= pow[k];
  }
  return v;
}

int jump_d_min(v_t v, uint32_t d);

int jump_min(v_t v, uint32_t k) {
//  std::cout << v << " " << k << " " << jmp_min[v][k] << '\n';
//  if (jmp_min[v].size() <= k) {
//    return jump_d_min(v, depth[v]);
//  }
  return jmp_min[v][k];
}

int jump_d_min(v_t v, uint32_t d) {
//  std::cout << v << ' ' << d << '\n';
  int res = (int) 1e9;
  while (d != 0) {
    uint32_t k = log[d];
    res = std::min(res, jump_min(v, k));
    v = jump(v, k);
//    std::cout << res << '\n';
    d -= pow[k];
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n;
  std::cin >> n;

  log.resize(std::max(size_t(10), n + 9));
  log[0] = 0;
  log[1] = 0;
  log[2] = 1;
  for (size_t i = 3; i < log.size(); ++i) {
    log[i] = log[i / 2] + 1;
  }

  pow.resize(31);
  pow[0] = 1;
  pow[1] = 2;
  for (size_t i = 2; i < pow.size(); ++i) {
    pow[i] = pow[i - 1] * 2;
  }

  depth.resize(2);
  depth[root] = 0;
  jmp.resize(2);
  jmp[root].resize(3, root);
  jmp_min.resize(2);
  jmp_min[root].resize(3, (int) 1e9);
  val.resize(2, (int) 1e9);

  for (v_t v = 2; v <= n; ++v) {
    v_t p;
    int val_edge;
    std::cin >> p >> val_edge;
    depth.resize(v + 1);
    depth[v] = depth[p] + 1;
    jmp.resize(v + 1);
    jmp[v].resize(log[depth[v]] + 1);
    jmp_min.resize(v + 1);
    jmp_min[v].resize(log[depth[v]] + 1, (int) 1e9);
    val.resize(v + 1);
    val[v] = val_edge;

    jmp[v][0] = p;
    jmp_min[v][0] = val[v];
    for (size_t j = 1; j < jmp[v].size(); ++j) {
      jmp[v][j] = jmp[jmp[v][j - 1]][j - 1];
      jmp_min[v][j] = std::min(jmp_min[v][j - 1], jmp_min[jmp[v][j - 1]][j - 1]);
    }
  }

  size_t KK;
  std::cin >> KK;
  std::string cmd = "GET";
  for (size_t i = 0; i < KK; ++i) {
//    std::cin >> cmd;
    if (cmd == "OUT") {
      std::cout << "\nDEPTH:\n";
      for (v_t v = 0; v < depth.size(); ++v) {
        std::cout << v << ' ' << depth[v] << '\n';
      }
      std::cout << '\n';
      std::cout << "V ";
      for (size_t j = 0; j < 10; ++j) {
        std::cout << j << ' ';
      }
      std::cout << "\nJMP:\n";
      for (v_t v = 0; v < jmp_min.size(); ++v) {
        std::cout << v << ' ';
        for (uint32_t k = 0; k < jmp_min[v].size(); ++k) {
          std::cout << jmp[v][k] << ' ';
        }
        std::cout << '\n';
      }
      std::cout << "\n\n\n";
    }
    if (cmd == "GET") {
      v_t v, u;
      std::cin >> v >> u;
      if (depth[v] < depth[u]) std::swap(v, u);
      int res_v = (int) 1e9, res_u = (int) 1e9;
      res_v = jump_d_min(v, (depth[v] - depth[u]));
      v = jump_d(v, (depth[v] - depth[u]));
      if (v == u) {
        std::cout << res_v << '\n';
        continue;
      }
//      std::cout << "identical?" << (jmp[v].size() == jmp[u].size()
//      && depth[v] == depth[u]) << '\n';
      v_t k = jmp[v].size();
      while (true) {
        v_t v_k = jump(v, k);
        v_t u_k = jump(u, k);
        if (v_k == u_k) {
          if (k == 0) {
            res_v = std::min(res_v, jump_min(v, 0));
            res_u = std::min(res_u, jump_min(u, 0));
//            std::cout << v_k << '\n';
            std::cout << std::min(res_v, res_u) << '\n';
            break;
          }
          k--;
        } else {
          res_v = std::min(res_v, jump_min(v, k));
          res_u = std::min(res_u, jump_min(u, k));
          v = v_k;
          u = u_k;
        }
      }
//      std::cout << jmp[v][0] << '\n';
    }
  }
}
/*
30
ADD 1 2
ADD 2 3
ADD 2 4
ADD 1 5
ADD 5 6
ADD 5 7
ADD 7 8
ADD 8 9

GET 9 3 - 5
*/
