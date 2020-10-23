#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::pair;
using std::min;
using std::max;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n;
vector<vector<v_t>> E;
vector<vector<pair<v_t, int64_t>>> E_weighted;

void floyd(vector<vector<int64_t>> &d) {
    for (all(v)) {
        d[to_sz(v)][to_sz(v)] = 0;
    }
    for (all(from)) {
        for (auto &edge : E_weighted[to_sz(from)]) {
            d[to_sz(from)][to_sz(edge.first)] = edge.second;
        }
    }
    for (all(middle)) {
        for (all(from)) {
            for (all(to)) {
                d[to_sz(from)][to_sz(to)] = min(d[to_sz(from)][to_sz(to)],
                                                d[to_sz(from)][to_sz(middle)] +
                                                d[to_sz(middle)][to_sz(to)]);
            }
        }
    }
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
    vector<vector<int64_t>> d(n + 1, vector<int64_t>(n + 1, INF));
    floyd(d);
    for (all(from)) {
        for (all(to)) {
            cout << d[to_sz(from)][to_sz(to)] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
