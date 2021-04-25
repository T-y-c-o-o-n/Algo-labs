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

    node(node *parent, int depth, int start)
            : parent(parent), suf_link(nullptr), depth(depth), start(start) {
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
    node *without_suf_link;
    node *check_node;
    int left, right;
    int depth_for_check;

    suffix_tree() : s(0) {
        left = 0;
        right = 0;

        temp_node = root = new node(nullptr, 0, -1);
        root->suf_link = root;

        without_suf_link = nullptr;
        check_node = nullptr;
        depth_for_check = 0;
    }

    void add_string(string const &str) {
        for (char ch : str) {
            s.push_back(tolower(ch) - 'a');
        }

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
                node *new_leaf = new node(temp_node, INT32_MAX, r);
                temp_node->link[s[r]] = new_leaf;
                temp_node = new_leaf;
                return true;
            } else {
                temp_node = temp_node->link[letter];
            }
        }
        return false;
    }

    bool go_down_for_check(int letter) {
        if (depth_for_check < check_node->depth) {
            int index = check_node->start + depth_for_check
                        - check_node->parent->depth;
            if (index < (int) s.size() && s[index] == letter) {
                depth_for_check++;
                return true;
            }
        } else {
            if (check_node->link[letter] != nullptr) {
                depth_for_check++;
                check_node = check_node->link[letter];
                return true;
            }
        }

        return false;
    }

    bool check_string(string &str) {
        check_node = root;
        depth_for_check = 0;
        bool result = true;
        for (char i : str) {
            if (!go_down_for_check(tolower(i) - 'a')) {
                result = false;
                break;
            }
        }

        return result;
    }

    ~suffix_tree() {
        delete (root);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    suffix_tree tree;

    string cmd, arg;
    while (cin >> cmd) {
        cin >> arg;

        if (cmd == "A") {
            tree.add_string(arg);
        } else if (cmd == "?") {
            bool res = tree.check_string(arg);
            if (res) {
                puts("YES");
            } else {
                puts("NO");
            }
        }
    }

    return 0;
}
