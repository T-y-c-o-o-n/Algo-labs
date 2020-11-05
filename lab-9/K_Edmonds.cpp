#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::swap;
using std::set;
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

size_t n, m;
vector<pair<int64_t, set<pair<int64_t, v_t>>>> edges_to;
vector<bool> took;
vector<v_t> selected_edge_to;
vector<v_t> temp_set;

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
        pair<int64_t, v_t> edge = (*edges_to[v].second.begin());  // extract_min
        edges_to[v].second.erase(edges_to[v].second.begin());
        from = edge.second;
        weight = edge.first + edges_to[v].first;
        from = find(from);
    }

    ans += weight;
    edges_to[v].first -= weight;

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
        v_t container = v;  // vertex for saving all edges to cycle
        while (temp != v) {
            dsu[temp].par = v;
//            dsu[v].size++;

            // merge of treaps
            v_t donor = temp;
            if (edges_to[donor].second.size() > edges_to[container].second.size()) {
                swap(donor, container);
            }
            while (!edges_to[donor].second.empty()) {
                pair<int64_t, v_t> edge = (*edges_to[donor].second.begin());  // extract_min
                edges_to[donor].second.erase(edges_to[donor].second.begin());
                edge.first += edges_to[donor].first - edges_to[container].first;
                edges_to[container].second.insert(edge);
            }

            temp = selected_edge_to[temp];
        }
        up(container, start, ans);
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
        edges_to[to].second.insert({weight, from});
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

    puts("YES");
    cout << edmonds(start) << '\n';

    return 0;
}
