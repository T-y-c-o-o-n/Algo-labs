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
    int left, right;
    int64_t substrings;
    int leafs;

    explicit suffix_tree(vector<char> const &str) : s(str.size()) {
        for (int i = 0; i < (int) str.size(); ++i) {
            if (str[i] == '?') {
                s[i] = -1;
            } else {
                s[i] = str[i] - 'a';
            }
        }
        if (str[0] == '?') {
            s[0] = 0;
            cout << "a 1\n";
        }

        left = 0;
        right = 0;
        substrings = 0;
        leafs = 0;

        temp_node = root = new node(nullptr, 0, -1);
        root->suf_link = root;

        node *without_suf_link = nullptr;

        while (right < (int) s.size()) {
            bool output = false;
            if (s[right] == -1) {
                output = true;
                if (right - left < temp_node->depth) {  // on the edge;
                    s[right] = s[temp_node->start + right - left - temp_node->parent->depth];
                } else {
                    for (int letter = 0; letter < sigma_size; ++letter) {
                        if (temp_node->link[letter]) {
                            s[right] = letter;
                            break;
                        }
                    }
                }
            }

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


            substrings += 1ll * leafs;
            if (output) {
                cout << ((char) (s[right] + 'a')) << ' ' << substrings << '\n';
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

    int n;
    cin >> n;
    vector<char> s(n);
    for (char &ch : s) {
        cin >> ch;
    }
    suffix_tree tree(s);

//    for (int val)

//    set<string> substrings;
//    for (int pref = 1; pref < s.size(); ++pref) {
//        for (int beg =)
//    }


    return 0;
}
