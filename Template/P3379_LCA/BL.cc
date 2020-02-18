#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 5e5 + 10;
const int K = 20;
vector<int> a[N];
int dep[N], f[N][K];

void DFS(int u, int parent) {
  f[u][0] = parent;
  dep[u] = parent < 0 ? 0 : dep[parent] + 1;
  for (int k = 1; k < K; ++k) {
    int v = f[u][k - 1];
    f[u][k] = v < 0 ? -1 : f[v][k - 1];
    if (v < 0)
      break;
  }
  for (auto &v : a[u]) {
    if (v != parent)
      DFS(v, u);
  }
}

int LCA(int u, int v) {
  if (dep[u] < dep[v])
    swap(u, v);
  for (int delta = dep[u] - dep[v], k = 0; k < K; ++k) {
    if (delta & (1 << k))
      u = f[u][k];
  }
  for (int k = K - 1; k >= 0; --k) {
    if (f[u][k] != f[v][k]) {
      u = f[u][k];
      v = f[v][k];
    }
  }
  return u == v ? u : f[u][0];
}

int main() {
  memset(f, -1, sizeof(f));
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    a[u].emplace_back(v);
    a[v].emplace_back(u);
  }

  DFS(s - 1, -1);

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    printf("%d\n", LCA(u, v) + 1);
  }
}