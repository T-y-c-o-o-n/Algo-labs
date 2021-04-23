#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int dollar = 0;

void simple_suffix_array(vector<int> &str, vector<int> &suffix_array, int sigma_size) {
    str.push_back(dollar);
    int n = (int) str.size();

    vector<int> classes(n);
    for (int i = 0; i < n; ++i) {
        classes[i] = str[i];
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<int> ptr(sigma_size, -1);

    vector<pair<int, int>> temp(n);
    int k = 0;
    while (k < n) {
        for (int i = 0; i < n; ++i) {
            temp[i].first = classes[i];
            temp[i].second = classes[(i + k) % n];
        }

        if (k == 0) {
            vector<int> cnt(sigma_size, 0);
            for (int i = 0; i < n; ++i) {
                cnt[classes[i]]++;
            }

            ptr[0] = -1;
            for (int c = 1; c < sigma_size; ++c) {
                ptr[c] = ptr[c - 1] + cnt[c - 1];
            }
        }

        vector<int> new_p(n);

        for (int i = 0; i < n; ++i) {
            int bruh = (p[i] + n - k) % n;
            new_p[++ptr[classes[bruh]]] = bruh;
        }

        for (int i = 0; i < n; ++i) {
            p[i] = new_p[i];
        }

        ptr.assign(n, -1);
        ptr[0] = -1;

        sigma_size = classes[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (temp[p[i]] == temp[p[i - 1]]) {

                classes[p[i]] = classes[p[i - 1]];
            } else {
                classes[p[i]] = classes[p[i - 1]] + 1;
                ptr[classes[p[i]]] = i - 1;
            }
        }
        sigma_size = classes[p.back()] + 1;

        if (sigma_size >= n) {
            break;
        }

        if (k == 0) {
            k = 1;
        } else {
            k *= 2;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        suffix_array[i] = p[i + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    vector<int> str;
    for (char ch : s) {
        str.emplace_back(ch - 'a' + 1);
    }

    vector<int> suffix_array(str.size());
    simple_suffix_array(str, suffix_array, 27);

    for (int suf : suffix_array) {
        cout << (suf + 1) << ' ';
    }
    cout << '\n';

    return 0;
}
