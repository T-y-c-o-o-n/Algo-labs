#include <iostream>
#include <vector>

using namespace std;

#define ll long long

vector<ll> cnt;
int crount = 0;

void msort(int l, int r) {
    if (r - l > 1) {
        vector<ll> b;
        int m = (r + l) / 2;
        msort(l, m);
        msort(m, r);
        int i = l, j = m;
        while (i < m || j < r) {
            if ((cnt[i] < cnt[j] || j == r) && i < m) {
                b.push_back(cnt[i]);
                i++;
            } else {
                b.push_back(cnt[j]);
                j++;
            }
        }
        for (i = l; i < r; ++i) {
            cnt[i] = b[i - l];
        }
    }
}

void reverse(int l, int r) {
    vector<ll> b;
    for (int i = l; i < r; ++i)
        b.push_back(cnt[r - i - 1]);
    for (int i = l; i < r; ++i)
        cnt[i] = b[i];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll m, n, p, ans_0 = (ll)2e11;
    cin >> m;
    vector<ll> a;
    vector<ll> b;
    vector<ll> t;
    for (int i = 0; i < m; ++i) {
        ll aa, bb, tt;
        cin >> aa >> bb >> tt;
        if (aa == 0) {
            ans_0 = min(ans_0, tt + bb);
        } else {
            a.push_back(aa);
            b.push_back(bb);
            t.push_back(tt);
            cnt.push_back(0);
        }
    }
    cin >> n >> p;
    if (p == 0)
        return cout << 0, 0;
    m = (ll)cnt.size();
    ll l = 0, r = (ll)3e10, ans;
    for (ll h = 0; h < 40; ++h) {
        ans = (l + r) / 2;
        for (int i = 0; i < m; ++i) {
            cnt[i] = max(1ll*0, (ans - t[i] - b[i]) / a[i]);
        }
        msort(0, (int)m);
        reverse(0, (int)m);
        ll sum = 0;
        for (int i = 0; i < min(n, m); ++i)
            sum += cnt[i];
        if (sum >= p)
            r = ans;
        else
            l = ans;
    }
    ans += 1;
    cout << min(ans_0, ans);
}
