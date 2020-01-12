/*#include <iostream>

using namespace std;

int n;
bool used[23];
int a[23], b[23], c[23], par[23];

int dfs(int v, int p, int temp, int cnt) {
    for (int u = 0; u < n; ++u) {
        if (u == v || u == p || used[u])
            continue;
        if (a[u] <= temp + c[v] && temp + c[v] <= b[u]) {
            int res = dfs(u, v, temp + c[v], cnt + 1);
            if (res > cnt)
                res--;
        }

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        par[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        int res = 0;
        if (a[i] <= k && k <= b[i])
            res = dfs(i, -1, k, 1);
    }
}
*/
