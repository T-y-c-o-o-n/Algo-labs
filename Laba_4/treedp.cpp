#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > E;
long long f[300009];
long long h[300009];
long long g[300009];
long long cnt[300009];

void dfs(int V, int P) {
    f[V] = 0;
    g[V] = 0;
    f[V] = 0;
    cnt[V] = 1;
    for (int U : E[V]) {
        if (U == P)
            continue;
        dfs(U, V);
        f[V] += f[U];
        g[V] += g[U] + cnt[U];
        cnt[V] += cnt[U];
    }/*
    for (int X : E[V]) {
        for (int Y : E[V]) {
            if (X == P || Y == P || X == Y)
                continue;
            h[V] += g[X] * cnt[Y] + cnt[X] * g[Y] + 2 * cnt[X] * cnt[Y];
        }
    }
    h[V] /= 2;*/
    for (int j = 1; j < E[V].size(); ++j) {
        if (E[V][j] == P)
            continue;
        for (int i = 0; i < j; i++) {
            if (E[V][i] == P)
                continue;
            int X = E[V][i];
            int Y = E[V][j];
            h[V] += g[X] * cnt[Y] + cnt[X] * g[Y] + 2 * cnt[X] * cnt[Y];
        }
    }
    f[V] += g[V] + h[V];
    // cout << V << " " << f[V] << " " << g[V] << " " << h[V] << " " << cnt[V] << "\n";
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    E.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        E[v].push_back(u);
        E[u].push_back(v);
    }
    dfs(1, -1);
    cout << f[1];
}
