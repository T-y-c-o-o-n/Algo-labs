#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::queue;
using std::string;

typedef uint64_t v_t;
typedef pair<v_t, v_t> edge;

#define ind(v) static_cast<size_t>(v)
#define all_v v_t v = 1; v <= N; ++v
size_t N, M;

vector<vector<pair<v_t, bool> > > E_full;
vector<vector<pair<v_t, bool> > > E;
vector<int> color;

bool dfs(v_t v, int c) {
	color[ind(v)] = c;
	for (auto vu : E[ind(v)]) {
		v_t u = vu.first;
		if (color[ind(u)] == -1) {
			if (!dfs(u, vu.second ? c : 1 - c)) {
				return false;
			}
		} else if (color[ind(u)] == vu.second ? 1 - c : c) {
			return false;
		}
	}
	return true;
}

int main() {
	cin >> N >> M;
	E_full.resize(N + 1);
	E.resize(N + 1);
	vector<pair<pair<v_t, v_t>, string> > data;
	for (size_t i = 0; i < M; ++i) {
		v_t v, u;
		string type;
		cin >> v >> u >> type;
		data.push_back({{v, u}, type});
		bool equals = type == "T";
		E_full[ind(v)].emplace_back(u, equals);
		E_full[ind(u)].emplace_back(v, equals);
	}
	size_t L = 0, R = M + 1;
	while (L + 1 < R) {
		size_t Mid = (L + R) / 2;
		color.clear();
		color.resize(N + 1, -1);
		for (auto &vect : E) {
			vect.clear();
		}
		for (size_t i = 0; i < Mid; ++i) {
			v_t v, u;
			string type;
			v = data[i].first.first;
			u = data[i].first.second;
			type = data[i].second;
			bool equals = type == "T";
			E[ind(v)].emplace_back(u, equals);
			E[ind(u)].emplace_back(v, equals);
		}
		bool can = true;
		for (all_v) {
			if (color[ind(v)] == -1) {
				if (!dfs(v, 0)) {
					can = false;
					continue;
				}
			}
		}
		if (can) {
			L = Mid;
//			 cout << "L = " << L << '\n';
		} else {
			R = Mid;
//			 cout << "R = " << R << '\n';
		}
	}
	cout <<  L << '\n';
}
