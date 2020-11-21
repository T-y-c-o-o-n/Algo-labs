#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::ios_base;
using std::queue;
using std::pair;
using std::reverse;

using v_t = int32_t;

size_t n;
vector<pair<v_t, v_t> > graph;
vector<vector<v_t> > edges, reversed_edges;
vector<v_t> order;
vector<int> comp;

vector<bool> used;
void dfs(v_t v) {
    used[v] = true;
    for (v_t u : edges[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    order.push_back(v);
}

void SCC(v_t u, int color) {
    comp[u] = color;
    for (v_t v : reversed_edges[u]) {
        if (comp[v] == -1) {
            SCC(v, color);
        }
    }
}

void find_comps() {
    used.resize(n + 1, false);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        if (!used[v]) {
            dfs(v);
        }
    }
    reverse(order.begin(), order.end());

    comp.resize(n + 1, -1);
    int color = 0;
    for (v_t v : order) {
        if (comp[v] == -1) {
            color++;
            SCC(v, color);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // input
    size_t l_size;
    cin >> l_size;
    n = 2 * l_size;
    edges.resize(n + 1);
    reversed_edges.resize(n + 1);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        size_t deg;
        cin >> deg;
        for (size_t i = 0; i < deg; ++i) {
            v_t u;
            cin >> u;
            edges[v].push_back(l_size + u);
            reversed_edges[l_size + u].push_back(v);
            graph.emplace_back(v, l_size + u);
        }
    }
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        v_t pair_u;
        cin >> pair_u;
        edges[l_size + pair_u].push_back(v);
        reversed_edges[v].push_back(l_size + pair_u);
//        for (auto &el : edges[v]) {
//            if (el == pair_u) {
//                edges[v].erase(& el);
//            }
//        }
    }

    // strong components
    find_comps();

    vector<vector<v_t> > ans(n + 1);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        for (v_t u : edges[v]) {
            if (comp[v] == comp[u]) {
                ans[v].push_back(u - l_size);
            }
        }
    }

    // output
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        cout << ans[v].size();
        for (v_t u : ans[v]) {
            cout << ' ' << u;
        }
        cout << '\n';
    }

    return 0;
}
