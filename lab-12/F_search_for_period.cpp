#include <iostream>
#include <string>
#include <vector>

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

void calculate_z_function(string &str, vector<int> &z_str) {
    z_str.assign(str.length(), 0);

    z_str[0] = 0;
    int temp_max_L = 0, temp_max_R = 0;
    for (int pos = 1; pos < (int) z_str.size(); ++pos) {
        z_str[pos] = 0;
        if (pos < temp_max_R) {
            z_str[pos] = min(z_str[pos - temp_max_L], temp_max_R - pos);
        }
        while (pos + z_str[pos] < (int) str.length() && str[z_str[pos]] == str[pos + z_str[pos]]) {
            z_str[pos]++;
        }
        if ((int) temp_max_R < pos + z_str[pos]) {
            temp_max_L = pos;
            temp_max_R = pos + z_str[pos];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    vector<int> pi_str;
    calculate_prefix_function(str, pi_str);

    int temp_border = pi_str[str.length() - 1];
    while (temp_border >= (int) (str.length() + 1) / 2) {
        if (str.length() % (str.length() - temp_border) == 0) {
            cout << str.length() - temp_border << '\n';
            return 0;
        }
        temp_border = pi_str[temp_border - 1];
    }

    cout << str.length() << '\n';

    return 0;
}
