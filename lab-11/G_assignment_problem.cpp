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
    int64_t cost, cap, flow;
    size_t copy_ind;

    edge(v_t from, v_t to, int64_t cost, int64_t cap)
            : from(from), to(to), cost(cost), cap(cap), flow(0), copy_ind(0) {}

    edge(v_t from, v_t to, int64_t weight)
            : edge(from, to, weight, 0) {}
};

const int64_t INF = std::numeric_limits<int64_t>::max();
/*

void hungarian_algorithm(size_t n, vector<vector<edge>> &edges, vector<edge> &res) {
    // первый для вершин левой доли, второй для правой
    vector<vector<bool>> used(2, vector(n, false));
    vector<vector<v_t>> pair(2, vector(n, -1));  // пара из паросочетания
    // минимальное входящее ребро из L+ в правую вершину
    vector<edge> min_edge(n, {-1, -1, INF});

    vector<int64_t> row_delta(n, 0);  // сколько прибавили к строке
    vector<int64_t> col_delta(n, 0);  // сколько прибавили к столбцу
    vector<vector<v_t>> parent(2, vector(n, -1));  // предок по чередующимся цепям
    size_t matching_size = 0;
    while (matching_size < n) {
        edge temp_min_edge(-1, -1, INF);
        for_v(v, n) {
            if (min_edge[v].cost < temp_min_edge.cost) {
                temp_min_edge = min_edge[v];
            }
        }
        for_v(v, n) {
            if (used[0][v]) {
                row_delta[v] -= temp_min_edge.cost;
            }
            if (used[1][v]) {
                col_delta[v] += temp_min_edge.cost;
            }
        }
        used[1][temp_min_edge.to] = true;
        if (pair[1][temp_min_edge.to] == -1) {
            v_t left = temp_min_edge.from, right = temp_min_edge.to;
            while (true) {
                pair[0][left] = right;
                pair[1][right] = left;
                parent[1][right] = left;
                right = parent[0][left];
                if (right == -1) {
                    break;
                }
                left = parent[1][right];
            }

            matching_size++;

            for_v(v, n) {
                if (pair[0][v] == -1) {
                    used[0][v] = true;
                } else {
                    used[0][v] = false;
                }
            }
            used[1].assign(n, false);
            parent.assign(2, vector(2, -1));
        } else {
            v_t v = pair[1][temp_min_edge.to];
            used[0][v] = true;
            for (edge &vu : edges[v]) {
                if (vu.cost < min_edge[vu.to].cost) {
                    min_edge[vu.to] = vu;
                }
            }
        }
    }
    res.emplace_back(1, 2, 3);
}
*/

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

void potential_algorithm(size_t left_size, size_t right_size,
                         vector<vector<edge>> &edges_original,
                         vector<edge> &res_edges) {
    size_t n = left_size + right_size;
    v_t s = n, t = n + 1;
    n += 2;
    vector<vector<edge>> edges(n);
    for_v(v, s) {
        for (edge &vu : edges_original[v]) {
            insert_edges_into_network(v, vu.to, vu.cost, 1, edges);
        }
    }
    for_v(v, left_size) {
        insert_edges_into_network(s, v, 0, 1, edges);
    }
    for_v(v, right_size) {
        insert_edges_into_network(v + left_size, t, 0, 1, edges);
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
    for_v(v, left_size) {
        for (edge &vu : edges[v]) {
            if (vu.flow > 0) {
                int64_t weight = 0;
                for (edge &vu_original : edges_original[v]) {
                    if (vu_original.to == vu.to) {
                        weight = vu_original.cost;
                        break;
                    }
                }
                res_edges.emplace_back(v, vu.to, weight);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;
    vector<vector<edge>> edges(2 * n);
    for_v(from, n) {
        for_v(to, n) {
            int64_t weight;
            cin >> weight;
            edges[from].emplace_back(from, to + (v_t) n, weight);
        }
    }
    vector<edge> res_edges;

//    hungarian_algorithm(n, edges, res_edges);
    potential_algorithm(n, n, edges, res_edges);

    int64_t ans = 0;
    for (edge &vu : res_edges) {
        ans += vu.cost;
    }
    cout << ans << '\n';
    for (edge &vu : res_edges) {
        cout << (vu.from + 1) << ' ' << (vu.to - n + 1) << '\n';
    }


    return 0;
}
