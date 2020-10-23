#include <iostream>
#include <stdlib.h>

using namespace std;

int n;
int a[100009];

int lower_bound(int x) {
    int l = 0, r = n + 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        if (a[m] < x)
            l = m;
        else
            r = m;
    }
    if (r <= n && a[r] == x)
        return r;
    else
        return -1;
}

int upper_bound(int x) {
    int l = 0, r = n + 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        if (a[m] > x)
            r = m;
        else
            l = m;
    }
    if (l > 0 && a[l] == x)
        return l;
    else
        return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int M;
    cin >> M;
    while (M--) {
        int b;
        cin >> b;
        cout << lower_bound(b) << " " << upper_bound(b) << '\n';
    }
    return 0;
}
