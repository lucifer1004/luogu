#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

struct Edge
{
  int from;
  int to;
  int length;
};

struct EdgeCompare
{
  bool operator()(const Edge &a, const Edge &b) const
  {
    return a.length < b.length || (a.length == b.length && a.from < b.from) || (a.length == b.length && a.from == b.from && a.to < b.to);
  }
};

const int CAP = 5001;
multiset<Edge, EdgeCompare> e;
vector<Edge> node[CAP];
bool used[CAP]{};

void extend(int x)
{
  used[x] = true;
  for (const auto &ei : node[x])
  {
    if (!used[ei.to])
      e.insert(ei);
  }
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  Edge min_edge = Edge{0, 0, INT_MAX};
  for (int i = 0; i < m; ++i)
  {
    int xi, yi, zi;
    scanf("%d%d%d", &xi, &yi, &zi);
    node[xi].emplace_back(Edge{xi, yi, zi});
    node[yi].emplace_back(Edge{yi, xi, zi});
    if (zi < min_edge.length)
      min_edge = Edge{xi, yi, zi};
  }
  int cost = min_edge.length;
  int count = 1;
  extend(min_edge.from);
  extend(min_edge.to);

  while (count < n - 1)
  {
    Edge head = *(e.begin());
    e.erase(e.begin());
    if (!used[head.to])
    {
      count++;
      cost += head.length;
      extend(head.to);
    }
  }

  cout << cost << endl;

  return 0;
}