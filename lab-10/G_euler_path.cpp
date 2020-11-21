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
vector<multiset<edge>> edges;

void euler(v_t v, vector<pair<v_t, v_t>> &order) {
    while (!edges[v].empty()) {
        auto edge_it = edges[v].begin();
        v_t to = (*edge_it).to;

        edges[v].erase(edge_it);
        auto copy_edge_it = edges[to].find(edge(v));
        if (copy_edge_it != edges[to].end()) {
            edges[to].erase(copy_edge_it);
        }

        euler(to, order);
        order.emplace_back(to, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // input
    size_t m = 0;
    cin >> n;
    size_t cnt_odd = 0;
    v_t odd_v = -1;
    edges.assign(n + 1, multiset<edge>());
    for (v_t v = 1; v <= (v_t) n; ++v) {
        size_t deg;
        cin >> deg;
        m += deg;
        if ((deg % 2) == 1) {
            cnt_odd++;
            odd_v = v;
        }
        for (size_t i = 0; i < deg; ++i) {
            v_t u;
            cin >> u;
            edges[v].insert(edge(u));
        }
    }
    m /= 2;

    if (cnt_odd != 0 && cnt_odd != 2) {
        return cout << "-1\n", 0;
    }
    vector<pair<v_t, v_t>> order;
    v_t start = (odd_v == -1) ? 1 : odd_v;
    euler(start, order);
    if (order.size() != m) {
        return cout << "-1\n", 0;
    }
    cout << m << '\n';
    if (!order.empty()) {
        cout << order.front().first;
    } else {
        cout << '1';
    }
    for (auto vu : order) {
        cout << ' ' << vu.second;
    }
    cout << '\n';
}
