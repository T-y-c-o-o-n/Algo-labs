//
// Created by tycoon on 30.05.2020.
//

#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::pair;

struct query {
  size_t l, r, t;
  uint64_t ans;
};

size_t n, m, k;
vector<uint32_t> arr;
vector< query > queries;
vector<uint32_t> cnt;

bool comp1(query a, query b) {
  if (a.l / k == b.l / k) return a.r < b.r;
  return a.l < b.l;
}

bool comp2(query a, query b) {
  return a.t < b.t;
}

void MO() {
  size_t l = 0, r = 0;
  uint64_t ans = 0;
  for (auto &q : queries) {
//    cout << l << ' ' << r << ' ' << ans << '\n';
    while (q.l < l) {
//      puts("L <- L");
      l--;
      uint32_t val = arr[l];
      cnt[val]++;
      ans += (uint64_t)val * (uint64_t)(cnt[val] * 2 - 1);
//      cout << ans << '\n';
    }
    while (q.r > r) {
//      puts("R -> R");
      r++;
      uint32_t val = arr[r];
      cnt[val]++;
      ans += (uint64_t)val * (uint64_t)(cnt[val] * 2 - 1);
//      cout << ans << '\n';
    }
    while (q.l > l) {
//      puts("L -> L");
      uint32_t val = arr[l];
      l++;
      ans -= (uint64_t)val * (uint64_t)(cnt[val] * 2 - 1);
      cnt[val]--;
//      cout << ans << '\n';
    }
    while (q.r < r) {
//      puts("R <- R");
      uint32_t val = arr[r];
      r--;
      ans -= (uint64_t)val * (uint64_t)(cnt[val] * 2 - 1);
      cnt[val]--;
//      cout << ans << '\n';
    }
//    std::cout << ans << '\n';
    q.ans = ans;
  }
}

int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(nullptr);
//  std::cout.tie(nullptr);

  cin >> n >> m;
  k = 1;
  while (k * k < m) k++;
  arr.resize(n + 1);
  queries.resize(m);
  uint32_t max = 0;
  for (size_t i = 1; i <= n; ++i) {
    cin >> arr[i];
    max = std::max(max, arr[i]);
  }
  cnt.resize(max + 1, 0);
  for (size_t i = 0; i < m; ++i) {
    cin >> queries[i].l >> queries[i].r;
    queries[i].t = i;
  }
  std::sort(queries.begin(), queries.end(), comp1);
  MO();
  std::sort(queries.begin(), queries.end(), comp2);
  for (auto &q : queries) {
    cout << q.ans << '\n';
  }
}
