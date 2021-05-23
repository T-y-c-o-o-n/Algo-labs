//
// Created by tycoon on 13.05.2021.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string banned_colors;
    cin >> banned_colors;

    vector<pair<int, int>> terms;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;

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
                    not_x( color_to_var(common, ban_v) ? v : not_x(v, n) , n),
                    not_x( color_to_var(common, ban_u) ? u : not_x(u, n) , n)
            );
        }
    }

    bool satisfied;
    vector<bool> values = solve_2_sat(n, terms, satisfied);
    if (satisfied) {
        string ans;
        for (int v = 0; v < n; ++v) {
            ans += var_to_color(values[v], banned_colors[v]);
        }
        cout << ans << '\n';
    } else {
        puts("Impossible");
    }

    return 0;
}
