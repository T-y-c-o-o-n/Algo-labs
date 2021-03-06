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

    int n;
    cin >> n;
    vector<string> templates(n);
    for (int ind = 0; ind < n; ++ind) {
        cin >> templates[ind];
    }

    string t;
    cin >> t;

    vector<int> MOD(2);
    MOD[0] = 1000000007;
    MOD[1] = 1000000037;
    int p = 1007;
    int len = (int) t.length();
    vector<vector<int>> deg(1000009, vector<int>(2));
    deg[0][0] = deg[0][1] = 1;
    for (int i = 1; i < 1000009; ++i) {
        for (int j = 0; j < 2; ++j) {
            deg[i][j] = (int) ((deg[i - 1][j] * 1ll * p) % MOD[j]);
        }
    }
    vector<vector<int>> pref_hash(len, vector<int>(2));
    pref_hash[0][0] = pref_hash[0][1] = (t[0] - 'a');
    for (int i = 1; i < len; ++i) {
        for (int j = 0; j < 2; ++j) {
            pref_hash[i][j] = (int) ((pref_hash[i - 1][j]
                                      + deg[i][j] * 1ll * (t[i] - 'a')) % MOD[j]);
        }
    }


    vector<vector<int>> template_hashes(n, vector<int>(2));
    for (int ind = 0; ind < (int) templates.size(); ++ind) {
        string s = templates[ind];
        template_hashes[ind][0] = template_hashes[ind][1] = (s[0] - 'a');
        for (int i = 1; i < (int) s.length(); ++i) {
            for (int j = 0; j < 2; ++j) {
                template_hashes[ind][j] = (int) ((template_hashes[ind][j]
                                                  + deg[i][j] * 1ll * (s[i] - 'a')) % MOD[j]);
            }
        }
        template_hashes[ind][0] = (int) ((template_hashes[ind][0]
                * 1ll * deg[t.length() - 1][0]) % MOD[0]);
        template_hashes[ind][1] = (int) ((template_hashes[ind][1]
                * 1ll * deg[t.length() - 1][1]) % MOD[1]);
    }


    for (int ind = 0; ind < n; ++ind) {
        bool match = false;
        for (int pos = 0; pos + (int) templates[ind].length() <= (int) t.length(); ++pos) {
            vector<int> substr_hashes(2);
            get_hash(pos, pos + (int) templates[ind].length() - 1, t.length(),
                     MOD, deg, pref_hash, substr_hashes);
            if (template_hashes[ind][0] == substr_hashes[0]
                && template_hashes[ind][1] == substr_hashes[1]) {
                match = true;
                break;
            }
        }
        if (match) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
