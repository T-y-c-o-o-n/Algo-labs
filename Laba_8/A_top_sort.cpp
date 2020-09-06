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

#define to_sz(v) static_cast<size_t>(v)

size_t N, M;

vector<edge> E;
vector<vector<v_t> > EE;
vector<int> deg;
vector<v_t> ans;

void top_sort_1() {
	for (edge vu : E) {
		deg[to_sz(vu.second)]++;
	}
	queue<v_t> Q;
	for (v_t v = 1; v <= N; ++v) {
		if (deg[to_sz(v)] == 0) {
			Q.push(v);
		}
	}
	while (!Q.empty()) {
		v_t v = Q.front();
		Q.pop();
		ans.push_back(v);
		for (v_t u : EE[to_sz(v)]) {
			deg[to_sz(u)]--;
			if (deg[to_sz(u)] == 0) {
				Q.push(u);
			}
		}
	}
}

int main() {
	cin >> N >> M;
	deg.resize(N + 1, 0);
	EE.resize(N + 1);
	for (size_t i = 0; i < M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E.emplace_back(from, to);
		EE[to_sz(from)].push_back(to);
	}
	top_sort_1();
	if (ans.size() == N) {
		for (v_t v : ans) {
			cout << v << ' ';
		}
		cout << '\n';
	} else {
		cout << "-1\n";
	}
}
