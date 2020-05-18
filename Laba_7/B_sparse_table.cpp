//
// Created by tycoon on 18.05.2020.
//
#include <iostream>

using namespace std;

int n;
int a[100009];

int pow2[31], log2[100009];
int RMQ[100009][31];

void build_RMQ() {
  for (int l = 0; l < n; ++l) {
    RMQ[l][0] = a[l];
  }
  for (int k = 1; k <= log2[n] + 1; ++k) {
    for (int L = 0; L + pow2[k] <= n; ++L) {
      RMQ[L][k] = min(RMQ[L][k-1], RMQ[L+pow2[k-1]][k-1]);  // CHECK RMQ[L+pow2[k-1]][k-1]
    }
  }
}

int get_min(int u, int v) {
  int l = min(u, v) - 1, r = max(u, v);
  int k = log2[r - l];
  return min(RMQ[l][k], RMQ[r - pow2[k]][k]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int m;
  cin >> n >> m;
  cin >> a[0];
  // cout << a[0];
  for (int i = 1; i < n; ++i) {
    a[i] = (23 * a[i-1] + 21563) % 16714589;
  }

  pow2[0] = 1;  // степени двойки
  for (int i = 1; i < 31; ++i) {
    pow2[i] = pow2[i-1] * 2;
  }
  log2[0] = -1;
  log2[1] = 0;
  log2[2] = 1;
  int pnt = 2;  // логарифмы
  for (int i = 3; i < 100009; ++i) {
    if (pnt * 2 == i) {
      log2[i] = log2[i-1] + 1;
      pnt *= 2;
    } else {
      log2[i] = log2[i-1];
    }
  }

  build_RMQ();

  int u, v, res;
  cin >> u >> v;
  res = get_min(u, v);
  for (int i = 1; i < m; ++i) {
    u = ((17 * u + 751 + res + 2 * i) % n) + 1;
    v = ((13 * v + 593 + res + 5 * i) % n) + 1;
    res = get_min(u, v);
  }
  cout << u  << ' ' << v << ' ' << res;
}
