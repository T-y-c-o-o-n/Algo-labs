//
// Created by tycoon on 13.05.2021.
//
#include <algorithm>
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


void dfs(int v, vector<vector<int>> &adj_list,
         vector<bool> &used, vector<int> &order) {
    used[v] = true;
    for (int u : adj_list[v]) {
        if (!used[u]) {
            dfs(u, adj_list, used, order);
        }
    }
    order.push_back(v);
}

void SCC(int v, int color,
         vector<vector<int>> &rev_adj_list,
         vector<int> &components) {
    components[v] = color;
    for (int u : rev_adj_list[v]) {
        if (components[u] == -1) {
            SCC(u, color, rev_adj_list, components);
        }
    }
}

// Pre: adj_list.size() == vertices
vector<int> compress(int vertices, vector<vector<int>> &adj_list) {
    vector<bool> used(vertices, false);
    vector<int> order;
    for (int v = 0; v < vertices; ++v) {
        if (!used[v]) {
            dfs(v, adj_list, used, order);
        }
    }
    reverse(order.begin(), order.end());

    vector<vector<int>> rev_adj_list(vertices);
    for (int v = 0; v < vertices; ++v) {
        for (int u : adj_list[v]) {
            rev_adj_list[u].push_back(v);
        }
    }

    vector<int> components(vertices, -1);
    int color = 0;
    for (int v : order) {
        if (components[v] == -1) {
            SCC(v, color++, rev_adj_list, components);
        }
    }
    return components;
}

int not_x(int x, int vars) {
    return x < vars ? x + vars : x - vars;
}

// not x = (x + vars)
vector<bool> solve_2_sat(int vars, vector<pair<int, int>> &terms, bool &satisfied) {
    int vertices = vars * 2;
    vector<vector<int>> adj_list(vertices);
    for (auto &term : terms) {
        adj_list[not_x(term.first, vars)].push_back(term.second);
        adj_list[not_x(term.second, vars)].push_back(term.first);
    }
    vector<int> components = compress(vertices, adj_list);

    vector<bool> values(vars);
    satisfied = true;
    for (int v = 0; v < vars; ++v) {
        if (components[v] == components[not_x(v, vars)]) {
            satisfied = false;
            break;
        }

        if (components[v] < components[not_x(v, vars)]) {
            values[v] = false;
        } else {
            values[v] = true;
        }
    }
    return values;
}

// R  G  B
bool color_to_var(char color, char banned_color) {
    if (banned_color == 'R') {
        return color == 'G';
    } else {
        return color == 'R';
    }
}

// R  G  B
char var_to_color(bool var, char banned_color) {
    if (banned_color == 'R') {
        return var ? 'G' : 'B';
    } else if (banned_color == 'G') {
        return var ? 'R' : 'B';
    } else {
        return var ? 'R' : 'G';
    }
}

void recoloring(int n, string &banned_colors, vector<pair<int, int>> &edges, string &result, bool &satisfied) {
    vector<pair<int, int>> terms;
    for (auto &vu : edges) {
        int v = vu.first, u = vu.second;

        char ban_v = banned_colors[v];
        char ban_u = banned_colors[u];
        if (ban_v == ban_u) {
            terms.emplace_back(v, u);
            terms.emplace_back(not_x(v, n), not_x(u, n));
        } else {
            char common;
            if (ban_v != 'R' && ban_u != 'R') {
                common = 'R';
            } else if (ban_v != 'G' && ban_u != 'G') {
                common = 'G';
            } else {
                common = 'B';
            }

            terms.emplace_back(
                    not_x(color_to_var(common, ban_v) ? v : not_x(v, n), n),
                    not_x(color_to_var(common, ban_u) ? u : not_x(u, n), n)
            );
        }
    }

    vector<bool> values = solve_2_sat(n, terms, satisfied);
    if (satisfied) {
        for (int v = 0; v < n; ++v) {
            result += var_to_color(values[v], banned_colors[v]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        edges.emplace_back(v, u);
    }

    string banned_colors;
    for (int i = 0; i < n; ++i) {
        banned_colors += 'R';
    }

    string res;
    bool satisfied = false;
    while (true) {
        // random banned_colors
        for (int i = 0; i < n; ++i) {
            int color = rand() % 3;
            if (color == 0) {
                banned_colors[i] = 'R';
            } else if (color == 1) {
                banned_colors[i] = 'G';
            } else if (color == 2) {
                banned_colors[i] = 'B';
            }
        }
        
        recoloring(n, banned_colors, edges, res, satisfied);
        if (satisfied) {
            for (char ch : res) {
                if (ch == 'R') {
                    cout << "1 ";
                } else if (ch == 'G') {
                    cout << "2 ";
                } else {
                    cout << "3 ";
                }
            }
            cout << '\n';
            break;
        }
    }

    return 0;
}

/*

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        adj_list[v].push_back(u);
        adj_list[u].push_back(v);
    }

    vector<bool> in_A(n, true), in_I(n, false);
    vector<int> colors(n, -1);
    bool satisfied = false;
    gen_max_sets(n, in_A, in_I, adj_list, satisfied, colors);

    if (satisfied) {
        for (int color : colors) {
            cout << (color + 1) << ' ';
        }
        cout << '\n';
    } else {
        // we must not get here
    }

    return 0;
}
*/
