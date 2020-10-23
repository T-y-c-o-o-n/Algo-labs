#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 300009;

long long arr[MAX_N];
int p[MAX_N];

int find(int v) {
    if (p[v] == v)
        return v;
    return p[v] = find(p[v]);
}

int solve(int l, int r, long long q) {
    l = find(p[l]);
    if (l <= r) {
        arr[l] = q;
        p[l] = solve(l + 1, r, q);
    }
    return p[l];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<long long, pair<int, int> > > request;
    for (int i = 1; i <= n + 1; ++i) {
        p[i] = i;
        arr[i] = 0;
    }
    for (int j = 0; j < m; ++j) {
        pair<long long, pair<int, int> > temp;
        cin >> temp.second.first >> temp.second.second >> temp.first;
        request.push_back(temp);
    }
    sort(request.rbegin(), request.rend());
    for (int i = 0; i < (int)request.size(); ++i) {
        int l = request[i].second.first, r = request[i].second.second;
        long long q = request[i].first;
        p[l] = solve(l, r, q);
    }
    for (int i = 1; i <= n; ++i)
        cout << arr[i] << " ";
}
