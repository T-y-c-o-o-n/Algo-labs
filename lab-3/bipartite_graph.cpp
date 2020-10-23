#include <iostream>

using namespace std;

const int MAX_N = 200000;
int p[MAX_N], cnt[MAX_N], rang[MAX_N];

int find(int v) {
    if (p[v] == v)
        return v;
    return find(p[v]);
}

int findCnt(int v, int tempCnt) {
    if (p[v] == v)
        return tempCnt + cnt[v];
    else
        return tempCnt + cnt[v] + findCnt(p[v], tempCnt);
}

void unite(int v, int u) {
    int cntV = findCnt(v, 0), cntU = findCnt(u, 0);
    v = find(v);
    u = find(u);
    if (rang[v] < rang[u]) {
        swap(v, u);
        swap(cntV, cntU);
    }
    p[u] = v;
    if (cntU % 2 == cntV % 2)
        cnt[u]++;
    cnt[u] -= cnt[v];
    if (rang[v] == rang[u])
        rang[v]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, shift = 0;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        cnt[i] = 0;
        rang[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int type, a, b;
        cin >> type >> a >> b;
        int v = (a + shift) % n;
        int u = (b + shift) % n;
        if (type == 0) {
            unite(v, u);
        }
        if (type == 1) {
            if (findCnt(v, 0) % 2 == findCnt(u, 0) % 2) {
                cout << "YES\n";
                shift = (shift + 1) % n;
            } else {
                cout << "NO\n";
            }
        }
    }
}
