#include <iostream>
#include <queue>


using namespace std;

#define mod first
#define sum second

bool was[1100][1100];
string ans[1100][1100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int n;
    cin >> n;
    queue<pair<int, int> > q;
    pair<int, int> temp = make_pair(0, 0);
    q.push(temp);
    was[0][0] = true;
    ans[0][0] = "";
    while (!was[0][n]) {
        temp = q.front();
        q.pop();
        for (int k = 0 ; k < 10; ++k) {
            int new_mod = (10 * temp.mod + k) % n;
            int new_sum = temp.sum + k;
            if (new_sum > n)
                break;
            if (!was[new_mod][new_sum]) {
                char c = (char)((int)'0' + k);
                q.push(make_pair(new_mod, new_sum));
                was[new_mod][new_sum] = true;
                ans[new_mod][new_sum] = ans[temp.mod][temp.sum] + c;
            }
        }
    }
    cout << ans[0][n];
}
