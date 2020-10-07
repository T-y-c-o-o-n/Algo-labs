//
// Created by tycoon on 03.10.2020.
//
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

v_t get_v(int a) {
	return a < 0 ?
		   static_cast<v_t>(-a) + static_cast<v_t>(N)
				 : static_cast<v_t>(a);
}

v_t get_not_v(int a) {
	return a > 0 ?
		   static_cast<v_t>(a) + static_cast<v_t>(N)
				 : static_cast<v_t>(-a);
}

void add(v_t x, v_t y, v_t not_x, v_t not_y) {
	E[to_sz(not_x)].push_back(y);
	H[to_sz(y)].push_back(not_x);

	E[to_sz(not_y)].push_back(x);
	H[to_sz(x)].push_back(not_y);
}

int main() {
 	std::ios_base::sync_with_stdio(false);
 	std::cin.tie(nullptr);
 	std::cout.tie(nullptr);

	cin >> N >> M;
	E.resize(2 * N + 9);
	H.resize(2 * N + 9);
	for (size_t i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		v_t x = get_v(a), y = get_v(b), z = get_v(c);
		v_t not_x = get_not_v(a), not_y = get_not_v(b), not_z = get_not_v(c);
		add(x, y, not_x, not_y);
		add(y, z, not_y, not_z);
		add(z, x, not_z, not_x);
	}

	used.resize(2 * N + 9, false);
	for (v_t v = 1; v <= 2 * N; ++v) {
		if (!used[to_sz(v)]) {
			dfs(v);
		}
	}
	reverse(order.begin(), order.end());

	comp.resize(2 * N + 9, -1);
	int color = 0;
	for (v_t v : order) {
		if (comp[to_sz(v)] == -1) {
			color++;
			SCC(v, color);
		}
	}

	vector<bool> ans(2 * N + 9, true);
	for (v_t v = 1; to_sz(v) <= N; ++v) {
		if (comp[to_sz(v)] == comp[to_sz(v) + N]) {
			puts("NO");
			return 0;
		} else if (comp[to_sz(v)] < comp[to_sz(v) + N]) {
			ans[to_sz(v)] = false;
		} else if (comp[to_sz(v)] > comp[to_sz(v) + N]) {
			ans[to_sz(v)] = true;
		}
	}
	puts("YES");
	for (int v = 1; to_sz(v) <= N; ++v) {
		if (ans[to_sz(v)]) {
			cout << v << ' ';
		} else {
			cout << (-v) << ' ';
		}
	}
}
