#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector <pair <int, int> > comp;
    for (int i = 0; i < k; i++) {
        int r;
        cin >> r;
        for (int j = 0; j < r; ++j) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            if (x > y) {
                x = x + y;
                y = x - y;
                x = x - y;
            }
            comp.push_back(make_pair(x, y));
        }
    }
    for (int x = 0; x < (1 << n); x++) {
        int a[20];
        for (int j = 0; j < n; ++j)
            a[j] = (x >> j) % 2;
        for (int j = 0; j < m; ++j) {
            int l = comp[j].first, r = comp[j].second;  // l > r
            if (a[l] > a[r]) {
                a[l] = a[l] + a[r];
                a[r] = a[l] - a[r];
                a[l] = a[l] - a[r];
            }
        }
        for (int j = 1; j < n; ++j)
            if (a[j - 1] > a[j])
                return cout << "No", 0;
    }
    cout << "Yes";
}
