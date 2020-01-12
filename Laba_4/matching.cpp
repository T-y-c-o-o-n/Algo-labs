/*#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;

int n;
long long f[200000], g[200000];  // f - ребро снизу, g - ребро нигде или сверху
// int G[100009][100009];
vector< vector< pair<int, int> > > E;

void dfs(int v, int p) {
    for (int i = 0; i < (int)E[v].size(); ++i) {
        int u = E[v][i].first;
        if (u != p)
            dfs(u, v);
    }
    f[v] = g[v] = 0;
    long long sum = 0;
    for (int i = 0; i < (int)E[v].size(); ++i) {
        int u = E[v][i].first;
        if (u != p)
            sum += max(f[u], g[u]);
    }
    g[v] = sum;
    for (int i = 0; i < (int)E[v].size(); ++i) {
        int u = E[v][i].first;
        if (u != p) {
            f[v] = max(((g[u] + E[v][i].second) + (sum - max(f[u], g[u]))) , f[v]);
        }
    }
    // cout << "p: " << p << "  v: " << v << "\n" << f[v] << " " << g[v] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    cin >> n;
    E.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        E[v].push_back(make_pair(u, w));
        E[u].push_back(make_pair(v, w));
        // G[v][u] = w;
        // G[u][v] = w;
        // G.insert(make_pair(v, u), w);
        // G.insert(make_pair(u, v), w);
    }
    dfs(1, -1);
    cout << max(f[1], g[1]);
}
*/
