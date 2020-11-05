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

int64_t kruskal() {
    sort(edges.begin(), edges.end(), [](edge const &a, edge const &b) {
        return a.weight < b.weight;
    });
    dsu.resize(n + 1);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        dsu[v] = v;
    }

    int64_t ans = 0;
    for (edge &edge : edges) {
        v_t v_1 = edge.v;
        v_t v_2 = edge.u;
        if (find(v_1) != find(v_2)) {
            ans += edge.weight;
            unite(v_1, v_2);
        }
    }

    return ans;
}

int main() {
    cin >> n >> m;
    edges.resize(m);
    for (size_t i = 0; i < m; ++i) {
        cin >> edges[i].v >> edges[i].u >> edges[i].weight;
    }
    cout << kruskal() << '\n';

    return 0;
}
