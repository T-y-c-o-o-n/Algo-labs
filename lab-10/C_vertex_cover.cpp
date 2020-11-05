//
// Created by tycoon on 05.11.2020.
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> l_size >> r_size;
    edges_l.resize(l_size + 1);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        size_t edges_count;
        cin >> edges_count;
        for (size_t j = 0; j < edges_count; ++j) {
            v_t u;
            cin >> u;
            edges_l[v].push_back(u);
        }
    }
    pair_l.resize(l_size + 1, -1);
    pair_r.resize(r_size + 1, -1);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        v_t u;
        cin >> u;
        if (u != 0) {
            pair_l[v] = u;
            pair_r[u] = v;
        }
    }

    used.resize(l_size + 1, false);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        if (pair_l[v] == -1) {
            dfs(v);
        }
    }

    vector<v_t> left_cover, right_cover;
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        if (!used[v]) {
            left_cover.push_back(v);
        } else if (pair_l[v] != -1) {
            right_cover.push_back(pair_l[v]);
        }
    }

    sort(left_cover.begin(), left_cover.end());
    sort(right_cover.begin(), right_cover.end());

    cout << (left_cover.size() + right_cover.size()) << '\n' << left_cover.size();
    for (v_t v : left_cover) {
        cout << ' ' << v;
    }
    cout << '\n' << right_cover.size();
    for (v_t v : right_cover) {
        cout << ' ' << v;
    }
    cout << '\n';

    return 0;
}
