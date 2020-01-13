#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 200009;

int n, pL[MAX_N], pR[MAX_N], p[MAX_N];

int findL(int v) {
    if (pL[v] == v)
        return v;
    return pL[v] = findL(pL[v]);
}

int findR(int v) {
    if (pR[v] == v)
        return v;
    return pR[v] = findR(pR[v]);
}

int find(int v) {
    if (p[v] == v)
        return v;
    return p[v] = find(p[v]);
}

void join(int v, int u) {
    v = find(v);
    u = find(u);
    int l = min(v, u);
    int r = max(v, u);
    p[l] = r;
}

void unite(int l, int r) {
    l = findR(l);
    r = findL(r);
    if (l >= r)
        return;
    while (l < r) {
        l++;
        pL[l] = l - 1;
        pR[l - 1] = l;
        join(l-1, l);
        l = findR(l);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        pL[i] = pR[i] = p[i] = i;
    }
    for (int i = 0; i < q; ++i) {
        int type, v, u;
        cin >> type >> v >> u;
        if (type == 1) {
            join(v, u);
        }
        if (type == 2) {
            unite(v, u);
        }
        if (type == 3) {
            v = find(v);
            u = find(u);
            if (v == u)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}
