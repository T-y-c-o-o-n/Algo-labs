#include <iostream>
#include <vector>

using namespace std;

#define v first.first
#define w first.second
#define t second.first
#define ind second.second

vector <pair <pair <int, int>, pair<double, int> > > a(100009);
vector <int> inds;

void msort1(int l, int r) {
    if (r - l > 1) {
        vector < pair<pair<int, int>, pair<double, int> > > b;
        int m = (r + l) / 2;
        msort1(l, m);
        msort1(m, r);
        int i = l, j = m;
        while (i < m || j < r) {
            if ((a[i].t < a[j].t || j == r) && i < m) {
                b.push_back(a[i]);
                i++;
            } else {
                b.push_back(a[j]);
                j++;
            }
        }
        for (i = l; i < r; ++i)
            a[i] = b[i - l];
    }
}

void msort2(int l, int r) {
    if (r - l > 1) {
        vector<int> c;
        int m = (r + l) / 2;
        msort2(l, m);
        msort2(m, r);
        int i = l, j = m;
        while (i < m || j < r) {
            if ((inds[i] < inds[j] || j == r) && i < m) {
                c.push_back(inds[i]);
                i++;
            } else {
                c.push_back(inds[j]);
                j++;
            }
        }
        for (i = l; i < r; ++i)
            inds[i] = c[i - l];
    }
}

int main() {  // K-Best
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].v >> a[i].w;
        a[i].ind = i + 1;
    }
    double l = 0, r = 10000009, ans;
    for (int h = 0; h < 42; ++h) {
        ans = (l + r) / 2;
        for (int i = 0; i < n; ++i)
            a[i].t = (double)a[i].v - (double)a[i].w * ans;
        msort1(0, n);
        double val_sum = 0, w_sum = 0;
        for (int i = n - k; i < n; ++i) {
            val_sum += (double)a[i].v;
            w_sum += (double)a[i].w;
        }
        if (val_sum / w_sum >= ans)
            l = ans;
        else
            r = ans;
    }
    for (int i = n - k; i < n; ++i)
        inds.push_back(a[i].ind);
    msort2(0, k);
    for (int i = 0; i < (int)inds.size(); ++i)
        cout << inds[i] << ' ';
}
