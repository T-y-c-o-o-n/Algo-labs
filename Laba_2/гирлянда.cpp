#include <iostream>
#include <iomanip>

using namespace std;

double b_search(double h[], int n) {
    double l = 0;
    double r = h[1];
    for (int k = 0; k < 100; ++k) {
        h[2] = (l + r) / (double)2;
        bool f = true;
        for (int i = 3; i <= n; ++i) {
            h[i] = (double)2 * h[i-1] - h[i-2] + (double)2;
            if (h[i] <= (double)0)
                f = false;
        }
        if (f)
            r = h[2];
        else
            l = h[2];
    }
    return h[2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    double h[1009];
    cin >> h[1];
    h[2] = b_search(h, n);
    for (int i = 3; i <= n; ++i) {
        h[i] = (double)2 * h[i-1] - h[i-2] + (double)2;
    }
    cout << setprecision(2) << fixed << h[n];
}
