//
// Created by tycoon on 11.11.2020.
//
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;
using std::string;
using std::pair;

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

void find_vertex_cover(vector<v_t> &left_cover, vector<v_t> &right_cover) {
    // Searching for max Matching
    kuhn();

    // Searching for min Cover
    used.assign(l_size + 1, false);
    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        if (pair_l[v] == -1) {
            dfs(v);
        }
    }

    for (v_t v = 1; v <= (v_t) l_size; ++v) {
        if (!used[v]) {
            left_cover.push_back(v);
        } else if (pair_l[v] != -1) {
            right_cover.push_back(pair_l[v]);
        }
    }
}

v_t cell_to_diag_1(size_t i, size_t j) {
    return (v_t) (i + j - 1);
}

v_t cell_to_diag_2(size_t i, size_t j, size_t m) {
    return (v_t) (i - j + m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // input
    size_t n, m;
    cin >> n >> m;
    l_size = r_size = n + m - 1;
    vector<string> input(n + 1, "");
    for (size_t i = 1; i <= n; ++i) {
        cin >> input[i];
    }

    vector<vector<pair<size_t, size_t>>> diag_1_to_cell(2), diag_2_to_cell(2);
    vector<vector<v_t>> left_cover(2, vector<v_t>(0)), right_cover(2, vector<v_t>(0));
    for (size_t k = 0; k < 2; ++k) {
        edges_l.assign(l_size + 1, vector<v_t>(0));
        diag_1_to_cell[k].assign(l_size + 1, {0, 0});
        diag_2_to_cell[k].assign(r_size + 1, {0, 0});
        for (size_t i = 1; i <= n; ++i) {
            string str = input[i];
            for (size_t j = 1; j <= str.length(); ++j) {
                if ((((i + j) % 2 == 0 && str[j - 1] == 'B')
                    || ((i + j) % 2 == 1 && str[j - 1] == 'W')) && k == 0) {
                        v_t v = cell_to_diag_1(i, j);
                        diag_1_to_cell[k][v] = {i, j};
                        v_t u = cell_to_diag_2(i, j, m);
                        diag_2_to_cell[k][u] = {i, j};
                        edges_l[v].push_back(u);
                } else if ((((i + j) % 2 == 0 && str[j - 1] == 'W')
                     || ((i + j) % 2 == 1 && str[j - 1] == 'B')) && k == 1) {
                    v_t v = cell_to_diag_1(i, j);
                    diag_1_to_cell[k][v] = {i, j};
                    v_t u = cell_to_diag_2(i, j, m);
                    diag_2_to_cell[k][u] = {i, j};
                    edges_l[v].push_back(u);
                }
            }
        }
        find_vertex_cover(left_cover[k], right_cover[k]);
    }

    size_t ans_ind = (left_cover[0].size() + right_cover[0].size())
                     > (left_cover[1].size() + right_cover[1].size()) ? 1 : 0;

    cout << (left_cover[ans_ind].size() + right_cover[ans_ind].size());
    for (v_t v : left_cover[ans_ind]) {
        const pair<size_t, size_t> &cell = diag_1_to_cell[ans_ind][(size_t) v];
        cout << "\n1 " << cell.first << ' ' << cell.second;
        if ((ans_ind == 0 && (cell.first + cell.second) % 2 == 0) ||
            (ans_ind == 1 && (cell.first + cell.second) % 2 == 1)) {
            cout << " W";
        } else {
            cout << " B";
        }
    }
    for (v_t v : right_cover[ans_ind]) {
        const pair<size_t, size_t> &cell = diag_2_to_cell[ans_ind][(size_t) v];
        cout << "\n2 " << cell.first << ' ' << cell.second;
        if ((ans_ind == 0 && (cell.first + cell.second) % 2 == 0) ||
            (ans_ind == 1 && (cell.first + cell.second) % 2 == 1)) {
            cout << " W";
        } else {
            cout << " B";
        }
    }

    return 0;
}
