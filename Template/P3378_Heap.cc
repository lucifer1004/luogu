#include <iostream>
#include <set>

using namespace std;

int main()
{
  int n;
  multiset<int> s;

  cin >> n;

  for (int i = 0; i < n; ++i)
  {
    int t, x;
    cin >> t;
    if (t == 1)
    {
      cin >> x;
      s.insert(x);
    }
    if (t == 2)
      cout << *(s.begin()) << endl;
    if (t == 3)
      s.erase(s.cbegin());
  }

  return 0;
}