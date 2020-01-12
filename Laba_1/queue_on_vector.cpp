#include <iostream>
#include <stdlib.h>

using namespace std;

int c = 1, s = 0, cnt;
int *pnt = (int *)malloc(c*sizeof(int));

void resize(int ns) {
    int *a = (int *) malloc(ns * sizeof(int));
    for (int i = 0; i < min(s, ns); i++)
        a[i] = pnt[i];
    pnt = a;
}

void push(int val) {
    s++;
    if (s > c) {
        c *= 2;
        resize(c);
    }
    *(pnt + s - 1) = val;
}

int pop() {
    cnt++;
    return *(pnt + cnt - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        char op;
        cin >> op;
        if (op == '+') {
            int val;
            cin >> val;
            push(val);
        }
        if (op == '-') {
            cout << pop() << '\n';
        }
    }
    return 0;
}
