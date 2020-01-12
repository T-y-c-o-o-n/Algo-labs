#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int a[15];
    while (n != 0) {
        int first_1 = -1, cnt_1 = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i])
                cnt_1++;
            if (first_1 == -1 && a[i] == 1)
                first_1 = i;
        }
        bool is_sorted = true;
        for (int i = 1; i < n; ++i)
            if (a[i] > a[i+1])
                is_sorted = false;
        if (is_sorted) {
            cout << "-1\n";
            cin >> n;
            continue;
        }
        cout << cnt_1-1+(1+n-2)*(n-2) << '\n';
        for (int i = first_1 + 1; i <= n; ++i)  // part 1
            if (a[i] == 1)
                cout << first_1 << ' ' << i << '\n';
        for (int i = 1; i < n; ++i)  // part 2
            for (int j = i + 1; j <= n; ++j)
                if (i != first_1 && j != first_1)
                    cout << i << ' ' << j << '\n';
        for (int i = 1; i < n; ++i)  // part 2.1
            for (int j = i + 1; j <= n; ++j)
                if (i != n - cnt_1 + 1 && j != n - cnt_1 + 1)
                    cout << i << ' ' << j << '\n';
        cin >> n;
    }
}
