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
    int no;

    edge(v_t to, int cap, int no) : to(to), cap(cap), flow(0), no(no) {}
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

void add_oriented_edges(v_t from, v_t to, int32_t cap, int no, vector<vector<edge>> &edges) {
    edges[from].emplace_back(to, cap, no);
    edges[to].emplace_back(from, 0, -1);
    edges[from].back().copy_ind = edges[to].size() - 1;
    edges[to].back().copy_ind = edges[from].size() - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;
    n += 2;
    v_t s = n - 2, t = n - 1;
    vector<pair<int32_t, int32_t>> ans(m);
    vector<vector<edge>> edges(n);
    int64_t sum_l = 0;
    for_i(i, m) {
        v_t from, to;
        int32_t l, r;
        cin >> from >> to >> l >> r;
        sum_l += (int64_t) l;
        from--;
        to--;
        ans[i].first = l;
        add_oriented_edges(from, to, r - l, i, edges);
        add_oriented_edges(s, to, l, -1, edges);
        add_oriented_edges(from, t, l, -1, edges);
    }

    int64_t flow = dinic(s, t, n, edges);
    if (flow >= sum_l) {
        cout << "YES\n";
        for_v(v, n - 2) {
            for (edge &vu : edges[v]) {
                if (vu.no != -1) {
                    ans[vu.no].second = ans[vu.no].first + vu.flow;
                }
            }
        }
        for_i(i, m) {
            cout << ans[i].second << '\n';
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}
