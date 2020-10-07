#include <iostream>

using namespace std;

int a[500], b[500];
int dp[500][500], G[500][500];

void answer(int l, int r) {
    if (l == r) {
        cout << 'A';
    } else {
        int m = G[l][r];
        if (l < m) {
            cout << '(';
            answer(l, m);
            cout << ')';
        } else {
            answer(l, m);
        }
 
        if ((m+1) < r) {
            cout << '(';
            answer(m+1, r);
            cout << ')';
        } else {
            answer(m+1, r);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout); 
 
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i] = 0;
        G[i][i] = i;
        dp[i][i+1] = a[i] * b[i] * b[i+1];
        G[i][i+1] = i;
    }
    dp[n-1][n-1] = 0;
    G[n-1][n-1] = n-1;
    for (int delta = 2; delta < n; delta++) {
        for (int i = 0; i + delta < n; ++i) {
            int j = i + delta;
            dp[i][j] = 2000000000;
            for (int R = i; R < j; ++R) {
                if (a[i] * b[R] * b[j] + dp[i][R] + dp[R+1][j] < dp[i][j]) {
                    G[i][j] = R;
                    dp[i][j] = a[i] * b[R] * b[j] + dp[i][R] + dp[R+1][j];
                }
            }
        }
    }
    if (n > 1)
        cout << '(';
    answer(0, n - 1);
    if (n > 1)
        cout << ')';
}

