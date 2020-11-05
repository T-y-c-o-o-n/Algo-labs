#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::swap;
using std::abs;
using std::sqrt;
using std::pair;
using std::ostream;
using std::istream;

typedef int32_t v_t;

struct edge {
    int32_t weight;
    v_t v, u;

    edge(int32_t weight, v_t v, v_t u) : weight(weight), v(v), u(u) {}
};

struct dsu_info {
    v_t par;
    size_t size;

    dsu_info(v_t par) : par(par), size(1) {}

    dsu_info() : par(0), size(0) {}
};

size_t n;
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

double kruskal() {
    sort(edges.begin(), edges.end(), [](edge const &a, edge const &b) {
        return a.weight < b.weight;
    });
    dsu.resize(n + 1);
    for (v_t v = 1; v <= (v_t) n; ++v) {
        dsu[v] = v;
    }

    double ans = 0;
    for (edge &edge : edges) {
        v_t v_1 = edge.v;
        v_t v_2 = edge.u;
        if (find(v_1) != find(v_2)) {
            ans += sqrt((double) edge.weight);
            unite(v_1, v_2);
        }
    }

    return ans;
}

int32_t square_dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    cin >> n;
    vector<pair<int32_t, int32_t>> points(n + 1);
    for (v_t i = 1; i <= (v_t) n; ++i) {
        cin >> points[i].first >> points[i].second;
    }
    for (v_t u = 2; u <= (v_t) n; ++u) {
        for (v_t v = 1; v < u; ++v) {
            edges.emplace_back(square_dist(points[v].first, points[v].second,
                                           points[u].first, points[u].second), v, u);
        }
    }
    cout << std::fixed << std::setprecision(14) << kruskal() << '\n';

    return 0;
}
