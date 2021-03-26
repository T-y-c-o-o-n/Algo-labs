#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_hash(int no, int l, int r, vector<int64_t> &MOD, vector<vector<int>> &deg,
             vector<vector<int>> &prev_hash) {
    int res = (int) ((prev_hash[r + 1][no] * 1ll
                      - prev_hash[l][no] * 1ll * deg[r - l + 1][no]) % MOD[no]);
    if (res < 0) {
        res += (int) MOD[no];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    vector<int64_t> MOD(2);
    MOD[0] = (int64_t) 1e9 + 7;
    MOD[1] = (int64_t) 1e9 + 37;
    int p = 1007;
    int len = (int) str.length();
    vector<vector<int>> deg(len + 1, vector<int>(2));
    vector<vector<int>> pref_hash(len + 1, vector<int>(2));
    deg[0][0] = deg[0][1] = 1;
    for (int no = 0; no < 2; ++no) {  // hash number
        deg[0][no] = 1;
        pref_hash[0][no] = 0;
        for (int i = 0; i < len; ++i) {
            deg[i + 1][no] = (int) ((deg[i][no] * 1ll * p) % MOD[no]);
            pref_hash[i + 1][no] = (int) ((pref_hash[i][no] * 1ll * p
                                           + (str[i] - 'a') * 1ll) % MOD[no]);
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int l_1, r_1, l_2, r_2;
        cin >> l_1 >> r_1 >> l_2 >> r_2;
        l_1--;
        r_1--;
        l_2--;
        r_2--;
        if (l_1 == l_2 && r_1 == r_2) {
            cout << "Yes\n";
            continue;
        }
        if (r_1 - l_1 != r_2 - l_2) {
            cout << "No\n";
            continue;
        }

        if (get_hash(0, l_1, r_1, MOD, deg, pref_hash)
            == get_hash(0, l_2, r_2, MOD, deg, pref_hash)
            && get_hash(1, l_1, r_1, MOD, deg, pref_hash)
               == get_hash(1, l_2, r_2, MOD, deg, pref_hash)) {
            cout << "Yes\n";
            continue;
        }
        cout << "No\n";
    }

    return 0;
}
