#include <iostream>

using namespace std;

const long long pow2_32 = 4294967296;
int par[500000], cnt[500000], read[500000], rang[500000];

int find(int v) {
    while (par[v] != v)
        v = par[v];
    return v;
}

void unite(int v, int u) {
    if (rang[v] < rang[u])
        swap(v, u);
    par[u] = v;
    cnt[u] -= cnt[v];
    if (rang[v] == rang[u])
        rang[v]++;
}

void send(int v) {
    v = find(v);
    cnt[v]++;
}

int toRead(int v) {
    int res = cnt[v] - read[v];
    int u = v;
    while(par[v] != v) {
        v = par[v];
        res += cnt[v];
    }
    read[u] += res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, zerg = 0, p = (int)1e6 + 3;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        par[i] = i;
        rang[i] = cnt[i] = read[i] = 0;
    }
    for (int h = 0; h < m; ++h) {
        int type, i, j;
        cin >> type;
        if (type == 1) {
            cin >> i;
            i = (i + zerg) % n;
            send(i);
            zerg = (30 * zerg + 239) % p;
        }
        if (type == 2) {
            cin >> i >> j;
            i = (i + zerg) % n;
            j = (j + zerg) % n;
            i = find(i);
            j = find(j);
            if (i != j) {
                unite(i, j);
                zerg = (13 * zerg + 11) % p;
            }
        }
        if (type == 3) {
            cin >> i;
            i = (i + zerg) % n;
            int q = toRead(i);
            cout << q << "\n";
            zerg = (int) ( (zerg*1ll*100500 + 1ll*q) % (1ll*p) );
        }
    }
}
