#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::priority_queue;
using std::set;
using std::pair;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v

struct edge {
    v_t to;
    int64_t weight;

    edge(v_t to, int64_t weight) : to(to), weight(weight) {}
};

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n;
vector<vector<edge>> E_weighted;

void dijkstra_adv(vector<int64_t> &d, v_t start) {
    d[to_sz(start)] = 0;
    priority_queue<pair<int64_t, v_t> > Q;
    Q.push({-0, start});
    while (!Q.empty()) {
        auto vu = Q.top();
        int64_t dist = vu.first;
        v_t from = vu.second;
        Q.pop();
        if (d[to_sz(from)] < dist) {
            continue;
        }
        for (edge &edge : E_weighted[to_sz(from)]) {
            v_t to = edge.to;
            int64_t weight = edge.weight;
            int64_t new_dist = d[to_sz(from)] + weight;
            if (new_dist < d[to_sz(to)]) {
                d[to_sz(to)] = new_dist;
                Q.push({-new_dist, to});
            }
        }
    }
}

int main() {
    size_t m;
    cin >> n >> m;
    E_weighted.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        v_t v, u;
        int64_t weight;
        cin >> v >> u >> weight;
        E_weighted[to_sz(v)].emplace_back(u, weight);
        E_weighted[to_sz(u)].emplace_back(v, weight);
    }
    vector<int64_t> d(n + 1, INF);
    v_t start = 1;
    dijkstra_adv(d, start);
    for (all_ind(i)) {
        cout << d[i] << ' ';
    }

    return 0;
}
