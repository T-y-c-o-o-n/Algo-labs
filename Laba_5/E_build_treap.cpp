#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    int x;
    int y;
    int link;
    node * par;
    node * left;
    node * right;
    node(int x, int y, int link): x(x), y(y),
        link(link), par(nullptr), left(nullptr), right(nullptr) { }
};

typedef node* tree;

tree root, temp_node;

vector <pair <int, pair<int, int> > > arr;
pair <int, pair<int, int> > ans[300009];

void build(int x, int y, int link) {
    tree new_node = new node(x, y, link);
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
            return;
        }
    }
    new_node->left = temp_node->right;
    new_node->par = temp_node;
    temp_node->right = new_node;
    if (new_node->left)
        new_node->left->par = new_node;
    temp_node = new_node;
}

int get_link(tree v) {
    return v ? v->link : 0;
}

void print(tree v) {
    if (v) {
        print(v->left);
        ans[v->link].first = get_link(v->par);
        ans[v->link].second.first = get_link(v->left);
        ans[v->link].second.second = get_link(v->right);
        print(v->right);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        arr[i].first = x;
        arr[i].second.first = y;
        arr[i].second.second = i + 1;
    }
    sort(arr.begin(), arr.end());
    root = nullptr;
    temp_node = root;
    for (int i = 0; i < n; ++i) {
        build(arr[i].first, arr[i].second.first, arr[i].second.second);
    }
    print(root);
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        cout << ans[i].first << " " << ans[i].second.first << " " << ans[i].second.second << "\n";
    }
    return 0;
}
