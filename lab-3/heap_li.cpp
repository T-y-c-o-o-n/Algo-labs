#include <iostream>

using namespace std;

int main() {
    string ans = "YES";
    int n;
    cin >> n;
    int a[100001];
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if ((2*i <= n && a[i] > a[2*i]) || (2*i+1 <= n && a[i] > a[2*i+1]))
            ans = "NO";
    }
    cout << ans;
}
