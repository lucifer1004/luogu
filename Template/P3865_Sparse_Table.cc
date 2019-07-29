#include <iostream>
#include <cmath>

using namespace std;

const int CAP = 100001;
int s[CAP][20]{};

int query(int l, int r)
{
  int t = log2(r - l + 1);
  return max(s[l - 1][t], s[r - (1 << t)][t]);
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    scanf("%d", &s[i][0]);

  int max_len = log2(n) + 2;
  for (int i = 1; i < max_len; ++i)
  {
    for (int j = 0; j < n - (1 << i) + 1; ++j)
    {
      s[j][i] = max(s[j + (1 << (i - 1))][i - 1], s[j][i - 1]);
    }
  }

  for (int i = 0; i < m; ++i)
  {
    int li, ri;
    scanf("%d%d", &li, &ri);
    printf("%d\n", query(li, ri));
  }

  return 0;
}