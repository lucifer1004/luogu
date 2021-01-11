#include <iostream>
#include <vector>
#define MAXN 100005
#define lson (idx << 1)
#define rson (idx << 1 | 1)

typedef long long ll;

std::vector<int> adj[MAXN]{};
int parent[MAXN]{}, size[MAXN]{}, depth[MAXN]{}, hson[MAXN], top[MAXN], dfn[MAXN], rank[MAXN], initial[MAXN]{};
int tot = 0, n, m, r, p;

struct Node {
  int l, r, val, lazy = 0;
} s[MAXN << 2];

void init(int u, int p) {
  parent[u] = p, size[u] = 1, depth[u] = depth[p] + 1;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    init(v, u);
    if (size[v] > size[hson[u]])
      hson[u] = v;
    size[u] += size[v];
  }
}

void decompose(int u, int t) {
  top[u] = t;
  dfn[u] = ++tot;
  rank[tot] = u;
  if (hson[u]) {
    decompose(hson[u], t);
    for (int v : adj[u])
      if (v != hson[u] && v != parent[u])
        decompose(v, v);
  }
}

void calc(int idx) {
  s[idx].val = (s[lson].val + s[rson].val) % p;
}

void build(int idx, int l, int r) {
  s[idx].l = l, s[idx].r = r;
  if (l == r) {
    s[idx].val = initial[rank[l]];
  } else {
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    calc(idx);
  }
}

void push_down(int idx) {
  if (s[idx].lazy) {
    for (int i = lson; i <= rson; ++i) {
      s[i].val = (1LL * s[idx].lazy * (s[i].r - s[i].l + 1) + s[i].val) % p;
      s[i].lazy = (s[i].lazy + s[idx].lazy) % p;
    }
    s[idx].lazy = 0;
  }
}

int query(int idx, int l, int r) {
  if (l <= s[idx].l && s[idx].r <= r)
    return s[idx].val;
  push_down(idx);
  int mid = (s[idx].l + s[idx].r) >> 1;
  int ans = 0;
  if (l <= mid)
    ans += query(lson, l, r);
  if (mid + 1 <= r)
    ans = (ans + query(rson, l, r)) % p;
  return ans;
}

void update(int idx, int l, int r, int x) {
  if (l <= s[idx].l && s[idx].r <= r) {
    s[idx].val = (1LL * x * (s[idx].r - s[idx].l + 1) + s[idx].val) % p;
    s[idx].lazy = (s[idx].lazy + x) % p;
  } else {
    push_down(idx);
    int mid = (s[idx].l + s[idx].r) >> 1;
    if (l <= mid)
      update(lson, l, r, x);
    if (mid + 1 <= r)
      update(rson, l, r, x);
    calc(idx);
  }
}

int main() {
  std::cin >> n >> m >> r >> p;
  for (int i = 1; i <= n; ++i)
    std::cin >> initial[i];
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  init(r, 0);
  decompose(r, r);
  build(1, 1, n);

  while (m--) {
    int t, x, y, z, ans;
    std::cin >> t;
    switch (t) {
    case 1:
      std::cin >> x >> y >> z;
      while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]])
          std::swap(x, y);
        update(1, dfn[top[x]], dfn[x], z);
        x = parent[top[x]];
      }
      if (depth[x] > depth[y])
        std::swap(x, y);
      update(1, dfn[x], dfn[y], z);
      break;
    case 2:
      std::cin >> x >> y;
      ans = 0;
      while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]])
          std::swap(x, y);
        ans = (ans + query(1, dfn[top[x]], dfn[x])) % p;
        x = parent[top[x]];
      }
      if (depth[x] > depth[y])
        std::swap(x, y);
      ans = (ans + query(1, dfn[x], dfn[y])) % p;
      std::cout << ans << std::endl;
      break;
    case 3:
      std::cin >> x >> z;
      update(1, dfn[x], dfn[x] + size[x] - 1, z);
      break;
    case 4:
      std::cin >> x;
      std::cout << query(1, dfn[x], dfn[x] + size[x] - 1) << std::endl;
      break;
    default:
      break;
    }
  }
}
