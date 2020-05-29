//
// Created by tycoon on 25.05.2020.
//
#include <cstdint>
#include <iostream>
#include <vector>
#include <cassert>

uint32_t const root = 1;
std::vector<uint32_t> depth;
std::vector< std::vector<uint32_t> > jmp;
std::vector<uint32_t> log;
std::vector<uint32_t> pow;

uint32_t jump(uint32_t v, uint32_t k) {
  if (jmp[v].size() <= k) {
    return root;
  }
  return jmp[v][k];
}

uint32_t jump_d(uint32_t v, uint32_t d) {
  while (d != 0) {
    uint32_t k = log[d];
    v = jump(v, k);
    d -= pow[k];
  }
  return v;
}

int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(nullptr);
//  std::cout.tie(nullptr);

  size_t KK;
  std::cin >> KK;

  log.resize(std::max(size_t(10), KK + 9));
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

  std::string cmd;
  for (size_t i = 0; i < KK; ++i) {
    std::cin >> cmd;
    if (cmd == "OUT") {
      std::cout << "\nDEPTH:\n";
      for (size_t v = 0; v < depth.size(); ++v) {
        std::cout << v << ' ' << depth[v] << '\n';
      }
      std::cout << '\n';
      std::cout << "V ";
      for (size_t j = 0; j < 10; ++j) {
        std::cout << j << ' ';
      }
      std::cout << "\nJMP:\n";
      for (size_t v = 0; v < jmp.size(); ++v) {
        std::cout << v << ' ';
        for (size_t k = 0; k < jmp[v].size(); ++k) {
          std::cout << jmp[v][k] << ' ';
        }
        std::cout << '\n';
      }
      std::cout << "\n\n\n";
    }
    if (cmd == "ADD") {
      uint32_t p, v;
      std::cin >> p >> v;
      depth.resize(v + 1);
      depth[v] = depth[p] + 1;
      jmp.resize(v + 1);
      jmp[v].resize(log[depth[v]] + 3);

      int32_t u = p;
      for (size_t j = 0; j < jmp[v].size(); ++j) {
        jmp[v][j] = u;
        u = jump(u, j);
      }
    }
    if (cmd == "GET") {
      uint32_t v, u;
      std::cin >> v >> u;
      if (depth[v] < depth[u]) std::swap(v, u);
      v = jump_d(v, (depth[v] - depth[u]));
      if (v == u) {
        std::cout << u << '\n';
        continue;
      }
//      std::cout << "identical?" << (jmp[v].size() == jmp[u].size()
//      && depth[v] == depth[u]) << '\n';
      uint32_t k = jmp[v].size();
      while (true) {
        uint32_t v_k = jump(v, k);
        uint32_t u_k = jump(u, k);
        if (v_k == u_k) {
          if (k == 0) {
            std::cout << v_k << '\n';
            break;
          }
          k--;
        } else {
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

