#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    constexpr int64_t MOD = (int64_t) 1e9 + 7;

    size_t len;
    int sigma_size;
    cin >> len >> sigma_size;

    vector<int> pi_str(len);
    pi_str[0] = 0;
    for (size_t i = 1; i < len; ++i) {
        cin >> pi_str[i];
    }

    int ans = sigma_size;

    for (size_t i = 1; i < len; ++i) {
        if (pi_str[i] == 0) {
            int unique_chars = 0;
            int border = pi_str[i - 1];
            while (border != 0) {
                if (pi_str[border] == 0) {
                    unique_chars++;
                }
                border = pi_str[border - 1];
            }
            unique_chars++;
            ans = (int) ((ans * 1ll * (sigma_size - unique_chars)) % MOD);
        }
    }

    cout << ans << '\n';

    return 0;
}
