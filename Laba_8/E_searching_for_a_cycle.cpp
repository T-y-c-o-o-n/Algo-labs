#include <iostream>
#include <cstdint>
#include <cstddef>
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
#define WHITE 0
#define GRAY  1
#define BLACK 2
vector<int> color;

bool dfs(v_t v) {
	static stack<v_t> path;
	color[to_sz(v)] = GRAY;
	path.push(v);
	if (path.size() == N) {
		return true;
	}
	for (v_t u : E[to_sz(v)]) {
		if (color[to_sz(u)] == WHITE) {
			if (dfs(u)) {
				return true;
			}
		}
	}
	path.pop();
	color[to_sz(v)] = BLACK;
	return false;
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	for (size_t i = 0; i < M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[to_sz(from)].push_back(to);
	}

	bool ans = false;
	color.resize(N + 1, false);
	for (v_t v = 1; v <= N; ++v) {
		if (color[to_sz(v)] == WHITE) {
			if (dfs(v)) {
				ans = true;
				break;
			}
		}
	}

	if (ans) {
		puts("YES");
	} else {
		puts("NO");
	}
}
