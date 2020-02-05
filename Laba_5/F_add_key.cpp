#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct node {
    int key;
    int cnt;
    node * par;
    node * left;
    node * right;
    node(int key): key(key),
                   cnt(1), par(nullptr), left(nullptr), right(nullptr) { }
};

typedef node* tree;
typedef pair<tree, tree> ptt;

tree root;
int p[300000];
int max_pos_of_null;

int get_cnt(tree v) {
    return v ? v->cnt : 0;
}

void update_cnt(tree v) {
    if (v)
        v->cnt = 1 + get_cnt(v->left) + get_cnt(v->right);
}

tree merge(tree a, tree b) {
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    if (rand() % (get_cnt(a) + get_cnt(b)) < get_cnt(a)) {
        a->right = merge(a->right, b);
        update_cnt(a);
        return a;
    } else {
        b->left = merge(a, b->left);
        update_cnt(b);
        return b;
    }
}

ptt split(tree v, int val) {
    if (v == nullptr)
        return make_pair(nullptr, nullptr);
    if (get_cnt(v->left) >= val) {
        ptt ab = split(v->left, val);
        v->left = ab.second;
        update_cnt(v);
        ab.second = v;
        return ab;
    } else {
        ptt ab = split(v->right, val - get_cnt(v->left) - 1);
        v->right = ab.first;
        update_cnt(v);
        ab.first = v;
        return ab;
    }
}

tree insert(tree v, int pos, int val) {
    ptt ab = split(v, pos - 1);
    return merge(merge(ab.first, new node(val)), ab.second);
}

tree remove(tree v, int pos) {
    ptt ab = split(v, pos - 1);
    ptt bc = split(ab.second, 1);
    return merge(ab.first, bc.second);
}

int find_null(int pos) {
    if (p[pos] == pos)
        return pos;
    return p[pos] = find_null(p[pos]);
}

tree add_key(tree v, int pos, int val) {
    int pos_null = find_null(pos);
    p[pos_null]++;
    max_pos_of_null = max(max_pos_of_null, p[pos_null]);
    v = remove(v, pos_null);
    return insert(v, pos, val);
}

void print(tree v) {
    if (v) {
        print(v->left);
        cout << v->key << " ";
        print(v->right);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    srand(time(0));
    for (int i = 1; i <= n + m; ++i) {
        root = merge(root, new node(0));
        p[i] = i;
    }
    max_pos_of_null = 1;
    int val = 0;
    while (n--) {
        int pos;
        cin >> pos;
        val++;
        root = add_key(root, pos, val);
    }
    // cout << max_pos_of_null;
    root = split(root, max_pos_of_null - 1).first;
    cout << max_pos_of_null - 1 << "\n";
    print(root);
    return 0;
}
