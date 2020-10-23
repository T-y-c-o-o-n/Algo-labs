#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <algorithm>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::queue;
using std::reverse;

#define to_sz(v) static_cast<size_t>(v)
typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

constexpr int64_t INF = static_cast<int64_t>(INT32_MAX);
size_t n, m;
vector<edge> G;
vector<vector<v_t> > E;
vector<v_t> order;

void top_sort() {
	vector<int64_t> deg;
	deg.resize(n + 1, 0);
	for (edge vu : G) {
		deg[to_sz(vu.second)]++;
	}
	queue<v_t> Q;
	for (v_t v = 1; v <= n; ++v) {
		if (deg[to_sz(v)] == 0) {
			Q.push(v);
		}
	}
	while (!Q.empty()) {
		v_t v = Q.front();
		Q.pop();
		order.push_back(v);
		for (v_t u : E[to_sz(v)]) {
			deg[to_sz(u)]--;
			if (deg[to_sz(u)] == 0) {
				Q.push(u);
			}
		}
	}
}


int main() {
	v_t start;
	cin >> n >> m >> start;
	E.resize(n + 1);
	for (size_t i = 0; i < m; ++i) {
		v_t from, to;
		cin >> from >> to;
		G.emplace_back(from, to);
		E[to_sz(from)].push_back(to);
	}
	vector<bool> dp;
	dp.resize(n + 1);

	top_sort();
	reverse(order.begin(), order.end());
	for (v_t v : order) {
		dp[to_sz(v)] = false;
		for (v_t u : E[to_sz(v)]) {
			if (!dp[to_sz(u)]) {
				dp[to_sz(v)] = true;
				break;
			}
		}
	}
	if (dp[to_sz(start)]) {
		puts("First player wins");
	} else {
		puts("Second player wins");
	}
}
