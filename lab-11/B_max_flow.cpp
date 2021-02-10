#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::min;
using v_t = int32_t;

#define for_v(v, n) for (v_t v = 0; v < (v_t) n; ++v)
#define for_i(i, n) for (size_t i = 0; i < (size_t) n; ++i)

struct edge {
    v_t from, to;
    int cap, flow;
    size_t copy_ind;

    edge(v_t from, v_t to, int cap) : from(from), to(to), cap(cap), flow(0) {}
};

int dfs_ford_falkerson(v_t v, v_t t, int c_min, vector<vector<edge>> &edges, vector<bool> &used) {
    used[v] = true;
    if (v == t) {
        return c_min;
    }
    for (edge &vu : edges[v]) {
        if (vu.cap - vu.flow > 0 && !used[vu.to]) {
            int d = dfs_ford_falkerson(vu.to, t, min(vu.cap - vu.flow, c_min), edges, used);
            if (d > 0) {
                vu.flow += d;
                edges[vu.to][vu.copy_ind].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int ford_falkerson(vector<vector<edge>> &edges, v_t s, v_t t) {
    vector<bool> used;
    int const c_max = (int)1e6;
    int ans = 0;
    int d;
    do {
        used.assign(edges.size(), false);
        d = dfs_ford_falkerson(s, t, c_max, edges, used);
        ans += d;
    } while (d > 0);

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<vector<edge>> edges(n);
    for_i(i, m) {
        v_t from, to;
        int c;
        cin >> from >> to >> c;
        from--;
        to--;
        edges[from].emplace_back(from, to, c);
        edges[to].emplace_back(to, from, 0);
        edges[from].back().copy_ind = edges[to].size() - 1;
        edges[to].back().copy_ind = edges[from].size() - 1;
    }

    v_t s = 1 - 1, t = n - 1;
    cout << ford_falkerson(edges, s, t);

    return 0;
}
