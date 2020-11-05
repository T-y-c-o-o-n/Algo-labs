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
using std::max;
using std::min;
using std::ostream;
using std::istream;

typedef int32_t v_t;

struct edge {
    int64_t weight;
    v_t v, u;
};

struct dsu_info {
    v_t par;
    size_t size;

    dsu_info() {}

    dsu_info(v_t par) : par(par), size(1) {}
};

const int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n, m;
vector<edge> edges;

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
    if (dsu[v_1].size > dsu[v_2].size) {
        swap(v_1, v_2);
    }
    dsu[v_2].par = v_1;
    dsu[v_1].size += dsu[v_2].size;
}

vector<vector<v_t>> v_edges;
vector<bool> used;

void dfs(v_t v) {
    used[v] = true;
    for (v_t to : v_edges[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int64_t tight_kruskal(bool &no_ans) {
    sort(edges.begin(), edges.end(), [](edge const &a, edge const &b) {
        return a.weight < b.weight;
    });
    dsu.resize(n + 1);

    no_ans = false;
    used.resize(n + 1, false);
    dfs(1);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        if (!used[v]) {
            no_ans = true;
            return 0;
        }
    }
    int64_t ans = INF;
    for (size_t min_edge_no = 0; min_edge_no < edges.size(); ++min_edge_no) {
        for (v_t v = 1; v <= (v_t) n; ++v) {
            dsu[v] = v;
        }
        int64_t max_edge = -INF, min_edge = INF;
        size_t edges_count = 0;
        for (size_t j = min_edge_no; j < edges.size(); ++j) {
            edge edge = edges[j];
            v_t v_1 = edge.v;
            v_t v_2 = edge.u;
            if (find(v_1) != find(v_2)) {
                max_edge = max(edge.weight, max_edge);
                min_edge = min(edge.weight, min_edge);
                unite(v_1, v_2);
                edges_count++;
            }
        }
        int64_t res = max_edge - min_edge;
        if (edges_count == n - 1 && res < ans) {
            ans = res;
        }
    }

    return ans;
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    v_edges.resize(n + 1);
    for (size_t i = 0; i < m; ++i) {
        cin >> edges[i].v >> edges[i].u >> edges[i].weight;
        v_edges[edges[i].v].push_back(edges[i].u);
        v_edges[edges[i].u].push_back(edges[i].v);
    }
    bool no_ans = true;
    int64_t ans = tight_kruskal(no_ans);
    if (no_ans) {
        puts("NO");
    } else {
        puts("YES");
        cout << ans << '\n';
    }

    return 0;
}
