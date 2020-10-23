#include <iostream>
#include <string>

using namespace std;

struct node {
    char val;
    node* prev;
    node(char v, node * p) : val(v), prev(p) { }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    while (cin >> s) {
        string ans = "YES";
        node *first = new node('-', NULL);
        node *last = new node('-', first);
        for (unsigned int i = 0; i < s.length(); ++i) {
            if (s[i] == '[' || s[i] == '(') {
                node *a = new node(s[i], last->prev);
                last->prev = a;
            }
            if (s[i] == ']') {
                if (last->prev->val == '[')
                    last->prev = last->prev->prev;
                else ans = "NO";
            }
            if (s[i] == ')') {
                if (last->prev->val == '(')
                    last->prev = last->prev->prev;
                else ans = "NO";
            }
        }
        if (last->prev != first)
            ans = "NO";
        cout << ans << "\n";
    }
}
