#include <iostream>

using namespace std;

int a[300001];

void msort(int l, int r) {
    if (r - l > 1) {
        int b[300001];
        int m = (r + l) / 2;
        msort(l, m);
        msort(m, r);
        int i = l, j = m, k = 0;
        while (i < m || j < r) {
            if ((a[i] < a[j] || j == r) && i < m) {
                b[k] = a[i];
                i++;
                k++;
            } else {
                b[k] = a[j];
                j++;
                k++;
            }
        }
        for (i = l; i < r; ++i)
            a[i] = b[i - l];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    msort(0, n);
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
}
