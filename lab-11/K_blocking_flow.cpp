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
    v_t to;
    int cap, flow;
    size_t copy_ind;
    int no;

    edge(v_t to, int cap, int no) : to(to), cap(cap), flow(0), copy_ind(0), no(no) {}
};

int32_t dfs_dinic(v_t v, v_t t, int32_t c_min, vector<vector<edge>> &edges,
                  vector<size_t> &first_useful_edge_ind, vector<int> &dist) {
    if (v == t) {
        return c_min;
    }
    for (; first_useful_edge_ind[v] < edges[v].size(); ++first_useful_edge_ind[v]) {
        edge &vu = edges[v][first_useful_edge_ind[v]];
        if (dist[v] + 1 == dist[vu.to] && vu.cap - vu.flow > 0) {
            int32_t d = dfs_dinic(vu.to, t, min(vu.cap - vu.flow, c_min),
                                  edges, first_useful_edge_ind, dist);
            if (d > 0) {
                vu.flow += d;
                edges[vu.to][vu.copy_ind].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m, L;
    cin >> n >> m >> L;

    vector<int> dist(n);
    vector<vector<edge>> edges(n);
    vector<size_t> first_useful_edge_ind(n, 0);
    v_t s = 1, t = (v_t) n;

    for_v(v, n) {
        cin >> dist[v];
        if (dist[v] == 1) {
            s = v;
        }
        if (dist[v] == (v_t) L) {
            t = v;
        }
    }
    for_i(i, m) {
        v_t from, to;
        int32_t c;
        cin >> from >> to >> c;
        from--;
        to--;
        edges[from].emplace_back(to, c, (int) i);
        edges[to].emplace_back(from, 0, -1);
        edges[from].back().copy_ind = edges[to].size() - 1;
        edges[to].back().copy_ind = edges[from].size() - 1;
    }

    while (true) {
        int32_t d = dfs_dinic(s, t, (int32_t) 1e7, edges, first_useful_edge_ind, dist);
        if (d == 0) {
            break;
        }
    }

    vector<int32_t> edge_flow(m, 0);
    for_v(v, n) {
        for (edge &vu : edges[v]) {
            if (vu.no >= 0) {
                edge_flow[vu.no] = vu.flow;
            }
        }
    }
    for_i(i, m) {
        cout << edge_flow[i] << '\n';
    }

    return 0;
}
