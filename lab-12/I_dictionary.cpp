#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int const sigma = 26;

struct Node {
    vector<int> a;
    int suf;
    bool term;
    vector<int> str_ids;
    Node() : a(sigma, -1), suf(-1), term(false), str_ids(0) {}
};

void add_word(vector<Node> &bor, string &str, int str_id) {
    int temp_ind = 0;
    for (char ch : str) {
        int c = ch - 'a';
        if (bor[temp_ind].a[c] != -1) {
            temp_ind = bor[temp_ind].a[c];
        } else {
            temp_ind = bor[temp_ind].a[c] = (int) bor.size();
            bor.emplace_back();
        }
    }
    bor[temp_ind].term = true;
    bor[temp_ind].str_ids.push_back(str_id);
}

void build_suf_bor(vector<Node> &bor) {
    int root_ind = 0;
    int fake_root_ind = (int) bor.size();
    bor.emplace_back();
    bor[fake_root_ind].a.assign(sigma, root_ind);
    bor[root_ind].suf = fake_root_ind;

    queue<int> queue;
    queue.push(root_ind);
    while (!queue.empty()) {
        int v_ind = queue.front();
        queue.pop();

        for (int c = 0; c < sigma; ++c) {
            if (bor[v_ind].a[c] != -1) {
                bor[bor[v_ind].a[c]].suf = bor[bor[v_ind].suf].a[c];
                queue.push(bor[v_ind].a[c]);
            } else {
                bor[v_ind].a[c] = bor[bor[v_ind].suf].a[c];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    int n;
    cin >> n;
    vector<string> templates(n);

    vector<Node> bor(1);
    int root_ind = 0;
    for (int ind = 0; ind < n; ++ind) {
        cin >> templates[ind];
        add_word(bor, templates[ind], ind);
    }

    build_suf_bor(bor);

    vector<bool> was_str(n, false);
    int v_ind = root_ind;
    for (char ch : str) {
        int c = ch - 'a';
        v_ind = bor[v_ind].a[c];
        int u_ind = v_ind;
        while (u_ind != root_ind) {
            if (bor[u_ind].term) {
                for (int id : bor[u_ind].str_ids) {
                    was_str[id] = true;
                }
            }
            u_ind = bor[u_ind].suf;
        }
    }

    for (bool ans : was_str) {
        if (ans) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

    return 0;
}
