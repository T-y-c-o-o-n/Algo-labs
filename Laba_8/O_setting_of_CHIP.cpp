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
#define to_v(sz) static_cast<v_t>(sz)

size_t N;

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
		   to_v(-a) + to_v(N)
				 : to_v(a);
}

v_t get_not_v(int a) {
	return a > 0 ?
		   to_v(a) + to_v(N)
				 : to_v(-a);
}

v_t get_not_v(v_t v) {
	return (v <= to_v(N)) ? (v + to_v(N)) : (v - to_v(N));
}

void add_diz_in_2_SAT(v_t x, v_t y) {
	v_t not_x = get_not_v(x), not_y = get_not_v(y);

	E[to_sz(not_x)].push_back(y);
	H[to_sz(y)].push_back(not_x);

	E[to_sz(not_y)].push_back(x);
	H[to_sz(x)].push_back(not_y);
}

int main() {
// 	std::ios_base::sync_with_stdio(false);
// 	std::cin.tie(nullptr);
// 	std::cout.tie(nullptr);

	cin >> N;
	E.resize(2 * N + 1);
	H.resize(2 * N + 1);
	vector<int> wire_color(N + 1);
	for (size_t i = 1; i <= N; ++i) {
		cin >> wire_color[i];
	}
	vector<v_t> wire_no(2 * N);
	vector<pair<size_t, size_t> > place(N + 1, {3 * N + 9, 3 * N + 9});
	for (size_t i = 0; i < 2 * N; ++i) {
		cin >> wire_no[i];
		if (place[to_sz(wire_no[i])].first == 3 * N + 9) {
			place[to_sz(wire_no[i])].first = i;
		} else {
			place[to_sz(wire_no[i])].second = i;
		}
	}
	for (size_t i = 0; i < 2 * N; ++i) {
		if (wire_no[i] != wire_no[(i + 1) % (2 * N)] &&
			wire_color[to_sz(wire_no[i])] == wire_color[to_sz(wire_no[(i + 1) % (2 * N)])]) {
			v_t x = wire_no[i], y = wire_no[(i + 1) % (2 * N)];

			if (place[to_sz(x)].second == i) {
				x = get_not_v(x);
			}
			if (place[to_sz(y)].second == (i + 1) % (2 * N)) {
				y = get_not_v(y);
			}

			add_diz_in_2_SAT(get_not_v(x), get_not_v(y));
		}
	}

	used.resize(2 * N + 9, false);
	for (v_t v = 1; v <= 2 * N; ++v) {
		if (!used[to_sz(v)]) {
			dfs(v);
		}
	}
	reverse(order.begin(), order.end());

	comp.resize(2 * N + 1, -1);
	int color = 0;
	for (v_t v : order) {
		if (comp[to_sz(v)] == -1) {
			color++;
			SCC(v, color);
		}
	}

	vector<bool> ans(2 * N + 1, true);
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
			cout << (place[to_sz(v)].first + 1) << ' ';
		} else {
			cout << (place[to_sz(v)].second + 1) << ' ';
		}
	}
}
