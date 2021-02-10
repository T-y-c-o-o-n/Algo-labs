#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::reverse;
using std::queue;
using std::set;
using std::map;
using std::pair;
using std::min;
using v_t = int32_t;

#define for_v(v, n) for (v_t v = 0; v < (v_t) (n); ++v)
#define for_i(i, n) for (size_t i = 0; i < (size_t) (n); ++i)

struct edge {
    v_t from, to;
    int64_t cap, flow, cost;
    size_t copy_ind;
    int64_t work_ind;

    edge(const edge &other) = default;

    edge(v_t from, v_t to, int64_t cap, int64_t cost, int64_t work_ind)
            : from(from), to(to), cap(cap), flow(0), cost(cost), copy_ind(0), work_ind(work_ind) {}

    edge(v_t from, v_t to, int64_t cap, int64_t cost)
            : edge(from, to, cap, cost, -1) {}
};

const int64_t INF = std::numeric_limits<int64_t>::max();

void ford_bellman(size_t n, v_t s, vector<vector<edge>> &edges, vector<int64_t> &dist) {
    dist.assign(n, INF);
    dist[s] = 0;

    for (size_t i = 0; i < n; ++i) {
        for_v(v, n) {
            if (dist[v] == INF) {
                continue;
            }
            for_i(j, edges[v].size()) {
                edge &vu = edges[v][j];
                if (vu.cap - vu.flow > 0) {
                    v_t from = v, to = vu.to;
                    int64_t w = vu.cost;
                    int64_t new_dist = dist[from] + w;
                    if (new_dist < dist[to]) {
                        dist[to] = new_dist;
                    }
                }
            }
        }
    }
}

void dijkstra(size_t n, v_t s, vector<vector<edge>> &edges,
              vector<int64_t> &phi, vector<int64_t> &dist) {
    dist.assign(n, INF);
    dist[s] = 0;

    vector<bool> used(n, false);
    while (true) {
        v_t selected = n + 5;
        for_v(v, n) {
            if (!used[v] && (selected == (v_t) (n + 5) || dist[v] < dist[selected])) {
                selected = v;
            }
        }
        if (selected == (v_t) (n + 5) || dist[selected] == INF) {
            break;
        }
        used[selected] = true;
        for (edge &vu : edges[selected]) {
            if (vu.cap - vu.flow > 0) {
                dist[vu.to] = min(dist[vu.to],
                                  dist[vu.from] + (vu.cost + phi[vu.from] - phi[vu.to]));
            }
        }
    }
}

void insert_edges_into_network(v_t from, v_t to, int64_t cost, int64_t cap,
                               vector<vector<edge>> &network) {
    network[from].emplace_back(from, to, cost, cap);
    network[to].emplace_back(to, from, -cost, 0);
    network[from].back().copy_ind = network[to].size() - 1;
    network[to].back().copy_ind = network[from].size() - 1;
}

int64_t dfs_find_zero_path_and_push_flow(v_t v, v_t t, int64_t min_cap,
                                         vector<vector<edge>> &edges,
                                         vector<int64_t> &phi, vector<bool> &used) {
    used[v] = true;
    if (v == t) {
        return min_cap;
    }
    for (edge &vu : edges[v]) {
        if ((vu.cost + phi[vu.from] - phi[vu.to]) == 0 && (vu.cap - vu.flow) > 0 && !used[vu.to]) {
            int64_t flow = dfs_find_zero_path_and_push_flow(
                    vu.to, t, min((vu.cap - vu.flow), min_cap), edges, phi, used);
            if (flow > 0) {
                vu.flow += flow;
                edges[vu.to][vu.copy_ind].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

void max_flow_min_cost_potential_algorithm(size_t n, v_t s, v_t t, vector<vector<edge>> &edges) {
    vector<int64_t> phi(n);
    ford_bellman(n, s, edges, phi);
    while (true) {
        vector<bool> used(n, false);
        int64_t flow = dfs_find_zero_path_and_push_flow(s, t, INF, edges, phi, used);
        if (flow == 0) {
            break;
        }
        vector<int64_t> d(n);
        dijkstra(n, s, edges, phi, d);
        for_v(v, n) {
            phi[v] = d[v] + phi[v] - phi[s];  // equals  d[v] + phi[v]
        }
    }
}

void add_edges(v_t from, v_t to, int64_t cap, int64_t cost,
               int64_t work_ind, vector<vector<edge>> &edges) {
    edges[from].emplace_back(from, to, cap, cost, work_ind);
    edges[to].emplace_back(to, from, 0, -cost, -1);
    edges[from].back().copy_ind = edges[to].size() - 1;
    edges[to].back().copy_ind = edges[from].size() - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, k;
    cin >> n >> k;
    vector<int64_t> s(n), t(n), c(n);
    set<int64_t> unique_times;
    for_i(i, n) {
        cin >> s[i] >> t[i] >> c[i];
        unique_times.insert(s[i]);
        unique_times.insert(s[i] + t[i]);
    }

    size_t vertex_cnt = unique_times.size() + 2;
    v_t start = (v_t) (vertex_cnt - 2), finish = (v_t) (vertex_cnt - 1);
    map<int64_t, v_t> time_to_vertex;
    v_t temp = 0;
    for (int64_t time : unique_times) {
          time_to_vertex[time] = temp++;
    }
    vector<vector<edge>> edges(vertex_cnt);
    for_i(i, n) {
        add_edges(time_to_vertex[s[i]], time_to_vertex[s[i] + t[i]], 1, -c[i], (int64_t) i, edges);
    }
    for_v(v, (start - 1)) {
        add_edges(v, v + 1, k, 0, -1, edges);
    }
    add_edges(start,  0, k, 0, -1, edges);
    add_edges(start - 1, finish, k, 0, -1, edges);

    max_flow_min_cost_potential_algorithm(vertex_cnt, start, finish, edges);

    vector<bool> ans(n, false);
    for_v(v, vertex_cnt) {
        for (edge &vu : edges[v]) {
            if (vu.work_ind != -1) {
                ans[(size_t) vu.work_ind] = vu.flow > 0;
            }
        }
    }

    for (bool i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
