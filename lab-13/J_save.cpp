#include <iostream>
#include <vector>
#include <set>
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
    int64_t substrings;
    int leafs;
    vector<int> distinct_prefix_substings;

    explicit suffix_tree(string const &str) : s(str.length()) {
        for (int i = 0; i < (int) str.length(); ++i) {
            s[i] = str[i] - 'a';
        }

        left = 0;
        right = 0;
        substrings = 0;
        leafs = 0;

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

            substrings += 1ll * leafs;
            cout << substrings << '\n';
//            distinct_prefix_substings.push_back(substrings);
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
                leafs++;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    suffix_tree tree(s);

//    for (int val)

//    set<string> substrings;
//    for (int pref = 1; pref < s.size(); ++pref) {
//        for (int beg =)
//    }


    return 0;
}
