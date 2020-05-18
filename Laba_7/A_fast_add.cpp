//
// Created by tycoon on 18.05.2020.
//
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <utility>

uint32_t a, b;
uint32_t cur = 0;
uint32_t next_rand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    size_t const n = (1 << 24);;
    size_t m, q;
    std::cin >> m >> q;
    std::cin >> a >> b;

    static uint32_t arr[n + 8];  // HERE

    for (size_t i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    for (size_t k = 0; k < m; ++k) {
        int add = next_rand();
        size_t l = next_rand(), r = next_rand();
        if (r < l) std::swap(l, r);
        arr[l] += add;
        arr[r + 1] -= add;
    }
    for (size_t i = 1; i < n; ++i) {
        arr[i] += arr[i - 1];
    }
    for (size_t i = 1; i < n; ++i) {
        arr[i] += arr[i - 1];
    }
    uint32_t ans = 0;
    for (size_t k = 0; k < q; ++k) {
        size_t l = next_rand(), r = next_rand();
        if (r < l) {
            std::swap(l, r);
        }
        int32_t res = arr[r];
        if (l > 0) {
            res -= arr[l - 1];
        }
        ans += res;
    }
    std::cout << ans << '\n';
    return 0;
}
