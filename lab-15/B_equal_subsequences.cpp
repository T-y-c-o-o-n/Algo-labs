#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void calculate_half(int n, string &str, int pos,
                    vector<char> &temp_seq_1,
                    vector<char> &temp_seq_2,
                    map<vector<char>, int> &seqs,
                    int &cnt_equal,
                    bool need_to_reverse) {
    if (pos >= n) {
        bool is_prefix = true;
        int prefix_len = min(temp_seq_1.size(), temp_seq_2.size());
        for (int i = 0; i < prefix_len; ++i) {
            if (temp_seq_1[i] != temp_seq_2[i]) {
                is_prefix = false;
                break;
            }
        }

        if (is_prefix) {
            if (temp_seq_1.size() > temp_seq_2.size()) {
                vector<char> suffix;
                for (int i = prefix_len; i < (int) temp_seq_1.size(); ++i) {
                    suffix.push_back(temp_seq_1[i]);
                }

                if (need_to_reverse) {
                    reverse(suffix.begin(), suffix.end());
                }

                seqs[suffix]++;
            } else if (temp_seq_1.size() == temp_seq_2.size()) {
                cnt_equal++;
            }
        }

        return;
    }

    temp_seq_1.push_back(str[pos]);
    calculate_half(n, str, pos + 1, temp_seq_1, temp_seq_2, seqs, cnt_equal, need_to_reverse);
    temp_seq_1.pop_back();

    temp_seq_2.push_back(str[pos]);
    calculate_half(n, str, pos + 1, temp_seq_1, temp_seq_2, seqs, cnt_equal, need_to_reverse);
    temp_seq_2.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;
    int n = ((int) str.length()) / 2;

    vector<char> temp_seq_1, temp_seq_2;
    map<vector<char>, int> seqs_more_left, seqs_more_right;
    int cnt_equal_left = 0, cnt_equal_right = 0;

    string half_1 = str.substr(0, n);
    calculate_half(n, half_1, 0, temp_seq_1, temp_seq_2, seqs_more_left, cnt_equal_left, false);

    string half_2 = str.substr(n);
    reverse(half_2.begin(), half_2.end());
    calculate_half(n, half_2, 0, temp_seq_1, temp_seq_2, seqs_more_right, cnt_equal_right, true);

    int64_t ans = cnt_equal_left * 1ll * cnt_equal_right;
    for (auto &seq_to_cnt : seqs_more_left) {
        ans += 2 * seq_to_cnt.second * 1ll * seqs_more_right[seq_to_cnt.first];
    }
    cout << ans << '\n';

    return 0;
}
