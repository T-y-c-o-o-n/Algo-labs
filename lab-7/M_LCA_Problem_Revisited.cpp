//
// Created by tycoon on 24.05.2020.
//
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>

std::vector< std::vector<uint64_t> > children;
std::vector<std::pair<uint64_t, uint64_t> > arr;  // <depth, vertex>
std::vector<size_t> ind;

void dfs(uint64_t v, uint64_t depth) {
  ind[(size_t)v] = arr.size();
  arr.emplace_back(depth, v);
  for (uint64_t u : children[(size_t)v]) {
    dfs(u, depth + 1);
    arr.emplace_back(depth, v);
  }
}

size_t n;
std::vector< std::vector< std::pair<uint64_t, uint64_t> > > RMQ;
size_t pow2[31];
std::vector<size_t>log2;

void build() {
  RMQ.resize(arr.size());
  for (auto &vect : RMQ) {
    vect.resize(log2[arr.size()] + 1);
  }
  for (size_t l = 0; l < arr.size(); ++l) {
    RMQ[l][0] = arr[l];
  }
  for (size_t k = 1; k <= log2[arr.size()] + 1; ++k) {
    for (size_t L = 0; L + pow2[k] <= arr.size(); ++L) {
      RMQ[L][k] = std::min(RMQ[L][k-1], RMQ[L+pow2[k-1]][k-1]);
//      if (RMQ[L][k-1].first < RMQ[L+pow2[k-1]][k-1].first) {
//        RMQ[L][k] = RMQ[L][k-1];
//      } else {
//        RMQ[L][k] = RMQ[L+pow2[k-1]][k-1];
//      }
    }
  }
}

std::pair<uint64_t, uint64_t> get_min(uint64_t v, uint64_t u) {
  size_t l = (size_t)std::min(u, v), r = (size_t)std::max(u, v) + 1;
  size_t k = log2[r - l];
  if (RMQ[l][k].first < RMQ[r - pow2[k]][k].first) {
    return RMQ[l][k];
  } else {
    return RMQ[r - pow2[k]][k];
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t m;
  std::cin >> n >> m;
  children.resize(n);
  ind.resize(n);
  for (size_t i = 1; i < n; ++i) {
    uint64_t p;
    std::cin >> p;
    children[(size_t)p].push_back((uint64_t)i);
  }
  dfs(0, 0);

  pow2[0] = 1;
  for (size_t i = 1; i < 31; ++i) {
    pow2[i] = 2 * pow2[i - 1];
  }
  log2.resize(arr.size() + 3);
  log2[1] = 0;
  log2[2] = 1;
  for (size_t i = 3; i < log2.size(); ++i) {
    log2[i] = log2[i / 2] + 1;
  }

  build();

  uint64_t ans = 0;
  std::vector<uint64_t> a(2 * m + 9);
  uint64_t x, y, z, v, u;
  std::cin >> a[1] >> a[2] >> x >> y >> z;
  for (size_t i = 3; i <= 2 * m + 1; ++i) {
    a[i] = (x * a[i - 2] + y * a[i - 1] + z) % (uint64_t)n;
  }
  uint64_t res = 0;
  for (size_t i = 1; i <= m; ++i) {
    v = (a[2 * i - 1] + res) % (uint64_t)n;
    u = a[2 * i];
//    std::cout << v << ' ' << u << '\n';
    // LCA(v, u) - ?
    res = get_min(ind[(size_t)v], ind[(size_t)u]).second;
    ans = ans + res;
  }
  std::cout << ans << '\n';
}
/*
3 2       n m
0 1       p1 p2
2 1       a1 a2
1 1 0     x y z
*/
