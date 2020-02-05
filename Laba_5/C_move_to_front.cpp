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

tree root, temp_node;

int get_cnt(tree v) {
    return v ? v->cnt : 0;
}

void update_cnt(tree v) {
    if (v)
        v->cnt = 1 + get_cnt(v->left) + get_cnt(v->right);
}

/*void build(int key) {
    tree new_node = new node(key);
    if (!root) {
        root = new_node;
        temp_node = root;
        return;
    }
    while (temp_node != root && temp_node->y > y) {
        temp_node = temp_node->par;
    }
    if (temp_node == root) {
        if (root->y > y) {
            root->par = new_node;
            new_node->left = root;
            root = new_node;
            temp_node = root;
            update_cnt(root);
            return;
        }
    }
    new_node->left = temp_node->right;
    new_node->par = temp_node;
    temp_node->right = new_node;
    if (new_node->left)
        new_node->left->par = new_node;
    temp_node = new_node;
    update_cnt(new_node);
    while (new_node != nullptr) {
        update_cnt(new_node);
        new_node = new_node->par;
    }
}*/

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

pair<tree, tree> split(tree v, int val) {
    if (v == nullptr)
        return make_pair(nullptr, nullptr);
    if (get_cnt(v->left) >= val) {
        pair<tree, tree> ab = split(v->left, val);
        v->left = ab.second;
        update_cnt(v);
        ab.second = v;
        return ab;
    } else {
        pair<tree, tree> ab = split(v->right, val - get_cnt(v->left) - 1);
        v->right = ab.first;
        update_cnt(v);
        ab.first = v;
        return ab;
    }
}

tree move_to_front(tree v, int l, int r) {
    pair<tree, tree> ab = split(v, l - 1);
    tree a = ab.first;
    tree b = ab.second;
    pair<tree, tree> bc = split(b, r - l + 1);
    b = bc.first;
    tree c = bc.second;
    return merge(b, merge(a, c));
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
    for (int i = 1; i <= n; ++i) {
        root = merge(root, new node(i));
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        root = move_to_front(root, l, r);
    }
    print(root);
    return 0;
}
