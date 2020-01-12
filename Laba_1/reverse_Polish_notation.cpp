#include <iostream>
#include <string>

using namespace std;

struct node {
    int val;
    node *prev;
    node(int v, node *p) : val(v), prev(p) {}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    char c;
    node *bottom = new node(-1, NULL);
    node *top = new node(-1, bottom);
    while (cin >> c) {
        int q = -1;
        if (c == '0') q = 0;
        if (c == '1') q = 1;
        if (c == '2') q = 2;
        if (c == '3') q = 3;
        if (c == '4') q = 4;
        if (c == '5') q = 5;
        if (c == '6') q = 6;
        if (c == '7') q = 7;
        if (c == '8') q = 8;
        if (c == '9') {
            q = 9;
        }
        if (q >= 0 && q <= 9) {
            node *a = new node(q, top->prev);
            top->prev = a;
        } else {
            if (c == '+') {
                top->prev->prev->val = top->prev->prev->val + top->prev->val;
                top->prev = top->prev->prev;
            }
            if (c == '-') {
                top->prev->prev->val = top->prev->prev->val - top->prev->val;
                top->prev = top->prev->prev;
            }
            if (c == '*') {
                top->prev->prev->val = top->prev->prev->val * top->prev->val;
                top->prev = top->prev->prev;
            }
        }
    }
    cout << top->prev->val;
}
