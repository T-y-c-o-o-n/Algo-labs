//
// Created by tycoon on 04.10.2020.
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
using std::swap;

typedef uint64_t v_t;

#define to_sz(v) static_cast<size_t>(v)
#define to_v(sz) static_cast<v_t>(sz)
#define all_v v_t v = 1; v <= to_v(n); ++v

size_t n, m;
bool exists_simple_cycle;
bool exists_difficult_cycle;
vector<v_t> simple_cycle;
vector<v_t> difficult_cycle;
vector<vector<v_t> > E;
vector<int> depth;
vector<int> in;
vector<int> out;
vector<v_t> parent;
vector<bool> used;
vector<vector<pair<v_t, v_t> > > up;

void pre_dfs(v_t v, v_t p, int temp_depth) {
	static int t = 0;
	in[to_sz(v)] = t++;
	used[to_sz(v)] = true;
	parent[to_sz(v)] = p;
	depth[to_sz(v)] = temp_depth;

	for (v_t u : E[to_sz(v)]) {
		if (u == p) continue;

		if (!used[to_sz(u)]) {
			pre_dfs(u, v, temp_depth + 1);
		}
	}

	out[to_sz(v)] = t;
}

bool v_in_tree_g(v_t v, v_t g) {
	return in[to_sz(g)] <= in[to_sz(v)] && out[to_sz(v)] <= out[to_sz(g)];
}

void dfs(v_t v, v_t p) {
	used[to_sz(v)] = true;

	for (v_t u : E[to_sz(v)]) {
		if (u == p) continue;

		if (!used[to_sz(u)]) {
			dfs(u, v);

			for (auto uw : up[to_sz(u)]) {
				if (up[to_sz(v)].size() < 2 && depth[to_sz(uw.second)] < depth[to_sz(v)]) {
					up[to_sz(v)].push_back(uw);
				}
			}

			if (up[to_sz(u)].size() >= 2) {
				if (!exists_difficult_cycle) {
					exists_difficult_cycle = true;
					v_t elder1 = up[to_sz(u)][0].second;
					v_t elder2 = up[to_sz(u)][1].second;
					v_t child1 = up[to_sz(u)][0].first;
					v_t child2 = up[to_sz(u)][1].first;
					if (depth[to_sz(elder1)] < depth[to_sz(elder2)]) {
						swap(elder1, elder2);
						swap(child1, child2);
					}

					difficult_cycle.push_back(child1);
					difficult_cycle.push_back(elder1);
					v_t temp = elder1;
					while (temp != elder2) {
						temp = parent[to_sz(temp)];
						difficult_cycle.push_back(temp);
					}

					if (v_in_tree_g(child1, child2)
						|| v_in_tree_g(child2, child1)) {
						if (depth[to_sz(child2)] > depth[to_sz(child1)]) {
							temp = child2;
							while (temp != child1) {
								difficult_cycle.push_back(temp);
								temp = parent[to_sz(temp)];
							}
						} else if (depth[to_sz(child2)] < depth[to_sz(child1)]) {
							vector<v_t> vect;
							temp = child1;
							while (temp != child2) {
								temp = parent[to_sz(temp)];
								vect.push_back(temp);
							}
							reverse(vect.begin(), vect.end());
							for (v_t temp1 : vect) {
								difficult_cycle.push_back(temp1);
							}
						}
					} else {
						temp = child2;
						while (!v_in_tree_g(child1, temp)) {
							difficult_cycle.push_back(temp);
							temp = parent[to_sz(temp)];
						}

						vector<v_t> vect;
						v_t temp1 = child1;
						while (temp1 != temp) {
							temp1 = parent[to_sz(temp1)];
							vect.push_back(temp1);
						}
						reverse(vect.begin(), vect.end());
						for (v_t temp2 : vect) {
							difficult_cycle.push_back(temp2);
						}
					}
				}
			}
		} else if (depth[to_sz(u)] < depth[to_sz(v)]) {
			if ((depth[to_sz(v)] % 2) != (depth[to_sz(u)] % 2)) {
				if (!exists_simple_cycle) {
					exists_simple_cycle = true;
					v_t g = v;
					do {
						simple_cycle.push_back(g);
						g = parent[to_sz(g)];
					} while (simple_cycle.back() != u);
				}
			}

			if (up[to_sz(v)].size() < 2) {
				up[to_sz(v)].emplace_back(v, u);
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	size_t T;
	cin >> T;
	for (size_t k = 0; k < T; ++k) {
		cin >> n >> m;
		E.clear();
		E.resize(n + 1);
		for (size_t i = 0; i < m; ++i) {
			v_t v, u;
			cin >> v >> u;
			E[to_sz(v)].push_back(u);
			E[to_sz(u)].push_back(v);
		}
		depth.clear();
		depth.resize(n + 1);
		out.clear();
		out.resize(n + 1);
		in.clear();
		in.resize(n + 1);
		parent.clear();
		parent.resize(n + 1);
		used.clear();
		used.resize(n + 1, false);
		up.clear();
		up.resize(n + 1);
		for (all_v) {
			if (!used[to_sz(v)]) {
				pre_dfs(v, 0, 0);
			}
		}
		exists_simple_cycle = false;
		exists_difficult_cycle = false;
		used.clear();
		used.resize(n + 1, false);
		for (all_v) {
			if (!used[to_sz(v)]) {
				dfs(v, 0);
			}
		}
		if (exists_simple_cycle) {
			cout << simple_cycle.size() << '\n';
			for (v_t v : simple_cycle) {
				cout << v << ' ';
			}
			cout << '\n';
		} else if (exists_difficult_cycle) {
			cout << difficult_cycle.size() << '\n';
			for (v_t v : difficult_cycle) {
				cout << v << ' ';
			}
			cout << '\n';
		} else {
				cout << "-1\n";
		}
	}
}
/*

1
12 13
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
8 2
10 4

 */
/*

1
12 14
1 2
2 3
3 4
4 5
5 6
4 6
6 7
7 8
8 9
9 1
1 10
10 11
11 12
12 2
*/
