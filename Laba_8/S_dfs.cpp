//
// Created by tycoon on 03.10.2020.
//
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::reverse;
using std::stack;

typedef uint64_t v_t;

#define to_sz(v) static_cast<size_t>(v)
#define to_v(sz) static_cast<v_t>(sz)
#define all_v v_t v = 1; v <= n; ++v

size_t n;
vector<v_t> parent;
vector<vector<v_t> > children;
vector<bool> used;
vector<pair<v_t, v_t> > edges;

void my_dfs(v_t v, vector<v_t> &ancestors) {
	used[to_sz(v)] = true;
	for (size_t i = 0; i + 1 < ancestors.size(); ++i) {
		v_t ancestor = ancestors[i];
		if (v > ancestors[i + 1]) {
			edges.emplace_back(v, ancestor);
		}
	}
	if (!ancestors.empty()) {
		edges.emplace_back(v, ancestors.back());
	}

	ancestors.push_back(v);
	for (v_t child : children[to_sz(v)]) {
		my_dfs(child, ancestors);
	}
	ancestors.pop_back();
}

int main() {
	size_t l;
	cin >> n >> l;

	parent.resize(n + 1);
	children.resize(n + 1);
	vector<v_t> stack;
	for (size_t i = 0; i < l; ++i) {
		v_t v;
		cin >> v;
		if (stack.size() >= 2 && stack[stack.size() - 2] == v) {
			parent[to_sz(stack.back())] = v;
			children[to_sz(v)].push_back(stack.back());
			stack.pop_back();
		} else {
			stack.push_back(v);
		}
	}
	used.resize(n + 1, false);
	vector<v_t> ancestors;
	for (all_v) {
		if (!used[to_sz(v)]) {
			my_dfs(v, ancestors);
		}
	}
	cout << edges.size() << '\n';
	for (auto &vu : edges) {
		cout << vu.first << ' ' << vu.second << '\n';
	}
}
