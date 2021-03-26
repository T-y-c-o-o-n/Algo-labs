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
    string str;
    cin >> str;

    string temp_str, reversed_temp_str;
    int temp_substr_cnt = 0;
    for (char i : str) {
        temp_str += i;
        reversed_temp_str = temp_str;
        reverse(reversed_temp_str.begin(), reversed_temp_str.end());

        vector<int> pi_temp_str;
        calculate_prefix_function(reversed_temp_str, pi_temp_str);

        int max_val = 0;
        for (int val : pi_temp_str) {
            max_val = max(val, max_val);
        }

        temp_substr_cnt += ((int) reversed_temp_str.length() - max_val);
        cout << temp_substr_cnt << '\n';
    }



    return 0;
}
