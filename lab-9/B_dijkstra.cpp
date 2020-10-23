#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n;
vector<vector<v_t>> E;
vector<vector<pair<v_t, int64_t>>> E_weighted;

void dijkstra(vector<int64_t> &d, v_t start) {
    d[to_sz(start)] = 0;
    priority_queue<pair<int64_t, v_t>> Q;
    Q.push({-0, start});
    while (!Q.empty()) {
        int64_t dist = -Q.top().first;
        v_t from = Q.top().second;
        Q.pop();
        if (dist > d[to_sz(from)]) {
            continue;
        }
        for (auto &edge : E_weighted[to_sz(from)]) {
            v_t to = edge.first;
            int64_t weight = edge.second;
            if (d[to_sz(from)] + weight < d[to_sz(to)]) {
                d[to_sz(to)] = d[to_sz(from)] + weight;
                Q.push({-d[to_sz(to)], to});
            }
        }
    }
}

int main() {
    v_t start, finish;
    cin >> n >> start >> finish;
    E_weighted.resize(n + 1);
    for (all_ind(i)) {
        for (all(to)) {
            int64_t weight;
            cin >> weight;
            if (weight != -1) {
                E_weighted[i].emplace_back(to, weight);
            }
        }
    }
    vector<int64_t> d(n + 1, INF);
    dijkstra(d, start);
    if (d[to_sz(finish)] != INF) {
        cout << d[to_sz(finish)] << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}
