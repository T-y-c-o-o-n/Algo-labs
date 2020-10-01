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

size_t N = 26;

vector<edge> G;
vector<vector<v_t> > E;
vector<int> deg;
vector<v_t> order;

void top_sort_1() {
	for (edge vu : G) {
		deg[ind(vu.second)]++;
	}
	queue<v_t> Q;
	for (v_t v = 1; v <= N; ++v) {
		if (deg[ind(v)] == 0) {
			Q.push(v);
		}
	}
	while (!Q.empty()) {
		v_t v = Q.front();
		Q.pop();
		order.push_back(v);
		for (v_t u : E[ind(v)]) {
			deg[ind(u)]--;
			if (deg[ind(u)] == 0) {
				Q.push(u);
			}
		}
	}
}

v_t to_v(char ch) {
	return ch - 'a' + 1;
}

void analize(string const &a, string const &b) {
	for (size_t i = 0; i < a.length(); ++i) {
		if (a[i] != b[i]) {
			G.emplace_back(to_v(a[i]), to_v(b[i]));
			E[ind(to_v(a[i]))].push_back(to_v(b[i]));
//			 cout << to_v(a[i]) << " -> " << to_v(b[i]) << '\n';
			return;
		}
	}
	G.emplace_back(to_v(a[0]), to_v(b[0]));
	E[ind(to_v(a[0]))].push_back(to_v(b[0]));
	E[ind(to_v(a[0]))].push_back(to_v(b[0]));
}

int main() {
	size_t cnt;
	cin >> cnt;
	deg.resize(N + 1, 0);
	E.resize(N + 1);
	vector<string> nums;
	for (size_t i = 0; i < cnt; ++i) {
		string num;
		cin >> num;
		if (!nums.empty() && nums.front().length() == num.length()) {
			for (auto const &a : nums) {
				analize(a, num);
			}
		} else {
			nums.clear();
		}
		nums.push_back(num);
	}
	top_sort_1();
	if (order.size() == N) {
		puts("YES");
		vector<size_t> ans(N);
//		 puts("order : ");
		for (size_t i = 0; i < order.size(); ++i) {
//			 cout << order[i] << ' ';
			ans[ind(order[i]) - 1] = i;
		}
//		 puts("\nans : ");
		for (size_t i : ans) {
			cout << i << ' ';
		}
		cout << '\n';
	} else {
		puts("NO");
	}
}
