#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::min;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v
const int64_t INF = static_cast<int64_t>(1e17);


int main() {
    size_t n;
    vector<vector<int64_t>> graph;
    v_t start, finish;
    cin >> n >> start >> finish;
    graph.resize(n + 1, vector<int64_t> (n + 1));

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            cin >> graph[i][j];
        }
    }
    vector<int64_t> d(n + 1, INF);
    d[start] = 0;

    vector<bool> used(n + 1, false);
    while (true) {
        v_t selected = 0;
        for (all(v)) {
            if (!used[to_sz(v)] && (selected == 0 || d[to_sz(v)] < d[to_sz(selected)])) {
                selected = v;
            }
        }
        if (selected == 0 || d[to_sz(selected)] == INF) {
            break;
        }
        used[to_sz(selected)] = true;
        for (all_ind(j)) {
            if (graph[to_sz(selected)][j] > 0) {
                d[j] = min(d[j], d[to_sz(selected)] + graph[to_sz(selected)][j]);
            }
        }
    }

    if (d[to_sz(finish)] != INF) {
        cout << d[to_sz(finish)] << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}
