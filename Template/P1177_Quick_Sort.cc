#include <iostream>

using namespace std;

const int CAP = 100001;
int x[CAP]{};

void xswap(int a, int b)
{
  int tmp = x[a];
  x[a] = x[b];
  x[b] = tmp;
}

void qsort(int l, int r)
{
  if (l >= r)
    return;
  int l0 = l;
  int mid = (l + r) / 2; // Use mid as pivot
  xswap(mid, r);
  for (int i = l; i <= r; ++i)
  {
    if (x[i] < x[r] || (x[i] == x[r] && i < mid))
    {
      xswap(i, l);
      l++;
    }
  }
  xswap(l, r);
  qsort(l0, l - 1);
  qsort(l + 1, r);
}

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &x[i]);
  qsort(0, n - 1);
  for (int i = 0; i < n - 1; ++i)
    printf("%d ", x[i]);
  printf("%d\n", x[n - 1]);
  return 0;
}