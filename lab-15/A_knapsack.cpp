#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void calculate_sums(int64_t max_weight, int64_t taken_weight, size_t pos, vector<int> &x, vector<int64_t> &sums) {
    if (pos >= x.size()) {
        sums.push_back(taken_weight);
        return;
    }

    if (taken_weight + 1ll * x[pos] <= max_weight) {
        calculate_sums(max_weight, taken_weight + 1ll * x[pos], pos + 1, x, sums);
    }
    calculate_sums(max_weight, taken_weight, pos + 1, x, sums);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;
    vector<int> x1(n / 2);
    for (int &el : x1) {
        cin >> el;
    }
    vector<int> x2(n - n / 2);
    for (int &el : x2) {
        cin >> el;
    }
    int64_t max_weight;
    cin >> max_weight;

    vector<int64_t> sums_1, sums_2;
    calculate_sums(max_weight, 0, 0, x1, sums_1);
    calculate_sums(max_weight, 0, 0, x2, sums_2);
    sort(sums_1.begin(), sums_1.end());
    sort(sums_2.begin(), sums_2.end());

    int64_t ans = 0;
    for (int64_t sum_1 : sums_1) {
        ans += int64_t (lower_bound(sums_2.begin(), sums_2.end(),
                                    max_weight - sum_1 + 1) - sums_2.begin());
    }
    cout << ans << '\n';

    return 0;
}
