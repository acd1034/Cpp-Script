#include <bits/stdc++.h>
using namespace std;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  const char* dlm = "";
  for (const auto& x : v) os << exchange(dlm, "\n") << x;
  return os;
}
struct Graph {
  using seen_t    = uint64_t;
  using ver_t     = size_t;
  using edge_t    = pair<size_t, ver_t>;
  const seen_t NO = 1e18;
  vector<seen_t> seen;
  vector<vector<edge_t>> edge;
  Graph(size_t n) : seen(n, NO), edge(n) {}

  void search(ver_t s) {
    seen[s] = 0;
    priority_queue<edge_t, vector<edge_t>, greater<edge_t>> que;
    que.push(make_pair(0, s));
    while (!que.empty()) {
      auto v = que.top();
      que.pop();
      for (const auto& nextv : edge[v.second]) {
        auto alt = seen[v.second] + nextv.first;
        if (alt < seen[nextv.second]) {
          seen[nextv.second] = alt;
          que.emplace(seen[nextv.second], nextv.second);
        }
      }
    }
  }
};
ostream& operator<<(ostream& os, const Graph& g) {
  for (const auto& x : g.seen) {
    if (x < g.NO)
      cout << x << '\n';
    else
      cout << "INF\n";
  }
  return os;
}
int32_t main() {
  size_t v, e, r;
  cin >> v >> e >> r;
  Graph g(v);
  size_t s, t, d;
  for (size_t i = 0; i < e; ++i) {
    cin >> s >> t >> d;
    g.edge[s].emplace_back(d, t);
  }
  g.search(r);
  cout << g;
}
