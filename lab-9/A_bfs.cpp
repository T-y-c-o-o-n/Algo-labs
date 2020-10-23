#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n;
vector<vector<v_t>> E;

void bfs(vector<int64_t> &d, v_t start) {
    d[to_sz(start)] = 0;
    queue<v_t> Q;
    Q.push(start);
    while (!Q.empty()) {
        v_t v = Q.front();
        Q.pop();
        for (v_t u : E[to_sz(v)]) {
            if (d[to_sz(u)] == INF) {
                d[to_sz(u)] = d[to_sz(v)] + 1;
                Q.push(u);
            }
        }
    }
}

int main() {
    size_t m;
    cin >> n >> m;
    E.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        v_t v, u;
        cin >> v >> u;
        E[to_sz(v)].push_back(u);
        E[to_sz(u)].push_back(v);
    }
    vector<int64_t> d(n + 1, INF);
    v_t start = 1;
    bfs(d, start);
    for (all_ind(i)) {
        cout << d[i] << ' ';
    }

    return 0;
}
