#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::string;

typedef uint64_t v_t;

#define ind(v) static_cast<size_t>(v)
#define all_v v_t v = 1; v <= N; ++v

size_t N;
vector<vector<v_t> > E, H;
vector<bool> reachable, generative;

void dfs(v_t v) {
	reachable[ind(v)] = true;
	for (v_t u : E[ind(v)]) {
		if (!reachable[ind(u)]) {
			dfs(u);
		}
	}
}

void dfs_back(v_t v) {
	generative[ind(v)] = true;
	for (v_t u : H[ind(v)]) {
		if (!generative[ind(u)]) {
			dfs_back(u);
		}
	}
}

int main() {
	cin >> N;
	E.resize(N + 1);
	H.resize(N + 1);
	vector<pair<pair<v_t, v_t>, int64_t> > edges;
	for (v_t from = 1; from <= N; ++from) {
		for (v_t to = 1; to <= N; ++to) {
			int64_t val;
			cin >> val;
			if (from != to) {
				edges.push_back({{from, to}, val});
			}
		}
	}
	int64_t L = -1, R = (int64_t)2e9;
	while (L + 1 < R) {
		int64_t Mid = (L + R) / 2;
		for (auto &vect : E) {
			vect.clear();
		}
		for (auto &vect : H) {
			vect.clear();
		}
		for (auto & edge : edges) {
			if (edge.second > Mid) {
				continue;
			}
			v_t from, to;
			from = edge.first.first;
			to = edge.first.second;
			E[ind(from)].push_back(to);
			H[ind(to)].push_back(from);
		}
		reachable.assign(N + 1, false);
		generative.assign(N + 1, false);
		dfs(1);
		dfs_back(1);
		bool can = true;
		for (all_v) {
			if (!generative[ind(v)] || !reachable[ind(v)]) {
				can = false;
				break;
			}
		}
		if (can) {
			R = Mid;
		} else {
			L = Mid;
		}
	}
	cout <<  R << '\n';
}
/*
5
0 1008 1009 309 1009
1009 0 1007 1009 1009
1009 1009 0 1009 200
1 1009 1009 0 1000
100 1009 1009 1009 0

 */
