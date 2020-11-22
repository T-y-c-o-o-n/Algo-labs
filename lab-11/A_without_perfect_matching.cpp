#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::ios_base;
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using v_t = int32_t;

#define for_v(v, n) for (v_t v = 0; v <= (v_t) n; ++v)
#define for_i(i, n) for (size_t i = 0; i < (size_t) n; ++i)

size_t n_left, m_right, k;
vector<vector<v_t>> edges;
vector<v_t> edge_r;
vector<bool> used;

bool dfs(v_t v) {
    used[v] = true;
    for (v_t u : edges_l[v]) {
        if (edge_r[u] == -1 ||
            (!used[edge_r[u]] && dfs(edge_r[u]))) {
            edge_r[u] = v;
            return true;
        }
    }

    return false;
}

size_t kuhn() {
    edge_r.resize(m_right + 1, -1);
    size_t ans = 0;
    for (v_t v = 1; v <= (v_t)n_left; ++v) {
        used.assign(n_left + 1, false);
        if (!used[v]) {
            if (dfs(v)) {
                ans++;
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n_left, n_right, m;
    while (cin >> n_left >> n_right >> m) {
        edges.assign(n_left, vector<v_t> (0));
        for_i(i, m) {
            v_t v, u;
            cin >> v >> u;
            edges[v - 1].push_back(u - 1);
        }


    }

    return 0;
}
