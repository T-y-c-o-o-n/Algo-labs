#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string p, t;
    cin >> p >> t;

    vector<int> positions;
    for (int i = 0; i < (int) t.length() - (int) p.length() + 1; ++i) {
        if (t.substr(i, p.length()) == p) {
            positions.push_back(i);
        }
    }

    cout << positions.size() << '\n';
    for (int pos : positions) {
        cout << (pos + 1) << ' ';
    }
    cout << '\n';

    return 0;
}
