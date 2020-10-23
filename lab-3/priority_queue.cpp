#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define val first
#define link second
#define ll long long
vector<pair<ll, int> > heap;
vector<int> pnt(1);

void swapAll(int v, int u) {
    swap(heap[v].val, heap[u].val);
    swap(heap[v].link, heap[u].link);
    swap(pnt[heap[v].link], pnt[heap[u].link]);
}

void siftUp(int v) {
    if (v == 0)
        return;
    while (heap[v] < heap[(v-1)/2]) {
        swapAll(v, (v-1)/2);
        v = (v - 1) / 2;
        if (v == 0)
            return;
    }
}

void siftDown(int v) {
    while (2 * v + 1 < (int)heap.size()) {
        int left = 2 * v + 1, right = 2 * v + 2;
        int u = left;
        if (right < (int)heap.size() && heap[right].val < heap[left].val)
            u = right;
        if (heap[v].val <= heap[u].val)
            return;
        swapAll(v, u);
        v = u;
    }
}

void push(ll val, int newLink) {
    heap.push_back(make_pair(val, newLink));
    pnt.push_back(heap.size()-1);
    siftUp(heap.size()-1);
}

void decreaseKey(int pos, ll newVal) {
    if (pnt[pos] == -1)
        return;
    heap[pnt[pos]].val = newVal;
    siftUp(pnt[pos]);
}

pair<ll, int> extractMin() {
    pair<ll, int> res = make_pair(heap[0].val, heap[0].link);
    swapAll(0, heap.size()-1);
    pnt[heap[heap.size()-1].link] = -1;
    heap.pop_back();
    siftDown(0);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string type;
    int counter = 0;
    while (cin >> type) {
        counter++;
        if (type == "push") {
            ll val;
            cin >> val;
            push(val, counter);
        }
        if (type == "decrease-key") {
            int pos;
            ll new_val;
            cin >> pos >> new_val;
            decreaseKey(pos, new_val);
            pnt.push_back(-1);
        }
        if (type == "extract-min") {
            if (heap.size() > 0) {
                pair<ll, int> res = extractMin();
                cout << res.val << " " << res.link << "\n";
            } else {
                cout << "*\n";
            }
            pnt.push_back(-1);
        }
    }
}
