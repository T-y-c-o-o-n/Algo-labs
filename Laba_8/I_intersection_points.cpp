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

vector<vector<v_t> > E;
vector<int> dep;
vector<int> up;
vector<bool> used;
vector<bool> is_point;

void dfs(v_t v, v_t p, int depth) {
	dep[sz(v)] = depth;
	up[sz(v)] = depth;
	used[sz(v)] = true;
	bool point = false;
	int children_cnt = 0;
	for (v_t u : E[sz(v)]) {
		if (u == p) {
			continue;
		}
		if (!used[sz(u)]) {
			children_cnt++;
			dfs(u, v, depth + 1);
			up[sz(v)] = min(up[sz(v)], up[sz(u)]);
			if (p != 0 && up[sz(u)] >= dep[sz(v)]) {
				point = true;
			}
		} else {
			up[sz(v)] = min(up[sz(v)], dep[sz(u)]);
		}
	}
	if (p == 0 && children_cnt > 1) {
		point = true;
	}
	is_point[sz(v)] = point;
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	dep.resize(N + 1);
	up.resize(N + 1);
	used.resize(N + 1, false);
	is_point.resize(N + 1, false);
	for (size_t i = 1; i <= M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[sz(from)].push_back(to);
		E[sz(to)].push_back(from);
	}
	for (v_t v = 1; v <= N; ++v) {
		if (!used[sz(v)]) {
			dfs(v, 0, 0);
		}
	}
	size_t cnt = 0;
	for (v_t v = 1; v <= N; ++v) {
		if (is_point[sz(v)]) {
			cnt++;
		}
	}
	cout << cnt << '\n';
	for (v_t v = 1; v <= N; ++v) {
		if (is_point[sz(v)]) {
			cout << v << ' ';
		}
	}
}
/*
9 12
1 4
4 5
5 1
1 2
2 6
6 7
7 2
2 3
3 8
8 9
9 3
3 1
*/
