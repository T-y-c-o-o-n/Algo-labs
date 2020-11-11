//
// Created by tycoon on 11.11.2020.
//
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;
using std::sort;

using v_t = int32_t;

size_t l_size, r_size;
vector<vector<v_t>> edges_l;
vector<v_t> pair_l, pair_r;
vector<bool> used;

void dfs(v_t v) {
    used[v] = true;
    for (v_t u : edges_l[v]) {
        if (pair_r[u] != -1 && !used[pair_r[u]]) {
            dfs(pair_r[u]);
        }
    }
}

bool dfs_kuhn(v_t v) {
    used[v] = true;
    for (v_t u : edges_l[v]) {
        if (pair_r[u] == -1 ||
            (!used[pair_r[u]] && dfs_kuhn(pair_r[u]))) {
            pair_r[u] = v;
            pair_l[v] = u;
            return true;
        }
    }

    return false;
}

void kuhn() {
    pair_l.assign(l_size + 1, -1);
    pair_r.assign(r_size + 1, -1);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        used.assign(l_size + 1, false);
        if (!used[v]) {
            dfs_kuhn(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t k;
    cin >> k;
    for (size_t i = 0; i < k; ++i) {
        cin >> l_size >> r_size;
        vector<vector<bool>> graph_before_inverting(l_size + 1, vector<bool>(r_size + 1));
        for (v_t v = 1; v <= (v_t) l_size; ++v) {
            v_t u = 0;
            do {
                cin >> u;
                if (u != 0) {
                    graph_before_inverting[v][u] = true;
                }
            } while (u != 0);
        }

        // Inverting graph
        edges_l.assign(l_size + 1, vector<v_t>(0));
        for (v_t v = 1; v <= (v_t) l_size; ++v) {
            for (v_t u = 1; u <= (v_t) r_size; ++u) {
                if (!graph_before_inverting[v][u]) {
                    edges_l[v].push_back(u);
                }
            }
        }

        // Searching for max Matching
        kuhn();

        // Searching for min Cover
        used.assign(l_size + 1, false);
        for (v_t v = 1; v <= (v_t) l_size; ++v) {
            if (pair_l[v] == -1) {
                dfs(v);
            }
        }

        vector<bool> left_covered(l_size + 1, false), right_covered(r_size + 1, false);
        for (v_t v = 1; v <= (v_t) l_size; ++v) {
            if (!used[v]) {
                left_covered[v] = true;
            } else if (pair_l[v] != -1) {
                right_covered[pair_l[v]] = true;
            }
        }

        // Searching for max Independent set
        vector<v_t> left_independent, right_independent;
        for (v_t v = 1; v <= (v_t) l_size; ++v) {
            if (!left_covered[v]) {
                left_independent.push_back(v);
            }
        }
        for (v_t v = 1; v <= (v_t) r_size; ++v) {
            if (!right_covered[v]) {
                right_independent.push_back(v);
            }
        }

        cout << (left_independent.size() + right_independent.size()) << '\n'
             << left_independent.size() << ' ' << right_independent.size() << '\n';
        for (v_t v : left_independent) {
            cout << v << ' ';
        }
        cout << '\n';
        for (v_t v : right_independent) {
            cout << v << ' ';
        }
        cout << "\n\n";
    }

    return 0;
}
