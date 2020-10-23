#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::reverse;

typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

#define to_sz(v) static_cast<size_t>(v)

size_t N, M;

vector<vector<v_t> > E;
vector<vector<v_t> > H;
vector<v_t> order;
vector<int> comp;

vector<bool> used;
void dfs(v_t v) {
	used[to_sz(v)] = true;
	for (v_t u : E[to_sz(v)]) {
		if (!used[to_sz(u)]) {
			dfs(u);
		}
	}
	order.push_back(v);
}

void SCC(v_t u, int color) {
	comp[to_sz(u)] = color;
	for (v_t v : H[to_sz(u)]) {
		if (comp[to_sz(v)] == -1) {
			SCC(v, color);
		}
	}
}

int main() {
	cin >> N >> M;
	E.resize(N + 1);
	H.resize(N + 1);
	for (size_t i = 0; i < M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[to_sz(from)].push_back(to);
		H[to_sz(to)].push_back(from);
	}

	used.resize(N + 1, false);
	for (v_t v = 1; v <= N; ++v) {
		if (!used[to_sz(v)]) {
			dfs(v);
		}
	}
	reverse(order.begin(), order.end());

	comp.resize(N + 1, -1);
	int color = 0;
	for (v_t v : order) {
		if (comp[to_sz(v)] == -1) {
			color++;
			SCC(v, color);
		}
	}

	cout << color << '\n';
	for (size_t i = 1; i <= N; ++i) {
		cout << comp[i] << ' ';
	}
	cout << '\n';
}
