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

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n;
vector<vector<v_t>> E;
vector<vector<pair<v_t, int64_t>>> E_weighted;

void dijkstra(vector<int64_t> &d, v_t start) {
    d[to_sz(start)] = 0;
}

int main() {
    size_t m;
    cin >> n >> m;
    E_weighted.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        v_t from, to;
        int64_t weight;
        cin >> from >> to >> weight;
        E_weighted[to_sz(from)].emplace_back(to, weight);
    }
    vector<int64_t> d(n + 1, INF);
    v_t start = 1;
    dijkstra(d, start);
    for (all_ind(i)) {
        cout << d[i] << ' ';
    }

    return 0;
}
