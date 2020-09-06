#include <iostream>
#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::stack;

typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

#define to_sz(v) static_cast<size_t>(v)

size_t N, M;
vector<vector<v_t> > E;
vector<size_t> depth;

void dfs(v_t v) {
	size_t max_child_depth = 0;
	for (v_t u : E[to_sz(v)]) {
		if (depth[to_sz(u)] == 0) {
			dfs(u);
		}
		max_child_depth = std::max(depth[to_sz(u)], max_child_depth);
	}
	depth[to_sz(v)] = 1 + max_child_depth;
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	for (size_t i = 0; i < M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[to_sz(from)].push_back(to);
	}

	depth.resize(N + 1, 0);
	for (v_t v = 1; v <= N; ++v) {
		if (depth[to_sz(v)] == 0) {
			dfs(v);
		}
	}
	for (v_t v = 1; v <= N; ++v) {
		if (depth[to_sz(v)] == N) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
}
