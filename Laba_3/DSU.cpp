#include <iostream>

using namespace std;

int p[300001], minim[300001], maxim[300001], rang[300001];

int find(int v) {
    if (p[v] == v)
        return v;
    else
        return p[v] = find(p[v]);
}

void unite(int v, int u) {
    v = find(v);
    u = find(u);
    if (v != u) {
        if (rang[v] < rang[u])
            swap(v, u);
        p[u] = v;
        rang[v] += rang[u];
        minim[v] = min(minim[v], minim[u]);
        maxim[v] = max(maxim[v], maxim[u]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        p[i] = minim[i] = maxim[i] = i;
        rang[i] = 1;
    }
    string type;
    while (cin >> type) {
        if (type == "union") {
            int v, u;
            cin >> v >> u;
            unite(u, v);
        }
        if (type == "get") {
            int v;
            cin >> v;
            v = find(v);
            cout << minim[v] << " " << maxim[v] << " " << rang[v] << "\n";
        }
    }
}
