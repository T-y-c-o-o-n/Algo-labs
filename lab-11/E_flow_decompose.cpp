#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <queue>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::reverse;
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
    int no;

    edge(v_t to, int cap, int no) : to(to), cap(cap), flow(0), copy_ind(0), no(no) {}
};

int32_t const c_max = (int32_t) 2e9;

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

int32_t dfs_find_path(v_t v, v_t t, int32_t c_min, vector<vector<edge>> &edges,
                      vector<size_t> first_useful_edge_ind, vector<int> &reversed_path) {
    if (v == t) {
        return c_min;
    }
    for (; first_useful_edge_ind[v] < edges[v].size(); ++first_useful_edge_ind[v]) {
        edge &vu = edges[v][first_useful_edge_ind[v]];
        if (vu.flow > 0 && vu.no != -1) {
            int32_t d = dfs_find_path(vu.to, t, min(vu.flow, c_min),
                                      edges, first_useful_edge_ind, reversed_path);
            if (d > 0) {
                reversed_path.push_back(vu.no);
                vu.flow -= d;
                edges[vu.to][vu.copy_ind].flow += d;
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

    size_t n, m;
    cin >> n >> m;
    vector<vector<edge>> edges(n);
    for_i(i, m) {
        v_t from, to;
        int c;
        cin >> from >> to >> c;
        from--;
        to--;
        edges[from].emplace_back(to, c, (int) i);
        edges[to].emplace_back(from, 0, -1);
        edges[from].back().copy_ind = edges[to].size() - 1;
        edges[to].back().copy_ind = edges[from].size() - 1;
    }

    v_t s = 0, t = n - 1;
    int64_t flow = dinic(s, t, n, edges);

    vector<pair<int32_t, vector<int>>> paths;
    vector<size_t> first_useful_edge_ind(n, 0);
    while (flow > 0) {
        vector<int> reversed_path;
        int32_t d = dfs_find_path(s, t, c_max, edges, first_useful_edge_ind, reversed_path);
        reverse(reversed_path.begin(), reversed_path.end());
        paths.emplace_back(d, reversed_path);
        flow -= d;
    }

    cout << paths.size() << '\n';
    for (auto &flow_path : paths) {
        cout << flow_path.first << ' ' << flow_path.second.size();
        for (int no : flow_path.second) {
            cout << ' ' << (no + 1);
        }
        cout << '\n';
    }
}
