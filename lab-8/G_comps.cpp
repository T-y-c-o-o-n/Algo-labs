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
vector<int> comp;

void dfs(v_t v, int color) {
	comp[ind(v)] = color;
	for (v_t u : E[ind(v)]) {
		if (comp[ind(u)] == -1) {
			dfs(u, color);
		}
	}
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

	comp.resize(N + 1, -1);
	int color = 0;
	for (all_v) {
		if (comp[ind(v)] == -1) {
			color++;
			dfs(v, color);
		}
	}
	cout << color << '\n';
	for (all_v) {
		cout << comp[ind(v)] << ' ';
	}
	cout << '\n';
}
