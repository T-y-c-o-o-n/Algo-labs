#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int u_int;

u_int x[1000009], a, b, cur;
long long ans = 0;

u_int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void msort(int l, int r) {
    if (r - l > 1) {
        vector<int> b;
        int m = (r + l) / 2;
        msort(l, m);
        msort(m, r);
        int i = l, j = m;
        while (i < m || j < r) {
            if ((x[i] <= x[j] || j == r) && i < m) {
                b.push_back(x[i]);
                i++;
            } else {
                ans += 1ll * m - 1ll * i;  // ??????? ????????
                b.push_back(x[j]);
                j++;
            }
        }
        for (i = l; i < r; ++i)
            x[i] = b[i - l];
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    u_int m;
    cin >> n >> m >> a >> b;
    for (int i = 0; i < n; ++i)
        x[i] = nextRand24() % m;
    msort(0, n);
    cout << ans;
}
