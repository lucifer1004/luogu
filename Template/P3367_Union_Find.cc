#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
  vector<int> f, s;

  int find(int x)
  {
    int x0 = x;
    while (x != f[x])
      x = f[x];
    f[x0] = x;
    return x;
  }

public:
  UnionFind(int n)
  {
    for (int i = 0; i <= n; ++i)
    {
      f.push_back(i);
      s.push_back(1);
    }
  }

  void merge(int a, int b)
  {
    int fa = find(a);
    int fb = find(b);
    if (s[fa] > s[fb])
    {
      f[fb] = fa;
      s[fa] = s[fa] + s[fb];
    }
    else
    {
      f[fa] = fb;
      s[fb] = s[fa] + s[fb];
    }
  }

  bool query(int a, int b)
  {
    return find(a) == find(b);
  }
};

int main()
{
  int n, m;
  cin >> n >> m;
  auto uf = UnionFind(n);
  for (int i = 0; i < m; ++i)
  {
    int zi, xi, yi;
    cin >> zi >> xi >> yi;
    if (zi == 1)
      uf.merge(xi, yi);
    else
    {
      bool result = uf.query(xi, yi);
      if (result)
        cout << "Y" << endl;
      else
        cout << "N" << endl;
    }
  }
}