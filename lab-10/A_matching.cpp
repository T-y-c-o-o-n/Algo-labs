#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::ios_base;

using v_t = int32_t;

size_t n, m, k;
vector<vector<v_t>> edges_l;
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
    edge_r.resize(m + 1, -1);
    size_t ans = 0;
    for (v_t v = 1; v <= (v_t)n; ++v) {
        used.assign(n + 1, false);
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

    cin >> n >> m >> k;
    edges_l.resize(n + 1);
    for (size_t i = 0; i < k; ++i) {
        v_t l, r;
        cin >> l >> r;
        edges_l[l].push_back(r);
    }

    cout << kuhn() << '\n';

    return 0;
}
