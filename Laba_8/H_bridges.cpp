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
using std::min;
using std::sort;

typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

#define sz(v) static_cast<size_t>(v)

size_t N, M;

vector<vector<pair<v_t, size_t> > > E;
vector<int> dep;
vector<int> up;
vector<bool> used;
vector<size_t> bridges;

void dfs(v_t v, v_t p, int depth) {
	dep[sz(v)] = depth;
	up[sz(v)] = depth;
	used[sz(v)] = true;
	for (auto vu : E[sz(v)]) {
		v_t u = vu.first;
		if (u == p) {
			continue;
		}
		if (!used[sz(u)]) {
			dfs(u, v, depth + 1);
			up[sz(v)] = min(up[sz(v)], up[sz(u)]);
			if (up[sz(u)] > dep[sz(v)]) {
				bridges.push_back(vu.second);
			}
		} else {
			up[sz(v)] = min(up[sz(v)], dep[sz(u)]);
		}
	}
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	dep.resize(N + 1);
	up.resize(N + 1);
	used.resize(N + 1, false);
	for (size_t i = 1; i <= M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[sz(from)].emplace_back(to, i);
		E[sz(to)].emplace_back(from, i);
	}
	for (v_t v = 1; v <= N; ++v) {
		if (!used[sz(v)]) {
			dfs(v, 0, 0);
		}
	}
	sort(bridges.begin(), bridges.end());
	cout << bridges.size() << '\n';
	for (size_t bridge_no : bridges) {
		cout << bridge_no << ' ';
	}
}
