#include <iostream>

using namespace std;

struct node {
    int key;
    unsigned int h;
    node * left;
    node * right;
    node * prev;
    node * next;
    node(int k): key(k), h(1), left(NULL), right(NULL), prev(NULL), next(NULL) { }
};

typedef node * tree;

tree root;

int get_h(tree v) {
    return v ? v -> h : 0;
}

int get_bal(tree v) {  // > 0 справа больше, < 0 слева больше
    return v ? get_h(v -> right) - get_h(v -> left) : 0;
}

void update_h(tree v) {
    v -> h = 1 + max(get_h(v -> left), get_h(v -> right));
}

tree rotate_right(tree p) {
    tree v = p -> left;
    p -> left = v -> right;
    v -> right = p;
    update_h(p);
    update_h(v);
    return v;
}

tree rotate_left(tree p) {
    tree v = p -> right;
    p -> right = v -> left;
    v -> left = p;
    update_h(p);
    update_h(v);
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

tree find(tree v, int val) {
    if (v == NULL || v -> key == val) {
        return v;
    }
    return val < v -> key ? find(v -> left, val) : find(v -> right, val);
}

int find_min(tree v) {
    return v -> left ? find_min(v -> left) : v -> key;
}

int find_max(tree v) {
    return v -> right ? find_max(v -> right) : v -> key;
}

void chain(tree l, tree r) {
    if (l != NULL)
        l -> next = r;
    if (r != NULL)
        r -> prev = l;
}

tree extract_min(tree v) {
    if (v -> left == NULL) {
        chain(v -> prev, v -> next);
        return v -> right;
    }
    // V isn't minimum
    v -> left = extract_min(v -> left);
    return balance(v);
}

tree extract_max(tree v) {
    if (v -> right == NULL) {
        chain(v -> prev, v -> next);
        return v -> right;
    }
    // V isn't maximum
    v -> right = extract_max(v -> right);
    return balance(v);
}

tree prev(tree v, tree p, char type, int val) {
    if (v == NULL) {
        if (p != NULL) {
            if (type == 'l') {  // V - left son of P
                return p -> prev;
            } else {  // V - right son of P
                return p;
            }
        }
        return NULL;
    }
    if (val > v -> key) {
        return prev(v -> right, v, 'r', val);
    } else if (val < v -> key) {
        return prev(v -> left, v, 'l', val);
    } else {
        return v -> prev;
    }
}

tree next(tree v, tree p, char type, int val) {
    if (v == NULL) {
        if (p != NULL) {
            if (type == 'l') {  // V - left son of P
                return p;
            } else {  // V - right son of P
                return p -> next;
            }
        }
        return NULL;
    }
    if (val > v -> key) {
        return next(v -> right, v, 'r', val);
    } else if (val < v -> key) {
        return next(v -> left, v, 'l', val);
    } else {
        return v -> next;
    }
}

tree insert(tree v, tree p, char type, int val) {
    if (v == NULL) {
        v = new node(val);
        if (p != NULL) {
            if (type == 'l') {  // V - left son of P
                chain(p -> prev, v);
                chain(v, p);
            } else {  // V - right son of P
                chain(v, p -> next);
                chain(p, v);
            }
        }
        return v;
    }
    if (val > v -> key) {
        v -> right = insert(v -> right, v, 'r', val);
    } else if (val < v -> key) {
        v -> left = insert(v -> left, v, 'l', val);
    }
    return balance(v);
}

tree remove(tree v, int val) {
    if (v == NULL) {
        return NULL;
    } else if (val < v -> key) {
        v -> left =  remove(v -> left, val);
    } else if (val > v -> key) {
        v -> right = remove(v -> right, val);
    } else {  // v.key = val
        if (v -> right == NULL) {
            chain(v -> prev, v -> next);
            return v -> left;
        }
        if (v -> left == NULL) {
            chain(v -> prev, v -> next);
            return v -> right;
        }
        v -> key = find_min(v -> right);
        v -> right = extract_min(v -> right);
    }
    return balance(v);
}

void log(tree v) {
    if (v == NULL)
        return;
    log(v -> left);
    cout << "KEY: ";
    cout << v -> key;
    cout << "   h = ";
    cout << (int)(v -> h);
    cout << "  prev = ";
    if (v -> prev == NULL)
        cout << "none";
    else
        cout << v -> prev -> key;
    cout << "  next = ";
    if (v -> next == NULL)
        cout << "none";
    else
        cout << v -> next -> key;
    cout << "\n";
    log(v -> right);
}

int main() {
    root = NULL;
    string command;
    while (cin >> command) {
        int x;
        cin >> x;
        if (command == "insert") {
            root = insert(root, NULL, '-', x);
        } else if (command == "delete") {
            root = remove(root, x);
        } else if (command == "exists") {
            if (find(root, x) != nullptr) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (command == "next") {
            tree v = next(root, NULL, '-', x);
            if (v == NULL)
                cout << "none\n";
            else
                cout << v -> key << "\n";
        } else if (command == "prev") {
            tree v = prev(root, NULL, '-', x);
            if (v == NULL)
                cout << "none\n";
            else
                cout << v -> key << "\n";
        }
        // log(root);
    }
    return 0;
}
