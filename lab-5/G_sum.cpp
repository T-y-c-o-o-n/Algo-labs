#include <iostream>

using namespace std;

struct node {
    long long key;
    long long sum;
    long long h;
    node * left;
    node * right;
    explicit node(long long k): key(k), sum(k), h(1ll), left(nullptr), right(nullptr) { }
};

typedef node * tree;

tree root;

long long get_sum(tree v) {
    return v ? v -> sum : 0;
}

long long get_h(tree v) {
    return v ? v -> h : 0;
}

long long get_bal(tree v) {  // > 0 справа больше, < 0 слева больше
    return v ? get_h(v -> right) - get_h(v -> left) : 0;
}

void update_sum(tree v) {
    if (v)
        v -> sum = v -> key + get_sum(v -> left) + get_sum(v -> right);
}

void update_h(tree v) {
    if (v)
        v -> h = 1ll + max(get_h(v -> left), get_h(v -> right));
}

tree rotate_right(tree p) {
    tree v = p -> left;
    p -> left = v -> right;
    v -> right = p;
    update_h(p);
    update_h(v);
    update_sum(p);
    update_sum(v);
    return v;
}

tree rotate_left(tree p) {
    tree v = p -> right;
    p -> right = v -> left;
    v -> left = p;
    update_h(p);
    update_h(v);
    update_sum(p);
    update_sum(v);
    return v;
}

tree big_rotate_right(tree g) {
    g -> left = rotate_left(g -> left);
    g = rotate_right(g);
    return g;
}

tree big_rotate_left(tree g) {
    g -> right = rotate_right(g -> right);
    g = rotate_left(g);
    return g;
}

tree balance(tree v) {
    update_h(v);
    update_sum(v);
    if (get_bal(v) == 2) {
        if (get_bal(v -> right) == -1) {
            v = big_rotate_left(v);
        } else {
            v = rotate_left(v);
        }
    } else if (get_bal(v) == -2) {
        if (get_bal(v -> left) == 1) {
            v = big_rotate_right(v);
        } else {
            v = rotate_right(v);
        }
    }
    return v;
}

tree insert(tree v, long long val) {
    if (v == nullptr) {
        v = new node(val);
        return v;
    }
    if (val > v -> key) {
        v -> right = insert(v -> right, val);
    } else if (val < v -> key) {
        v -> left = insert(v -> left, val);
    }
    return balance(v);
}

long long get_sum_L_R(long long L, long long R) {
    tree v = root;
    while (v != nullptr && (v -> key < L || R < v -> key)) {
        if (v -> key < L)
            v = v -> right;
        else
            v = v -> left;
    }
    if (!v)
        return 0;
    long long sum = v -> key;
    tree w = v -> left;
    while (w) {
        if (w -> key >= L) {
            sum += w -> key + get_sum(w -> right);
            w = w -> left;
        } else {
            w = w -> right;
        }
    }
    w = v -> right;
    while (w) {
        if (w -> key <= R) {
            sum += w -> key + get_sum(w -> left);
            w = w -> right;
        } else {
            w = w -> left;
        }
    }
    return sum;
}

void log(tree v) {
    if (!v)
        return;
    log(v -> left);
    cout << "KEY: ";
    cout << v -> key;
    cout << "  SUMMA: ";
    cout << v -> key;
    cout << "    h = ";
    cout << (long long)(v -> h);
    cout << "\n";
    log(v -> right);
}

int main() {
    root = nullptr;
    long long n;
    cin >> n;
    string type;
    bool need_to_decode = false;
    long long y = 0;
    for (long long i = 0; i < n; ++i) {
        cin >> type;
        if (type == "+") {
            long long x;
            cin >> x;
            if (need_to_decode) {
                x = (x + y) % (1ll * 1000000000);
            }
            root = insert(root, x);
            need_to_decode = false;
        }
        if (type == "?") {
            long long l, r;
            cin >> l >> r;
            y = get_sum_L_R(l, r);
            cout << y << "\n";
            need_to_decode = true;
        }
        // log(root);
    }
    return 0;
}
