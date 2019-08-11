#include <iostream>
#include <climits>

using namespace std;
typedef unsigned long long ll;

ll gcd(ll i, ll j) {
  if (i < j) return gcd(j, i);
  if (i % j == 0) return j;
  else return gcd(j, i % j);
}

int main() {
    ll n, m;
    cin >> n >> m;

    //总的选取方法数C(nm, 3)
    ll nm = (n+1) * (m+1);
    ll ans = nm * (nm - 1) / 2;
    ans = ans * (nm - 2) / 3;

    //不能构成三角形的
    //三点在同一列
    ll a = (n + 1) * n * (n - 1) / 6 * (m + 1);
    //三点在同一行
    ll b = (m + 1) * m * (m - 1) / 6 * (n + 1);
    //三点在矩形的同一条对角线上
    ll c = 0;
    for (ll i = 2; i <= n; ++i) {
      for (ll j = 2; j <= m; ++j) {
        c += (gcd(i,j) - 1) * (n - i + 1) * (m - j + 1) * 2;
      }
    }

    ans -= a + b + c;

    cout << ans << endl;
}
