#include <iostream>
#include <string>
#include <vector>

using namespace std;

void get_hash(int l, int r, int len, vector<int> &MOD, vector<vector<int>> &deg,
              vector<vector<int>> &prev_hash, vector<int> &res) {
    for (int j = 0; j < 2; ++j) {
        res[j] = prev_hash[r][j];
        if (l > 0) {
            res[j] -= prev_hash[l - 1][j];
        }
        if (res[j] < 0) {
            res[j] += MOD[j];
        }
        res[j] = (int) ((res[j] * 1ll * deg[len - l - 1][j]) % MOD[j]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    vector<int> MOD(2);
    MOD[0] = 1000000007;
    MOD[1] = 1000000037;
    int p = 1007;
    int len = (int) str.length();
    vector<vector<int>> deg(len, vector<int> (2));
    deg[0][0] = deg[0][1] = 1;
    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < 2; ++j) {
            deg[i][j] = (int) ((deg[i - 1][j] * 1ll * p) % MOD[j]);
        }
    }
    vector<vector<int>> pref_hash(len, vector<int> (2));
    pref_hash[0][0] = pref_hash[0][1] = (str[0] - 'a');
    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < 2; ++j) {
            pref_hash[i][j] = (int) ((pref_hash[i - 1][j]
                    + deg[i][j] * 1ll * (str[i] - 'a')) % MOD[j]);
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
        vector<int> hashes_1(2);
        vector<int> hashes_2(2);
        get_hash(l_1, r_1, len, MOD, deg, pref_hash, hashes_1);
        get_hash(l_2, r_2, len, MOD, deg, pref_hash, hashes_2);

        if (hashes_1[0] == hashes_2[0] && hashes_1[1] == hashes_2[1]) {
            if (str.substr(l_1, r_1 - l_1) == str.substr(l_2, r_2 - l_2)) {
                cout << "Yes\n";
                continue;
            }
        }
        cout << "No\n";
    }

    return 0;
}
