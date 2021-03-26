#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int sigma_size = 26;

struct Node {
    vector<int> go;
    int suf;
    bool term;

    Node() : go(sigma_size, -1), suf(-1), term(false) {}
};

void add_word(vector<Node> &bor, string &str) {
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
    bor[temp_ind].term = true;
}

const int MOD = 10000;

struct matrix {
    vector<vector<int>> data;

    explicit matrix(size_t size) : data(size, vector<int>(size, 0)) {}

    matrix &operator=(matrix const &rhs) = default;

    vector<int> &operator[](size_t const index) {
        return data[index];
    }

    matrix &operator*=(matrix rhs) {
        for (size_t i = 0; i < data.size(); ++i) {
            vector<int> str(data.size());
            for (size_t j = 0; j < data.size(); ++j) {
                int val = 0;
                for (size_t k = 0; k < data.size(); ++k) {
                    val = (val + (data[i][k] * rhs.data[k][j]) % MOD) % MOD;
                }
                str[j] = val;
            }
            data[i] = str;
        }
        return *this;
    }
};

using v_t = int;

void build_suf_bor(vector<Node> &bor, matrix &adj_matrix, vector<bool> &deleted) {
    int root_ind = 0;
    int fake_root_ind = (int) bor.size();

    bor.emplace_back();
    bor[fake_root_ind].go.assign(sigma_size, root_ind);
    bor[root_ind].suf = fake_root_ind;

    adj_matrix = matrix(bor.size());
    deleted.assign(bor.size(), false);

    queue<int> queue;
    queue.push(root_ind);
    while (!queue.empty()) {
        int v_ind = queue.front();
        queue.pop();

        bool v_deleted = bor[v_ind].term || deleted[bor[v_ind].suf];
        deleted[v_ind] = v_deleted;

        for (int c = 0; c < (int) sigma_size; ++c) {
            if (bor[v_ind].go[c] != -1) {
                bor[bor[v_ind].go[c]].suf = bor[bor[v_ind].suf].go[c];
                queue.push(bor[v_ind].go[c]);
            } else {
                bor[v_ind].go[c] = bor[bor[v_ind].suf].go[c];
            }

            if (!v_deleted && !deleted[bor[v_ind].go[c]]) {
                adj_matrix[v_ind][bor[v_ind].go[c]] = (adj_matrix[v_ind][bor[v_ind].go[c]] + 1) % MOD;
            }
        }
    }
}

matrix matrix_bin_pow(matrix m, int deg) {
    matrix res(m.data.size());
    for (size_t i = 0; i < res.data.size(); ++i) {
        res.data[i][i] = 1;
    }

    while (deg > 0) {
        if (deg % 2 == 1) {
            res *= m;
            deg--;
        } else {
            m *= m;
            deg /= 2;
        }
    }

    return res;
}

int bin_pow(int a, int deg) {
    int res = 1;

    while (deg > 0) {
        if (deg % 2 == 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        deg /= 2;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int word_count;
    cin >> word_count;

    vector<string> templates(word_count);
    vector<Node> bor(1);
    for (int ind = 0; ind < word_count; ++ind) {
        cin >> templates[ind];
        add_word(bor, templates[ind]);
    }

    int len;
    cin >> len;

    vector<bool> deleted;
    matrix adj_matrix(bor.size());
    build_suf_bor(bor, adj_matrix, deleted);

    adj_matrix = matrix_bin_pow(adj_matrix, len);

    int ans = 0;
    for (v_t v = 0; v < (v_t) bor.size(); ++v) {
        if (!deleted[v]) {
            ans = (ans + adj_matrix[0][v]) % MOD;
        }
    }

    int all = bin_pow(26, len);

    int res = ((all) - ans) % MOD;
    if (res < 0) {
        res += MOD;
    }
    cout << res << '\n';

    return 0;
}
