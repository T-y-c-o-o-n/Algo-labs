#include <iostream>
#include <vector>

using namespace std;

int const sigma_size = 26;

int temp_id = 0;
struct Node {
    vector<int> go;
    Node() : go(sigma_size, -1) {}
};

void add_word(vector<Node> &bor, const string& str) {
    int temp_ind = 0;
    for (char ch : str) {
        int c = ch - 'a';
        if (bor[temp_ind].go[c] != -1) {
            temp_ind = bor[temp_ind].go[c];
        } else {
            temp_ind = bor[temp_ind].go[c] = (int) bor.size();
            bor.emplace_back();
        }
    }
}

void output_dfs(vector<Node> &bor, int v) {
    for (int i = 0; i < sigma_size; ++i) {
        int u = bor[v].go[i];
        if (u != -1) {
            cout << (v + 1) << ' ' << (u + 1) << ' ' << ((char) ('a' + i)) << '\n';
            output_dfs(bor, u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    vector<Node> bor(1);
    for (int i = 0; i < (int) str.length(); ++i) {
        add_word(bor, str.substr(i));
    }

    cout << bor.size() << ' ' << (bor.size() - 1) << '\n';
    output_dfs(bor, 0);

    return 0;
}
