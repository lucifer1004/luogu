#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#define INF 1e8
#define MAX 500005

using namespace std;

int depth[MAX], enter[MAX], euler[MAX * 2];
vector<int> adj[MAX], st[21];

class Tree {
  int n, root, step;

  void dfs(int i) {
    enter[i] = step;
    euler[step++] = i;
    for (int j : adj[i]) {
      if (enter[j] == -1) {
        depth[j] = depth[i] + 1;
        dfs(j);
        euler[step++] = i;
      }
    }
  }

  void calculate_sparse_table() {
    int upper = 2 * n - 1;
    int max_level = log2(upper) + 1;
    for (int level = 0; level < max_level; ++level)
      for (int i = 0; i < upper; ++i) {
        if (level == 0)
          st[level].emplace_back(euler[i]);
        else {
          st[level].emplace_back(st[level - 1][i]);
          int right = i + (1 << (level - 1));
          if (right < upper &&
              depth[st[level - 1][right]] < depth[st[level][i]])
            st[level][i] = st[level - 1][right];
        }
      }
  }

public:
  Tree(int n, int root) {
    this->n = n;
    this->root = root;
    depth[0] = INF;
  }

  void add_edge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  void init() {
    step = 0;
    dfs(root);
    calculate_sparse_table();
  }

  int query_lca(int u, int v) {
    if (u == v)
      return u;
    int l = min(enter[u], enter[v]);
    int r = max(enter[u], enter[v]);
    int k = log2(r - l);
    int lans = st[k][l];
    int rans = st[k][r - (1 << k) + 1];
    if (depth[lans] < depth[rans])
      return lans;
    else
      return rans;
  }
};

int main() {
  memset(depth, 0, sizeof(depth));
  memset(enter, -1, sizeof(enter));
  memset(euler, 0, sizeof(euler));

  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  Tree tree = Tree(n, s);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree.add_edge(u, v);
  }

  tree.init();

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", tree.query_lca(u, v));
  }
}