#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::queue;

typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

#define ind(v) static_cast<size_t>(v)
#define all_v v_t v = 1; v <= N; ++v
size_t N, M;

vector<vector<v_t> > E;
vector<int> color;

bool dfs(v_t v, int c) {
	color[ind(v)] = c;
	for (v_t u : E[ind(v)]) {
		if (color[ind(u)] == -1) {
			if (!dfs(u, 1 - c)) {
				return false;
			}
		} else if (color[ind(u)] == c) {
			return false;
		}
	}
	return true;
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	for (size_t i = 0; i < M; ++i) {
		v_t v, u;
		cin >> v >> u;
		E[ind(v)].push_back(u);
		E[ind(u)].push_back(v);
	}

	color.resize(N + 1, -1);
	for (all_v) {
		if (color[ind(v)] == -1) {
			if (!dfs(v, 0)) {
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
}
