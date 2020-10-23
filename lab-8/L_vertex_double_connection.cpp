#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <stack>
#include <algorithm>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::stack;
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
vector<int> color;
int temp_color;

void dfs(v_t v, v_t p, int depth, stack<size_t> &st) {
	dep[sz(v)] = depth;
	up[sz(v)] = depth;
	used[sz(v)] = true;
	for (auto vu : E[sz(v)]) {
		v_t u = vu.first;
		if (u == p) {
			continue;
		}
		if (!used[sz(u)]) {
			size_t sz_was = st.size();
			st.push(vu.second);
			dfs(u, v, depth + 1, st);
			up[sz(v)] = min(up[sz(v)], up[sz(u)]);
			if (up[sz(u)] >= dep[sz(v)]) {
				temp_color++;
				while (st.size() > sz_was) {
					color[st.top()] = temp_color;
					st.pop();
				}
			}
		} else {
			if (dep[sz(u)] < dep[sz(v)]) {
				st.push(vu.second);
			}
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
	color.resize(M, false);
	for (size_t i = 0; i < M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[sz(from)].emplace_back(to, i);
		E[sz(to)].emplace_back(from, i);
	}
	temp_color = 0;
	stack<size_t> st;
	for (v_t v = 1; v <= N; ++v) {
		if (!used[sz(v)]) {
			dfs(v, 0, 0, st);
		}
	}
	cout << temp_color << '\n';
	for (int edge_color : color) {
		cout << edge_color << ' ';
	}
}
