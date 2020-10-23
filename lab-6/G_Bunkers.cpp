#include <iostream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> E;  // список смежных вершин
vector<int> par;  // список родителей, обновляемый в dfs-е "find_far", нужен ток чтобы искать середину пути
int max_depth;  // максимальная глубина в dfs-е
int far;  // самая глубокая вершина в dfs-е

void find_far(int v, int p, int depth) {
    par[v] = p;
    if ((E[v].size() == 1 && E[v][0] == p) || E[v].empty()) {
        if (depth > max_depth) {
            max_depth = depth;
            far = v;
        }
        return;
    }
    for (int u : E[v]) {
        if (u != p) {
            find_far(u, v, depth + 1);
        }
    }
}

vector< vector<int> > classes;  // список уже изученных классов,
// причём в качестве уникального номера класса используется индекс в этом векторе
vector<int> my_class;  // класс вершинки
vector< vector<int> > kids;  // список классов детей

void cluster(int v, int p) {  // кластеризует вершину, основываясь на классах детей и уже имеющейся информации в classes
    for (int u : E[v]) {
        if (u != p) {
            cluster(u, v);
            kids[v].push_back(my_class[u]);
        }
    }
    if (!kids[v].empty()) {
        sort(kids[v].begin(), kids[v].end());
    }

    for (size_t id = 0; id < classes.size(); ++id) {
        if (kids[v].size() != classes[id].size()) {  // not equals
            continue;
        }
        bool equals = true;
        for (size_t j = 0; j < kids[v].size(); ++j) {
            if (kids[v][j] != classes[id][j]) {  // not equals
                equals = false;
                break;
            }
        }
        if (equals) {
            my_class[v] = id;
            return;
        }
    }
//     else need to give new class;
    classes.push_back(kids[v]);
    my_class[v] = static_cast<int>(classes.size() - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    E.resize(n + 1);
    par.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        E[v].push_back(u);
        E[u].push_back(v);
    }
//     найти самый длинный путь между двумя вершинами
    int l, r, distant;
    find_far(1, -1, 0);
    l = far;
    max_depth = 0;

    find_far(l, -1, 0);
    r = far;
    distant = max_depth;
//     если в нём нечётное количество рёбер, то false
    if (distant % 2 == 1) {
        return cout << "NO", 0;
    }
//     найти середину пути
    int mid = r;
    for (int i = 0; i < distant / 2; ++i) {
        mid = par[mid];
    }
    if (E[mid].size() != 2) {
        cout << "NO";
        return 0;
    }

    int root1 = E[mid][0], root2 = E[mid][1];

    // кластеризация деревьев
    my_class.resize(n + 1);
    kids.resize(n + 1);
    cluster(root1, mid);
    cluster(root2, mid);
    // проверка изоморфности
    if (my_class[root1] == my_class[root2]) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
