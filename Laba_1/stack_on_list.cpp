#include <iostream>

using namespace std;

struct node {
    int val;
    node* prev;
    node(int v, node * p) : val(v), prev(p) { }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int M;
    cin >> M;
    node* last = new node(-1, NULL);
    while (M--) {
        char c;
        cin >> c;
        if (c == '+') {
            int val;
            cin >> val;
            node* a = new node(val, last -> prev);
            last -> prev = a;
        }
        if (c == '-') {
            cout << last -> prev -> val << "\n";
            last -> prev = last -> prev -> prev;
        }
    }
}
