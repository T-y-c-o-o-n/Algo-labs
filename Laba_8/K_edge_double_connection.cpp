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

vector<vector<v_t> > E;
vector<int> dep;
vector<int> up;
vector<bool> used;
vector<int> color;
int temp_color;

void dfs(v_t v, v_t p, int depth, stack<v_t> &st) {
	dep[sz(v)] = depth;
	up[sz(v)] = depth;
	used[sz(v)] = true;
	st.push(v);
	for (v_t u : E[sz(v)]) {
		if (u == p) {
			continue;
		}
		if (!used[sz(u)]) {
			size_t sz_was = st.size();
			dfs(u, v, depth + 1, st);
			up[sz(v)] = min(up[sz(v)], up[sz(u)]);
			if (up[sz(u)] > dep[sz(v)]) {
//				 bridges.push_back(vu.second);
				temp_color++;
				while (st.size() > sz_was) {
					color[sz(st.top())] = temp_color;
					st.pop();
				}
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
	color.resize(N + 1);
	for (size_t i = 1; i <= M; ++i) {
		v_t from, to;
		cin >> from >> to;
		E[sz(from)].push_back(to);
		E[sz(to)].push_back(from);
	}
	temp_color = 0;
	stack<v_t> st;
	for (v_t v = 1; v <= N; ++v) {
		if (!used[sz(v)]) {
			dfs(v, 0, 0, st);
			temp_color++;
			while (!st.empty()) {
				color[sz(st.top())] = temp_color;
				st.pop();
			}
		}
	}
	cout << temp_color << '\n';
	for (v_t v = 1; v <= N; ++v) {
		cout << color[sz(v)] << ' ';
	}
}
