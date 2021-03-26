#include <iostream>
#include <string>
#include <vector>

using namespace std;

int P;
int MOD_COUNT;
vector<int64_t> MOD;
vector<vector<int>> deg;

void calc_pref_hash(string &str, vector<vector<int>> &pref_hash) {
    pref_hash.assign(str.length() + 1, vector<int>(MOD_COUNT));
    for (int no = 0; no < MOD_COUNT; ++no) {  // hash number
        pref_hash[0][no] = 0;
        for (int i = 0; i < (int) str.length(); ++i) {
            pref_hash[i + 1][no] = (int) ((pref_hash[i][no] * 1ll * P
                                           + (str[i] - 'a') * 1ll) % MOD[no]);
        }
    }
}

int get_hash(int no, int l, int r, vector<vector<int>> &pref_hash) {
    int res = (int) ((pref_hash[r + 1][no] * 1ll
                      - pref_hash[l][no] * 1ll * deg[r - l + 1][no]) % MOD[no]);
    if (res < 0) {
        res += (int) MOD[no];
    }
    return res;
}

bool cmp_hashes(int l_1, int r_1, int l_2, int r_2,
                vector<vector<int>> &pref_hash_1, vector<vector<int>> &pref_hash_2) {
    for (int no = 0; no < MOD_COUNT; ++no) {
        if (get_hash(no, l_1, r_1, pref_hash_1) != get_hash(no, l_2, r_2, pref_hash_2)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string template_str, str;
    cin >> template_str >> str;
    int len = (int) str.length();

    if (str.length() < template_str.length()) {
        return cout << 0 << '\n', 0;
    }

    P = 1007;
    MOD_COUNT = 2;
    MOD.resize(MOD_COUNT);
    MOD[0] = (int64_t) 1e9 + 7;
    MOD[1] = (int64_t) 1e9 + 37;

    deg.assign(len + 1, vector<int>(MOD_COUNT));
    deg[0][0] = deg[0][1] = 1;
    for (int no = 0; no < MOD_COUNT; ++no) {  // hash number
        deg[0][no] = 1;
        for (int i = 0; i < len; ++i) {
            deg[i + 1][no] = (int) ((deg[i][no] * 1ll * P) % MOD[no]);
        }
    }

    vector<vector<int>> str_pref_hash;
    vector<vector<int>> template_pref_hash;

    calc_pref_hash(template_str, template_pref_hash);
    calc_pref_hash(str, str_pref_hash);

    vector<int> positions;
    for (int pos = 0; pos + (int) template_str.length() <= (int) str.length(); ++pos) {
        int eq_pr_len;

        {
            int l = -1, r = template_str.length();
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (cmp_hashes(0, m, pos, pos + m, template_pref_hash, str_pref_hash)) {
                    l = m;
                } else {
                    r = m;
                }
            }
            eq_pr_len = l + 1;
        }

        if (eq_pr_len == (int) template_str.length()) {
            positions.push_back(pos);
            continue;
        }
        if (eq_pr_len + 1 == (int) template_str.length()) {
            positions.push_back(pos);
            continue;
        }

        if (cmp_hashes(eq_pr_len + 1, (int) template_str.length() - 1,
                       pos + eq_pr_len + 1, pos + (int) template_str.length() - 1,
                       template_pref_hash, str_pref_hash)) {
            positions.push_back(pos);
        }
    }

    cout << positions.size() << '\n';
    for (int pos : positions) {
        cout << (pos + 1) << ' ';
    }
    cout << '\n';

    return 0;
}
