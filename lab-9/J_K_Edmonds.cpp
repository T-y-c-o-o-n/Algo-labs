#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::swap;
using std::pair;
using std::ostream;
using std::istream;

typedef int32_t v_t;

struct edge {
    int64_t weight;
    v_t from, to;
};

struct dsu_info {
    v_t par;

    dsu_info() {}

    dsu_info(v_t par) : par(par) {}
};

vector<dsu_info> dsu;

v_t find(v_t v) {
    if (dsu[v].par == v) {
        return v;
    }
    return dsu[v].par = find(dsu[v].par);
}

void unite(v_t v_1, v_t v_2) {
    v_1 = find(v_1);
    v_2 = find(v_2);
//    if (dsu[v_1].size > dsu[v_2].size) {
//        swap(v_1, v_2);
//    }
    dsu[v_2].par = v_1;
//    dsu[v_1].size += dsu[v_2].size;
}

const int64_t INF = static_cast<int64_t>(INT64_MAX);
size_t n, m;
vector<vector<pair<int64_t, v_t>>> edges_to;
vector<bool> took;
vector<v_t> selected_edge_to;
vector<v_t> temp_set;

vector<pair<int64_t, v_t>> merge(vector<pair<int64_t, v_t>> a, vector<pair<int64_t, v_t>> b) {
    vector<pair<int64_t, v_t>> res;
    size_t size = a.size() + b.size();
    for (size_t i = 0; i < size; ++i) {
        if (a.empty() || (!b.empty() && b.back().first < a.back().first)) {
            res.push_back(b.back());
            b.pop_back();
        } else {
            res.push_back(a.back());
            a.pop_back();
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

void up(v_t v, v_t start, int64_t &ans) {
    if (v == start) {
        return;
    }
    if (!took[v]) {
        temp_set.push_back(v);
    }
    took[v] = true;
    v_t from = v;
    int64_t weight;
    while (from == v) {
        auto edge = edges_to[v].back();  // extract_min
        edges_to[v].pop_back();
        from = edge.second;
        weight = edge.first;
        from = find(from);
    }

    ans += weight;
    for (auto &vu : edges_to[v]) {  // adding
        vu.first -= weight;
    }


    if (from == start) {  // 1 - from start
        selected_edge_to[v] = from;
        for (v_t u : temp_set) {
            dsu[u].par = start;
//            dsu[start].size++;
        }
        temp_set.clear();
        return;
    }
    if (took[from]) {  // 2 - cycle
        selected_edge_to[v] = from;
        v_t temp = from;
        while (temp != v) {
            dsu[temp].par = v;
//            dsu[v].size++;
            edges_to[v] = merge(edges_to[v], edges_to[temp]);  // merge of treaps
            edges_to[temp].clear();
            temp = selected_edge_to[temp];
        }
        up(v, start, ans);
    } else {  // 3 - from usual vertex
        selected_edge_to[v] = from;
        up(from, start, ans);
    }
}

int64_t edmonds(v_t start) {
    took.resize(n + 1);
    selected_edge_to.resize(n + 1);
    dsu.resize(n + 1);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        dsu[v] = v;
    }
    int64_t ans = 0;
    for (v_t v = 1; v <= (v_t) n; ++v) {
        if (!took[v]) {
            up(v, start, ans);
        }
    }
    return ans;
}

vector<vector<v_t>> edges_from;
vector<bool> used;

void dfs(v_t v) {
    used[v] = true;
    for (v_t to : edges_from[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main() {
    cin >> n >> m;
    v_t start = 1;
    edges_to.resize(n + 1);
    edges_from.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        v_t from, to;
        int64_t weight;
        cin >> from >> to >> weight;
        edges_from[from].push_back(to);
        edges_to[to].emplace_back(weight, from);
    }
    used.resize(n + 1, false);
    dfs(start);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        if (!used[v]) {
            puts("NO");
            return 0;
        }
    }
    used.clear();
    edges_from.clear();

    for (v_t v = 1; v <= (v_t) n; ++v) {
        sort(edges_to[v].rbegin(), edges_to[v].rend());
    }

    puts("YES");
    cout << edmonds(start) << '\n';

    return 0;
}
