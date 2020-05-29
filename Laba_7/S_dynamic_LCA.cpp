//
// Created by tycoon on 27.05.2020.
//
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

std::vector<uint32_t> in, out;
std::vector< std::vector<uint32_t> > edges;
std::vector<std::pair<uint32_t, uint32_t> > arr;  // <depth, vertex>
std::vector<size_t> ind;

uint32_t t;

void dfs(uint32_t p, uint32_t v, uint32_t depth) {
  in[v] = t++;
  ind[v] = arr.size();
  arr.emplace_back(depth, v);
  for (uint32_t u : edges[v]) {
    if (u == p) continue;
    dfs(v, u, depth + 1);
    arr.emplace_back(depth, v);
  }
  out[v] = t;
}

std::vector< std::vector< std::pair<uint32_t, uint32_t> > > RMQ;
size_t pow2[31];
size_t log2[500000];

void build_RMQ() {
  RMQ.assign(arr.size(), std::vector<std::pair<uint32_t, uint32_t> >(log2[arr.size()] + 1));
  for (size_t l = 0; l < arr.size(); ++l) {
    RMQ[l][0] = arr[l];
  }
  for (size_t k = 1; k <= log2[arr.size()] + 1; ++k) {
    for (size_t L = 0; L + pow2[k] <= arr.size(); ++L) {
      RMQ[L][k] = std::min(RMQ[L][k-1], RMQ[L+pow2[k-1]][k-1]);
    }
  }
}

uint32_t LCA(uint32_t v, uint32_t u) {
  size_t l = ind[v];
  size_t r = ind[u];
  if (r < l) std::swap(l, r);
  r++;
  size_t k = log2[r - l];
  return std::min(RMQ[l][k], RMQ[r - pow2[k]][k]).second;
}

bool in_tree(uint32_t v, uint32_t p) {
  return in[p] <= in[v] && out[v] <= out[p];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);


  pow2[0] = 1;
  for (size_t i = 1; i < 31; ++i) {
    pow2[i] = 2 * pow2[i - 1];
  }
  log2[1] = 0;
  log2[2] = 1;
  for (size_t i = 3; i < 500000; ++i) {
    log2[i] = log2[i / 2] + 1;
  }

  size_t n;
  while (true) {
    std::cin >> n;
    if (n == 0) return 0;

    in.assign(n + 1, 0);
    out.assign(n + 1, 0);
    edges.assign(n + 1, std::vector<uint32_t>(0));
    ind.assign(n + 1, 0);
    arr.assign(0, {0, 0});
//    puts("initialized");
    for (size_t i = 0; i != n - 1; ++i) {
      uint32_t v, u;
      std::cin >> v >> u;
      edges[v].push_back(u);
      edges[u].push_back(v);
    }
    t = 0;
    dfs(-1, 1, 0);
//    puts("dfs completed");

    build_RMQ();
//    puts("RMQ built");

    uint32_t temp_root = 1;

    size_t m;
    std::cin >> m;
    std::string cmd;
//    puts("commands started");
    for (size_t i = 0; i != m; ++i) {
      std::cin >> cmd;
      if (cmd == "?") {
        uint32_t v, u;
        std::cin >> v >> u;
//        puts("read");
        uint32_t lca = LCA(v, u);
//        puts("here 1");
        uint32_t ans = lca;
        if (in_tree(temp_root, lca)) {
//          puts("here 2");
          uint32_t ans_v = LCA(temp_root, v);
          uint32_t ans_u = LCA(temp_root, u);
          if (ans_v != lca) {
            ans = ans_v;
          } else if (ans_u != lca) {
            ans = ans_u;
          }
//          puts("here 3");
        }
        std::cout << ans << '\n';
//        puts("done");
      }
      if (cmd == "!") {
        std::cin >> temp_root;
//        puts("read");
//        puts("done");
      }
    }
  }
}
/*

 5
 1 2
 3 2
 5 4
 4 3
 5
 ? 2 1
 ? 2 3
 ? 4 3
 ? 4 5
 9
 1 2
 1 3
 2 4
 2 5
 3 6
 3 7
 6 8
 6 9
 10
 ? 4 5
 ? 5 6
 ? 8 7
 ! 6
 ? 8 7
 ? 4 5
 ? 4 7
 ? 5 9
 ! 2
 ? 4 3
 9
 3 1
 3 7
 6 8
 2 4
 2 5
 2 1
 9 6
 6 3
 10
 ? 5 4
 ? 5 6
 ? 8 7
 ! 6
 ? 7 8
 ? 4 5
 ? 7 4
 ? 5 9
 ! 2
 ? 3 4
 0

*/
