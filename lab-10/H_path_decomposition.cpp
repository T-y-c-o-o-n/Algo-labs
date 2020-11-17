//
// Created by tycoon on 12.11.2020.
//
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::ios_base;
using std::vector;
using std::multiset;
using std::pair;

using v_t = int32_t;

struct edge {
    v_t to;
    bool deleted;
    size_t copy_ind;

    edge() : to(0), deleted(false), copy_ind(0) {}

    explicit edge(v_t to) : to(to), deleted(false), copy_ind(0) {}
};

bool operator<(const edge &a, const edge &b) {
    return a.to < b.to;
}

size_t n;
vector<vector<edge>> edges;
vector<bool> used;

void euler(v_t v, vector<pair<v_t, v_t>> &order) {
    for (edge &vu : edges[v]) {
        if (vu.deleted) {
            continue;
        }
        v_t to = vu.to;
        vu.deleted = true;
        edges[to][vu.copy_ind].deleted = true;
        euler(to, order);
        order.emplace_back(to, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // input
    size_t m;
    cin >> n >> m;
    v_t dop_vertex = (v_t) (n + 1);
    edges.assign(n + 5, vector<edge>());
    for (size_t i = 0; i < m; ++i) {
        v_t v, u;
        cin >> v >> u;
        edges[v].push_back(edge(u));
        edges[u].push_back(edge(v));
        edges[v].back().copy_ind = edges[u].size() - 1;
        edges[u].back().copy_ind = edges[v].size() - 1;
    }

    // adding edges between dop vertex and odd vertices
    for (v_t v = 1; v <= (v_t) n; ++v) {
        if (edges[v].size() % 2 == 1) {
            edges[v].push_back(edge(dop_vertex));
            edges[dop_vertex].push_back(edge(v));
            edges[v].back().copy_ind = edges[dop_vertex].size() - 1;
            edges[dop_vertex].back().copy_ind = edges[v].size() - 1;
        }
    }

    // euler tour
    vector<pair<v_t, v_t>> edge_order;
    used.resize(dop_vertex + 1);
    euler(dop_vertex, edge_order);
    for (v_t v = 1; v <= dop_vertex; ++v) {
        if (!used[v]) {
            euler(v, edge_order);
        }
    }

    vector<v_t> vertex_order;
    if (!edge_order.empty()) {
        vertex_order.push_back(edge_order.front().first);
    }
    for (size_t i = 0; i < edge_order.size(); ++i) {
        auto &vu = edge_order[i];
        if (i > 0 && edge_order[i - 1].second != edge_order[i].first) {
            vertex_order.push_back(dop_vertex);
            vertex_order.push_back(edge_order[i].first);
        }
        vertex_order.push_back(vu.second);
    }

    // output
    vector<vector<v_t> > paths;
    size_t ind = 0;
    for (size_t i = 0; i < vertex_order.size(); ++i) {
        v_t v = vertex_order[i];
        if (i == 0 && v == dop_vertex) {
            continue;
        }

        if (v != dop_vertex) {
            paths.resize(ind + 1);
            paths[ind].push_back(v);
        } else {
            ind++;
        }
    }

    cout << paths.size() << '\n';
    for (auto const &path : paths) {
        for (v_t v : path) {
            cout << v << ' ';
        }
        cout << '\n';
    }
}
