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

int main() {
    string p, t;
    cin >> p >> t;

    string str = p + "#" + t;

    vector<int> pi_str;
    calculate_prefix_function(str, pi_str);

    vector<int> positions;
    for (int i = p.length(); i < (int) pi_str.size(); ++i) {
        if (pi_str[i] == (int) p.length()) {
            positions.push_back(i - 2 * p.length());
        }
    }

    cout << positions.size() << '\n';
    for (int pos : positions) {
        cout << (pos + 1) << ' ';
    }
    cout << '\n';

    return 0;
}
