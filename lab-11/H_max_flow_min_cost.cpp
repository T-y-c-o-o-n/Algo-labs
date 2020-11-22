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
    v_t from, to;
    int64_t cap, flow, cost;
    size_t copy_ind;

    edge(v_t from, v_t to, int64_t cap, int64_t cost)
            : from(from), to(to), cap(cap), flow(0), cost(cost), copy_ind(0) {}
};

int64_t const c_max = (int64_t) 2e9;

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

int64_t dfs_dinic(v_t v, v_t t, int64_t c_min, vector<vector<edge>> &edges,
                  vector<size_t> &first_useful_edge_ind, vector<int> &dist) {
    if (v == t) {
        return c_min;
    }
    for (; first_useful_edge_ind[v] < edges[v].size(); ++first_useful_edge_ind[v]) {
        edge &vu = edges[v][first_useful_edge_ind[v]];
        if (dist[v] + 1 == dist[vu.to] && vu.cap - vu.flow > 0) {
            int64_t d = dfs_dinic(vu.to, t, min(vu.cap - vu.flow, c_min),
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
            int64_t d = dfs_dinic(s, t, c_max, edges, first_useful_edge_ind, dist);
            if (d == 0) {
                break;
            }
            flow += d;
        }
    }

    return flow;
}

const int64_t INF = INT64_MAX;

void find_negative_cycle(size_t n, vector<vector<edge>> &edges, vector<pair<v_t, size_t>> &cycle) {
    vector<int64_t> dist(n, 0);
    vector<pair<v_t, size_t>> prev(n, {-1, 0});
    v_t end_of_cycle = -1;
    for (size_t i = 0; i < n; ++i) {
        for_v(v, n) {
            for_i(j, edges[v].size()) {
                edge &vu = edges[v][j];
                if (vu.cap - vu.flow > 0) {
                    v_t from = v, to = vu.to;
                    int64_t w = vu.cost;
                    int64_t new_dist = dist[from] + w;
                    if (new_dist < dist[to]) {
                        if (i + 1 == n) {
                            end_of_cycle = to;
                        }
                        dist[to] = new_dist;
                        prev[to] = {from, j};
                    }
                }
            }
        }
    }
    if (end_of_cycle != -1) {
        for (size_t i = 0; i < n; ++i) {
            end_of_cycle = prev[end_of_cycle].first;
        }
        v_t temp = end_of_cycle;
        while (temp != end_of_cycle || cycle.empty()) {
            cycle.push_back(prev[temp]);
            temp = prev[temp].first;
        }
        reverse(cycle.begin(), cycle.end());
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
        v_t from, to;
        int64_t cap, cost;
        cin >> from >> to >> cap >> cost;
        from--;
        to--;
        edges[from].emplace_back(from, to, cap, cost);
        edges[to].emplace_back(to, from, 0, -cost);
        edges[from].back().copy_ind = edges[to].size() - 1;
        edges[to].back().copy_ind = edges[from].size() - 1;
    }

    v_t s = 0, t = n - 1;
    dinic(s, t, n, edges);

    while (true) {
        vector<pair<v_t, size_t>> cycle;
        find_negative_cycle(n, edges, cycle);
        if (cycle.empty()) {
            break;
        }
        int64_t c_min = c_max;
        for (auto &v_ind : cycle) {
            c_min = min(edges[v_ind.first][v_ind.second].cap
                        - edges[v_ind.first][v_ind.second].flow, c_min);
        }
        for (auto &v_ind : cycle) {
            v_t v = v_ind.first;
            size_t ind = v_ind.second;
            edges[v][ind].flow += c_min;
            edges[edges[v][ind].to][edges[v][ind].copy_ind].flow -= c_min;
        }
    }


    int64_t final_cost = 0;
    for_v(v, n) {
        for (edge &vu : edges[v]) {
            if (vu.cap > 0) {
                final_cost += (vu.flow) * (vu.cost);
            }
        }
    }
    cout << final_cost << '\n';

    return 0;
}
/*

4 5
1 2 1 2
1 3 2 2
3 2 1 1
2 4 2 1
3 4 2 3

 4 4
1 2 10 -10
2 4 5 -10
1 3 7 -10
3 4 2 -10

 6 10
1 2 1 2
1 3 2 2
3 2 1 1
2 6 2 1
3 6 2 3
1 4 1 2
1 5 2 2
5 4 1 1
4 6 2 1
5 6 2 3

*/
