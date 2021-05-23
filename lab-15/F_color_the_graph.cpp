//
// Created by tycoon on 13.05.2021.
//
#include "iostream"
#include "vector"

using namespace std;

bool dfs(int v, int color, vector<int> &colors, vector<vector<int>> &adj_list, vector<bool> &in_I) {
    colors[v] = color;

    for (int u : adj_list[v]) {
        if (in_I[u]) {
            continue;
        }

        if (colors[u] == color) {
            return false;
        }
        if (colors[u] == -1) {
            if (!dfs(u, 1 - color, colors, adj_list, in_I)) {
                return false;
            }
        }
    }

    return true;
}

void gen_max_sets(int vertices, vector<bool> &in_A, vector<bool> &in_I,
                  vector<vector<int>> &adj_list, bool &satisfied, vector<int> &colors) {
    bool empty_A = true;
    int vertex = -1;
    int degree = numeric_limits<int>::max();
    for (int v = 0; v < vertices; ++v) {
        if (in_A[v]) {
            empty_A = false;

            int v_degree = 0;
            for (int u : adj_list[v]) {
                if (in_A[u]) {
                    v_degree++;
                }
            }
            if (v_degree < degree) {
                vertex = v;
                degree = v_degree;
            }
        }
    }

    if (empty_A) {
        for (int v = 0; v < vertices; ++v) {
            if (!in_I[v] && colors[v] == -1) {
                if (!dfs(v, 0, colors, adj_list, in_I)) {
                    satisfied = false;
                    colors.assign(vertices, -1);
                    return;
                }
            }
        }

        satisfied = true;
        for (int v = 0; v < vertices; ++v) {
            if (in_I[v]) {
                colors[v] = 2;
            }
        }
        return;
    }

    vector<int> to_try;
    to_try.push_back(vertex);
    for (int u : adj_list[vertex]) {
        if (in_A[u]) {
            to_try.push_back(u);
        }
    }

    for (int v : to_try) {
        vector<int> deleted_from_A;
        in_A[v] = false;
        deleted_from_A.push_back(v);
        for (int u : adj_list[v]) {
            if (in_A[u]) {
                in_A[u] = false;
                deleted_from_A.push_back(u);
            }
        }
        in_I[v] = true;

        gen_max_sets(vertices, in_A, in_I, adj_list, satisfied, colors);
        if (satisfied) {
            return;
        }

        for (int u : deleted_from_A) {
            in_A[u] = true;
        }
        in_I[v] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> origin_adj_list(n);
    vector<vector<int>> adj_list(m);
    int edges = 0;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v;
        --u;

        for (auto &edge : origin_adj_list[v]) {
            adj_list[i].push_back(edge.second);
            adj_list[edge.second].push_back(i);
            edges++;
        }
        for (auto &edge : origin_adj_list[u]) {
            adj_list[i].push_back(edge.second);
            adj_list[edge.second].push_back(i);
            edges++;
        }

        origin_adj_list[v].emplace_back(u, i);
        origin_adj_list[u].emplace_back(v, i);
    }

    for (int v = 0; v < n; ++v) {
        if ((int) origin_adj_list[v].size() > 3) {
            return cout << "NO\n", 0;
        }
    }

    if (edges == 0) {
        cout << "YES\n";
        for (int i = 0; i < m; ++i) {
            cout << "1 ";
        }
        cout << '\n';
        return 0;
    }

    vector<int> colors(m, -1);
    vector<bool> in_A(m, true), in_I(m, false);

    bool double_dole = true;
    for (int i = 0; i < m; ++i) {
        if (colors[i] == -1 && !dfs(i, 0, colors, adj_list, in_I)) {
            double_dole = false;
            colors.assign(m, -1);
            break;
        }
    }
    if (double_dole) {
        cout << "YES\n";
        for (int color : colors) {
            cout << (color + 1) << ' ';
        }
        cout << '\n';
        return 0;
    }

    bool satisfied = false;
    gen_max_sets(m, in_A, in_I, adj_list, satisfied, colors);

    if (satisfied) {
        cout << "YES\n";
        for (int color : colors) {
            cout << (color + 1) << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }

    return 0;
}