//
// Created by tycoon on 22.11.2020.
//
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using v_t = int32_t;

#define for_v(v, n) for (v_t v = 0; v < (v_t) n; ++v)
#define for_i(i, n) for (size_t i = 0; i < (size_t) n; ++i)

struct edge {
    v_t to;
    int32_t weight;

    edge(v_t to, int32_t weight) : to(to), weight(weight) {}
};

bool dfs_kuhn(v_t v, int32_t min_weight, vector<vector<edge>> &edges,
              vector<v_t> &edges_r, vector<bool> &used) {
    used[v] = true;
    for (edge &vu : edges[v]) {
        if (vu.weight >= min_weight
            && (edges_r[vu.to] == -1
                || (!used[edges_r[vu.to]] &&
                    dfs_kuhn(edges_r[vu.to], min_weight, edges, edges_r, used)))) {
            edges_r[vu.to] = v;
            return true;
        }
    }

    return false;
}

size_t kuhn(size_t n, int32_t min_weight, vector<vector<edge>> &edges) {
    vector<v_t> edges_r(n, -1);
    size_t ans = 0;
    for_v(v, n) {
        vector<bool> used(n, false);
        if (dfs_kuhn(v, min_weight, edges, edges_r, used)) {
            ans++;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;
    vector<vector<edge>> edges(n);
    for_v(v, n) {
        for_v(u, n) {
            int32_t weight;
            cin >> weight;
            edges[v].emplace_back(u, weight);
        }
    }

    int32_t L = -1, R = (int32_t)1e7;
    while (L + 1 < R) {
        int32_t M = L + (R - L) / 2;
        size_t matching_size = kuhn(n, M, edges);
        if (matching_size < n) {
            R = M;
        } else {
            L = M;
        }
    }
    cout << L << '\n';

    return 0;
}

