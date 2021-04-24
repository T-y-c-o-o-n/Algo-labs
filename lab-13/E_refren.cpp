#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int dollar = 0;
int sigma_size;

struct node {
    node *parent;
    node *suf_link;
    vector<node *> link;
    int depth;
    int start;

    node(node *parent, int depth, int start)
            : parent(parent), suf_link(nullptr), link(sigma_size), depth(depth), start(start) {
        for (auto &val : link) {
            val = nullptr;
        }
    }

    ~node() {
        for (auto &val : link) {
            if (val) {
                delete (val);
            }
        }
    }
};

struct suffix_tree {

    vector<int> s;
    node *root;
    node *temp_node;
    int left, right;

    explicit suffix_tree(vector<int> &str) : s(str.size() + 1) {
        for (int i = 0; i < (int) str.size(); ++i) {
            s[i] = str[i];
        }
        s.back() = dollar;

        left = 0;
        right = 0;

        temp_node = root = new node(nullptr, 0, -1);
        root->suf_link = root;

        node *without_suf_link = nullptr;

        while (right < (int) s.size()) {
            while (left <= right) {
                bool created_new_node = go_down(right);

                if (without_suf_link != nullptr) {
                    without_suf_link->suf_link = temp_node->parent;
                    without_suf_link = nullptr;
                }

                if (!created_new_node) {
                    break;
                }

                temp_node = temp_node->parent;

                if (temp_node->suf_link == nullptr) {  // !!!!!!!!!!!!!!!!!
                    without_suf_link = temp_node;
                    temp_node = temp_node->parent;
                }
                temp_node = temp_node->suf_link;

                left++;
                while (temp_node->depth < right - left) {
                    go_down(left + temp_node->depth);
                }
            }

            right++;
        }
    }

    bool go_down(int r) {
        int letter = s[r];
        if (r - left < temp_node->depth) {  // on the edge;
            node *parent = temp_node->parent;
            int delta = r - left - parent->depth;
            int next_letter_on_edge = s[temp_node->start + delta];

            if (next_letter_on_edge != letter) {
                node *new_node = new node(temp_node->parent, r - left, temp_node->start);
                new_node->link[next_letter_on_edge] = temp_node;

                parent->link[s[temp_node->start]] = new_node;
                temp_node->parent = new_node;
                temp_node->start += delta;

                temp_node = new_node;
            }

        }

        if (r - left == temp_node->depth) {
            if (temp_node->link[letter] == nullptr) {
                node *new_leaf = new node(temp_node, s.size(), r);
                temp_node->link[s[r]] = new_leaf;
                temp_node = new_leaf;
                return true;
            } else {
                temp_node = temp_node->link[letter];
            }
        }
        return false;
    }

    ~suffix_tree() {
        delete (root);
    }
};

struct dfs_result {
    int64_t refren;
    int pos;
    int len;
    int suffices;

    dfs_result() : refren(0), pos(0), len(0), suffices(0) {}
};

dfs_result dfs(node *v, vector<int> &str, int parent_depth) {
    dfs_result res{};
    if (v->link[0]) {
        res.suffices = 1;
    }
    for (int letter = 1; letter < sigma_size; ++letter) {
        auto child = v->link[letter];
        if (child) {
            auto child_res = dfs(child, str, v->depth);
            if (res.refren < child_res.refren) {
                res.refren = child_res.refren;
                res.pos = child_res.pos;
                res.len = child_res.len;
            }
            res.suffices += child_res.suffices;
        }
    }
    int len;
    if (v->depth == (int) str.size() + 1) {
        int edge_len = (int) str.size() + 1 - v->start;
        int leaf_depth = parent_depth + edge_len - 1;
        len = leaf_depth;

        res.suffices++;
    } else {
        len = v->depth;
    }
    int64_t refren_here = len * 1ll * res.suffices;
    if (res.refren < refren_here) {
        res.refren = refren_here;
        res.pos = v->start - parent_depth;
        res.len = len;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n >> sigma_size;
    sigma_size++;
    vector<int> str(n);
    for (int &el : str) {
        cin >> el;
    }

    suffix_tree tree(str);
    auto res = dfs(tree.root, str, 0);
    cout << res.refren << '\n' << res.len << '\n';
    for (int i = res.pos; i < res.pos + res.len; ++i) {
        cout << str[i] << ' ';
    }
    cout << '\n';

    return 0;
}
/*
9 3
1 2 1 2 1 3 1 2 1
*/
