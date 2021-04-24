#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sigma_size = 26;

struct node {
    node *parent;
    node *suf_link;
    node *link[sigma_size];
    int depth;
    int start;
    int no;

    node(node *parent, int depth, int start, int no)
            : parent(parent), suf_link(nullptr), depth(depth), start(start), no(no) {
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
    int vertices;

    explicit suffix_tree(string const &str) : s(str.length()) {
        for (int i = 0; i < (int) str.length(); ++i) {
            s[i] = str[i] - 'a';
        }

        left = 0;
        right = 0;

        temp_node = root = new node(nullptr, 0, -1, vertices = 1);
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
                node *new_node = new node(temp_node->parent, r - left, temp_node->start, ++vertices);
                new_node->link[next_letter_on_edge] = temp_node;

                parent->link[s[temp_node->start]] = new_node;
                temp_node->parent = new_node;
                temp_node->start += delta;

                temp_node = new_node;
            }

        }

        if (r - left == temp_node->depth) {
            if (temp_node->link[letter] == nullptr) {
                node *new_leaf = new node(temp_node, s.size(), r, ++vertices);
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

    friend ostream &operator<<(ostream &out, suffix_tree const &tree);
};

void dfs_output(node *vertex, vector<int> const &s) {
    for (auto child : vertex->link) {
        if (child) {
            cout << vertex->no << ' ' << child->no << ' ';
            int second;
            if (child->depth == (int) s.size()) {
                second = (int) s.size();
            } else {
                second = child->start + child->depth - vertex->depth;
            }
            cout << (child->start + 1) << ' ' << (second) << '\n';
            dfs_output(child, s);
        }
    }
}

ostream &operator<<(ostream &out, suffix_tree const &tree) {
    cout << tree.vertices << ' ' << (tree.vertices - 1) << '\n';
    tree.root->no = 1;
    dfs_output(tree.root, tree.s);
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    suffix_tree tree(s);
    cout << tree;

    return 0;
}
