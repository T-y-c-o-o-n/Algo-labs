#include <iostream>

using namespace std;

struct node {
    int val;
    node* prev;
    node* next;
    node(int v, node * p, node * q) : val(v), prev(p), next(q) { }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int M;
    cin >> M;
    node* last = new node(-1, NULL, NULL);
    node* first = new node(-1, NULL, NULL);
    last -> next = first;
    first -> prev = last;
    while (M--) {
        char c;
        cin >> c;
        if (c == '+') {
            int val;
            cin >> val;
            node* a = new node(val, last, last -> next);
            last -> next -> prev = a;
            last -> next = a;
        }
        if (c == '-') {
            cout << first -> prev -> val << "\n";
            // delete first -> prev;
            first -> prev -> prev -> next = first;
            first -> prev = first -> prev -> prev;
        }
    }
}
