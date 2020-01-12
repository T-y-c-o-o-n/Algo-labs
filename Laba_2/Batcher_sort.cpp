#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int> > > comps(12);

void sort_2_parts(int l, int r, int h) {
    for (int i = l; i <= (l+r)/2; ++i)
        comps[h].push_back(make_pair(i, r - (i-l)));
}

void sort_biton(int l, int r, int h) {
    if (r - l == 0)
        return;
    for (int i = l; i <= (l+r)/2; ++i)
        comps[h].push_back(make_pair(i, i + (r-l+1)/2));
    sort_biton(l, (l+r)/2, h + 1);
    sort_biton((l+r)/2+1, r, h + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, hh[5] = {0, 1, 2, 4, 7};
    cin >> n;
    if (n == 1)
        return cout << "1 0 0", 0;
    int pow_2[6], h, cnt = 1;
    pow_2[0] = 1;
    for (int i = 0; i < 5; ++i)
        pow_2[i] = 2 * pow_2[i-1];
    for (int i = 1; i < 5; ++i) {
        cnt *= 2;
        h = hh[i];
        int l = 1, r = 1 + cnt - 1;
        while (l <= 16) {
            sort_2_parts(l, r, h);
            sort_biton(l, (l+r)/2, h + 1);
            sort_biton((l+r)/2+1, r, h + 1);
            l += cnt;
            r += cnt;
        }
    }
    int m = 80, k = 10;
    for (int i = 1; i <= 10; ++i) {
        for (int j = 0; j < (int)comps[i].size();) {
            pair<int, int> p = comps[i][j];
            if (p.first > n || p.second > n) {
                comps[i].erase(comps[i].begin() + j);
                m--;
            } else {
                j++;
            }
            if (comps[i].size() == 0)
                k--;
        }
    }
    cout << n << " " << m << " " << k << "\n";
    for (int i = 1; i <= 10; ++i) {
        if (comps[i].size() != 0) {
            cout << comps[i].size() << " ";
            for (int j = 0; j < (int)comps[i].size(); ++j)
                cout << comps[i][j].first << " " << comps[i][j].second << " ";
            cout << "\n";
        }
    }
}
