#include <iostream>

using namespace std;

typedef long long ll;

const int CAP = 100005;
ll t[CAP*2]{};
ll d[CAP]{};
int n, m, h;

void calc(int p, int k) {
  if (d[p] == 0) t[p] = t[p << 1] + t[p << 1 | 1];
  else t[p] += d[p] * k;
}

void apply(int p, ll val, int k) {
  t[p] += val * k;
  if (p < n) d[p] += val;
}

void build(int l, int r) {
  int k = 2;
  for (l += n, r += n - 1; l > 1; k <<= 1) {
    l >>= 1, r >>= 1;
    for (int i = r; i >= l; --i) calc(i, k);
  }
}

void push(int l, int r) {
  int s = h, k = 1 << (h - 1);
  for (l += n, r += n - 1; s > 0; --s, k >>= 1)
    for (int i = l >> s; i <= r >> s; ++i)
      if (d[i] != 0) {
        apply(i << 1, d[i], k);
        apply(i << 1 | 1, d[i], k);
        d[i] = 0;
      }
}

void increment(int l, int r, ll val) {
  if (val == 0) return;
  push(l, l+1);
  push(r-1, r);
  bool cl = false, cr = false;
  int k = 1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (cl) calc(l-1, k);
    if (cr) calc(r, k);
    if (l & 1) apply(l++, val, k), cl = true;
    if (r & 1) apply(--r, val, k), cr = true;
  }
  for (--l; r > 0; l >>= 1, r >>= 1, k <<= 1) {
    if (cl) calc(l, k);
    if (cr && (!cl || l != r)) calc(r, k);
  }
}

ll query(int l, int r) {
  ll ans = 0;
  push(l, l+1);
  push(r-1, r);
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &m);
  h = sizeof(int) * 8 - __builtin_clz(n);
  for (int i = 0; i < n; ++i) scanf("%lld", &t[n+i]);
  build(0, n);
  for (int i = 0; i < m; ++i) {
    ll ti, li, ri, ki;
    scanf("%lld", &ti);
    if (ti == 1) {
      scanf("%lld%lld%lld", &li, &ri, &ki);
      increment(li-1, ri, ki);
    } else {
      scanf("%lld%lld", &li, &ri);
      printf("%lld\n", query(li-1, ri));
    }
  }
}