#include <iostream>

using namespace std;

int p[300001];

int find(int v) {
    if (p[v] == v)
        return v;
    else
        return p[v] = find(p[v]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int place;
        cin >> place;
        place = find(place);
        cout << place << " ";
        if (place < n)
            p[place] = place + 1;
        else
            p[place] = 1;
    }
}
