#include <iostream>

using namespace std;

const int MAX_N = 1009, MAX_M = 1009;

int cnt[MAX_M][(int)'z'+1], pnt_l[MAX_M][(int)'z'+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    int i, j, c;
    cin >> n >> m >> k;
    string s[2][MAX_N];
    for (i = 0; i < n; ++i) {
        cin >> s[0][i];
        s[1][i] = s[0][i];
        for (j = 0; j < m; ++j)
            cnt[j][(int)s[0][i][j]]++;
    }
    for (j = 0; j < m; ++j) {
        pnt_l[j][(int)'a'] = 0;
        for (c = (int)'b'; c <= (int)'z'; c++)
            pnt_l[j][c] = pnt_l[j][c-1] + cnt[j][c-1];
    }
    for (j = m - 1; j >= m - k; j--) {
        int t = j % 2;
        for (i = 0; i < n; ++i) {
            char cc = s[1-t][i][j];
            s[t][pnt_l[j][(int)cc]] = s[1-t][i];
            pnt_l[j][(int)cc]++;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << s[(j+1)%2][i] << '\n';
    }
}
