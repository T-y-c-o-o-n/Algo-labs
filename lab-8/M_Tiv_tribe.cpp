#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <queue>
#include <set>
#include <string>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::queue;
using std::set;
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
	return (ch - 'a' + 1);
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
	bool cannot = false;
	set<v_t> banned_for_0;
	for (size_t i = 0; i < cnt; ++i) {
		string num;
		cin >> num;
		if (num.length() > 1) {
			banned_for_0.insert(to_v(num[0]));
		}
		if (!nums.empty()) {
			for (auto const &a : nums) {
				if (a.length() > num.length() || a == num) {
					cannot = true;
				}
				if (a.length() == num.length()) {
					analize(a, num);
				}
			}
		}
		nums.push_back(num);
	}
	if (cannot) {
		puts("NO");
		return 0;
	}
	top_sort_1();
	if (order.size() == N) {
		v_t zero_v = 0;
		vector<bool> source(N + 1, true);
		for (auto &vu : G) {
			source[ind(vu.second)] = false;
		}
		for (v_t v = 1; v <= N; ++v) {
			if (source[ind(v)] && banned_for_0.find(v) == banned_for_0.end()) {
				zero_v = v;
				break;
			}
		}
		if (zero_v == 0) {
			puts("NO");
			return 0;
		}

		puts("YES");
		vector<size_t> digit(N + 1, 999);
		size_t temp_digit = 0;
		digit[ind(zero_v)] = temp_digit++;
		for (v_t v : order) {
			if (v != zero_v) {
				digit[ind(v)] = temp_digit++;
			}
		}
		for (size_t i = 1; i <= N; ++i) {
			cout << digit[i] << ' ';
		}
		cout << '\n';
	} else {
		puts("NO");
	}
}
