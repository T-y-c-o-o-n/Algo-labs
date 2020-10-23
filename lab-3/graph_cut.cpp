#include <iostream>
#include <stack>

using namespace std;

int p[50009], rang[50009];

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
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
    }
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    stack<pair<string, pair<int, int> > > request;
    for (int i = 0; i < k; ++i) {
        pair<string, pair<int, int> > temp;
        cin >> temp.first >> temp.second.first >> temp.second.second;
        request.push(temp);
    }
    stack<string> ans;
    while (!request.empty()) {
        pair<string, pair<int, int> > temp = request.top();
        request.pop();
        string type = temp.first;
        int v = temp.second.first, u = temp.second.second;
        if (type == "cut") {
            unite(u, v);
        }
        if (type == "ask") {
            if (find(u) == find(v))
                ans.push("YES");
            else
                ans.push("NO");
        }
    }
    while (!ans.empty()) {
        cout << ans.top() << '\n';
        ans.pop();
    }
}
