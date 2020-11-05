#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::priority_queue;
using std::set;
using std::pair;
using std::reverse;
using std::min;

typedef uint32_t v_t;
#define to_sz(v) static_cast<size_t>(v)
#define to_v(v) static_cast<v_t>(v)
#define all_ind(i) size_t i = 1; i <= n; ++i
#define all(v) v_t v = 1; v <= n; ++v

struct edge {
    v_t from, to;
    int64_t weight;

    edge(v_t v, v_t u, int64_t w) : from(v), to(u), weight(w) {}
};

const int64_t INF = INT64_MAX;
size_t n;
vector<edge> graph;
vector<v_t> prev;

void ford_bellman_find_cycle(vector<v_t> &cycle, v_t start) {
    vector<int64_t> d(n + 1, INF);
    d[to_sz(start)] = 0;
    prev.resize(n + 1, 0);
    v_t end_of_cycle = 0;
    for (size_t i = 0; i < n; ++i) {
        for (edge &edge : graph) {
            v_t from = edge.from, to = edge.to;
            int64_t w = edge.weight;
            if (d[to_sz(from)] != INF) {
                int64_t new_dist = d[to_sz(from)] + w;
                if (new_dist < d[to_sz(to)]) {
                    if (i + 1 == n) {
                        end_of_cycle = to;
                    }
                    d[to_sz(to)] = new_dist;
                    prev[to_sz(to)] = from;
                }
            }
        }
    }
    if (end_of_cycle != 0) {
        for (size_t i = 0; i < n; ++i) {
            end_of_cycle = prev[to_sz(end_of_cycle)];
        }
        v_t temp = end_of_cycle;
        while (temp != end_of_cycle || cycle.empty()) {
            cycle.push_back(temp);
            temp = prev[to_sz(temp)];
        }
        cycle.push_back(temp);
        reverse(cycle.begin(), cycle.end());
    }
}

int main() {
    cin >> n;
    const auto no_edge = static_cast<int64_t>(1e9);
    for (all(v)) {
        for (all(u)) {
            int64_t weight;
            cin >> weight;
            if (weight != no_edge) {
                graph.emplace_back(v, u, weight);
            }
        }
    }
    n++;
    v_t start = to_v(n);
    for (all(v)) {
        if (v != start) {
            graph.emplace_back(start, v, 0);
        }
    }
    vector<v_t> cycle;
    ford_bellman_find_cycle(cycle, start);
    if (cycle.empty()) {
        puts("NO");
    } else {
        puts("YES");
        cout << cycle.size() << '\n';
        for (v_t v : cycle) {
            cout << v << ' ';
        }
        cout << '\n';
    }

    return 0;
}
