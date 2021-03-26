#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void calculate_prefix_function(string &str, vector<int> &pi_str) {
    pi_str.assign(str.length(), 0);

    pi_str[0] = 0;
    for (size_t i = 1; i < pi_str.size(); ++i) {
        int k = pi_str[i - 1];
        while (k > 0 && str[k] != str[i]) {
            k = pi_str[k - 1];
        }
        if (str[k] == str[i]) {
            k++;
        }
        pi_str[i] = k;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;
    int n = (int) str.length();

    vector<vector<int>> substr_cnt(n, vector<int> (n, 0));
    string temp_str, reversed_temp_str;

//    for (int i = 0; i < n; ++i) {
//        substr_cnt[i][i] = 1;
//    }
    substr_cnt[0][0] = 1;
    temp_str += str[0];
    for (int i = 1; i < n; ++i) {
        temp_str += str[i];
        reversed_temp_str = temp_str;
        reverse(reversed_temp_str.begin(), reversed_temp_str.end());

        vector<int> pi_temp_reversed_str;
        calculate_prefix_function(reversed_temp_str, pi_temp_reversed_str);

        int max_val = 0;
        for (int j = i; j >= 0; --j) {
            max_val = max(pi_temp_reversed_str[i - j], max_val);
            substr_cnt[j][i] = substr_cnt[j][i - 1] + (i - j + 1 - min(max_val, i - j + 1));
        }
    }

    int query_cnt;
    cin >> query_cnt;
    for (int i = 0; i < query_cnt; ++i) {
        int l, r;
        cin >> l >> r;
        cout << substr_cnt[l - 1][r - 1] << '\n';
    }

    return 0;
}
