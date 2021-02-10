#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::reverse;
using std::pair;
using std::min;
using v_t = int32_t;

#define for_v(v, n) for (v_t (v) = 0; (v) < (v_t) (n); ++(v))
#define for_i(i, n) for (size_t (i) = 0; (i) < (size_t) (n); ++(i))

struct edge {
    v_t from, to;
    int64_t cost, cap, flow;
    size_t copy_ind;
    bool used;

    edge(const edge &other) = default;

    edge(v_t from, v_t to, int64_t cost, int64_t cap)
            : from(from), to(to), cost(cost), cap(cap), flow(0), copy_ind(0), used(false) {}

    edge(v_t from, v_t to, int64_t weight)
            : edge(from, to, weight, 0) {}

    edge() : edge(-1, -1, 0) {}
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

void potential_algorithm(size_t left_size, size_t right_size, size_t needed_deg,
                         vector<vector<edge>> &edges_original, vector<vector<edge>> &subgraph) {
    size_t n = left_size + right_size;
    v_t s = (v_t) n, t = (v_t) n + 1;
    n += 2;
    vector<vector<edge>> edges(n);
    for_v(v, s) {
        for (edge &vu : edges_original[v]) {
            insert_edges_into_network(v, vu.to, vu.cost, 1, edges);
        }
    }
    for_v(v, left_size) {
        insert_edges_into_network(s, v, 0, needed_deg, edges);
    }
    for_v(v, right_size) {
        insert_edges_into_network(v + left_size, t, 0, needed_deg, edges);
    }
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

    // filling subgraph
    subgraph.assign(left_size + right_size, vector<edge>(0));
    for_v(v, left_size + right_size) {
        for (edge &vu : edges[v]) {
            if (vu.flow > 0 && vu.to < (v_t) (left_size + right_size)) {
                subgraph[v].emplace_back(vu.from, vu.to, vu.cost);
            }
        }
    }
}

bool dfs_kuhn(v_t v, int no, vector<vector<edge>> &edges,
              vector<pair<v_t, int64_t>> &match_left, vector<v_t> &match_right, vector<int> &used) {
    used[v] = no;
    for (edge &vu : edges[v]) {
        if (vu.used) {
            continue;
        }
        if (match_right[vu.to] == -1 || (used[match_right[vu.to]] != no
                                         && dfs_kuhn(match_right[vu.to], no, edges,
                                                     match_left, match_right, used))) {
            match_right[vu.to] = v;
            match_left[v].first = vu.to;
            match_left[v].second = vu.cost;
            return true;
        }
    }

    return false;
}

void kuhn(size_t left_size, size_t right_size,
          vector<vector<edge>> &edges, vector<edge> &matching) {
    vector<int> used(left_size, -1);  // number of last dfs
    vector<pair<v_t, int64_t>> match_left(left_size, {-1, 0});
    vector<v_t> match_right(left_size + right_size, -1);
    for_v(v, left_size) {
        if (used[v] != v) {
            dfs_kuhn(v, v, edges, match_left, match_right, used);
        }
    }
    for_v(v, left_size) {
        if (match_left[v].first != -1) {
            matching.emplace_back(v, match_left[v].first, match_left[v].second);
        }
    }
}

void find_k_matchings(size_t left_size, size_t right_size, size_t k, vector<vector<edge>> &edges,
                      vector<vector<edge>> &matchings) {
    for_i(i, k) {
        vector<edge> matching;
        kuhn(left_size, right_size, edges, matching);
        matchings.push_back(matching);
        for (edge &edge_ : matching) {
            for (edge &vu : edges[edge_.from]) {
                if (vu.to == edge_.to) {
                    vu.used = true;
                    break;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, k;
    cin >> n >> k;
    vector<vector<edge>> edges(2 * n);
    for_v(from, n) {
        for_v(to, n) {
            int64_t weight;
            cin >> weight;
            edges[from].emplace_back(from, to + (v_t) n, weight);
        }
    }

    // найдёт минимальный k-регулярный подграф
    vector<vector<edge>> subgraph(2 * n);
    potential_algorithm(n, n, k, edges, subgraph);
/*
    3 1
    1 90 23
    23 0 23
    20 20 20
*/

    // найдёт k паросочетаний
    vector<vector<edge>> matchings;
    find_k_matchings(n, n, k, subgraph, matchings);

    int64_t ans = 0;
    for (auto &matching : matchings) {
        for (edge &vu : matching) {
            ans += vu.cost;
        }
    }
    cout << ans << '\n';
    for (auto &matching  : matchings) {
        vector<v_t> match(n);
        for (edge &vu : matching) {
            match[vu.from] = vu.to;
        }
        for (v_t u : match) {
            cout << (u - n + 1) << ' ';
        }
        cout << '\n';
    }


    return 0;
}
