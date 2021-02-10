#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::pair;
using std::min;
using v_t = int32_t;

#define for_v(v, n) for (v_t v = 0; v < (v_t) n; ++v)
#define for_i(i, n) for (size_t i = 0; i < (size_t) n; ++i)

struct edge {
    v_t to;
    int32_t cap, flow;
    size_t copy_ind;

    edge(v_t to, int cap) : to(to), cap(cap), flow(0) {}
};

int32_t const c_max = (int32_t)2e9;

int32_t dfs_ford_falkerson(v_t v, v_t t, int c_min,
                           vector<vector<edge>> &edges, vector<bool> &used) {
    used[v] = true;
    if (v == t) {
        return c_min;
    }
    for (edge &vu : edges[v]) {
        if (vu.cap - vu.flow > 0 && !used[vu.to]) {
            int32_t d = dfs_ford_falkerson(vu.to, t, min(vu.cap - vu.flow, c_min), edges, used);
            if (d > 0) {
                vu.flow += d;
                edges[vu.to][vu.copy_ind].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int32_t ford_falkerson(v_t s, v_t t, size_t n, vector<vector<edge>> &edges) {
    vector<bool> used;
    int32_t flow = 0;
    int32_t d;
    do {
        used.assign(n, false);
        d = dfs_ford_falkerson(s, t, c_max, edges, used);
        flow += d;
    } while (d > 0);

    return flow;
}

void bfs_dinic(v_t s, vector<int> &dist, vector<vector<edge>> &edges) {
    dist[s] = 0;
    queue<v_t> Q;
    Q.push(s);
    while (!Q.empty()) {
        v_t v = Q.front();
        Q.pop();
        for (edge &vu : edges[v]) {
            if (dist[vu.to] == -1 && vu.cap - vu.flow > 0) {
                dist[vu.to] = dist[v] + 1;
                Q.push(vu.to);
            }
        }
    }
}

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

int64_t dinic(v_t s, v_t t, size_t n, vector<vector<edge>> &edges) {
    int64_t flow = 0;
    while (true) {
        vector<int> dist(n, -1);
        bfs_dinic(s, dist, edges);
        if (dist[t] == -1) {
            break;
        }
        vector<size_t> first_useful_edge_ind(n, 0);
        while (true) {
            int32_t d = dfs_dinic(s, t, c_max, edges, first_useful_edge_ind, dist);
            if (d == 0) {
                break;
            }
            flow += (int64_t) d;
        }
    }

    return flow;
}

void dfs(v_t v, vector<vector<edge>> &edges, vector<bool> &used) {
    used[v] = true;
    for (edge vu : edges[v]) {
        if (!used[vu.to] && vu.cap - vu.flow > 0) {
            dfs(vu.to, edges, used);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    vector<vector<edge>> edges(n);
    for_i(i, m) {
        v_t v, u;
        int c;
        cin >> v >> u >> c;
        v--;
        u--;
        edges[v].emplace_back(u, c);
        edges[u].emplace_back(v, c);
        edges[v].back().copy_ind = edges[u].size() - 1;
        edges[u].back().copy_ind = edges[v].size() - 1;
    }

    v_t s = 0, t = n - 1;
    dinic(s, t, n, edges);

    vector<bool> used(n, false);
    dfs(s, edges, used);
    vector<v_t> reachable;
    for_v(v, n) {
        if (used[v]) {
            reachable.push_back(v);
        }
    }
    cout << reachable.size() << '\n';
    for (v_t v : reachable) {
        cout << (v + 1) << ' ';
    }
    cout << '\n';

    return 0;
}
