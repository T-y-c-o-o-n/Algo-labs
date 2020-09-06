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
vector<vector<v_t> > H;
vector<vector<pair<v_t, int64_t> > > E_weighted;
vector<int64_t> deg;
vector<v_t> order;
vector<bool> v_to_t;

void top_sort() {
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

void dfs(v_t u) {
	v_to_t[to_sz(u)] = true;
	for (v_t v : H[to_sz(u)]) {
		if (!v_to_t[to_sz(v)]) {
			dfs(v);
		}
	}
}

int main() {
	v_t s, t;
	cin >> n >> m >> s >> t;
	deg.resize(n + 1, 0);
	E.resize(n + 1);
	H.resize(n + 1);
	E_weighted.resize(n + 1);
	for (size_t i = 0; i < m; ++i) {
		v_t from, to;
		int64_t weight;
		cin >> from >> to >> weight;
		G.emplace_back(from, to);
		E[to_sz(from)].push_back(to);
		H[to_sz(to)].push_back(from);
		E_weighted[to_sz(from)].emplace_back(to, weight);
	}
	top_sort();
	reverse(order.begin(), order.end());
	vector<int64_t> dp;
	dp.resize(n + 1, INF);
	dp[to_sz(t)] = 0;

	v_to_t.resize(n + 1, false);
	dfs(t);
	if (!v_to_t[to_sz(s)]) {
		return cout << "Unreachable\n", 0;
	}
	for (v_t v : order) {
		if (!v_to_t[to_sz(v)]) {
			continue;
		}
		for (auto vwu : E_weighted[to_sz(v)]) {
			if (vwu.second + dp[to_sz(vwu.first)] < dp[to_sz(v)]) {
				dp[to_sz(v)] = vwu.second + dp[to_sz(vwu.first)];
			}
		}
	}
	cout << dp[to_sz(s)] << '\n';
}
