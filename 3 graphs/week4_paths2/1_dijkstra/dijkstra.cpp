#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

bool relax(int u, int v, vector<int> &distances, int cost){
  if(distances[v] == -1 || distances[u] + cost < distances[v]) {    
    distances[v] = distances[u] + cost;
    return true;
  }
  return false;
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  vector<int> distances(adj.size(), -1);
  distances[s] = 0;

  priority_queue<pair<int, int>> q;
  q.push(std::make_pair(s, 0));

  while(!q.empty()) {
    int u = q.top().first;
    q.pop();

    for (int i = 0; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      if (relax(u, v, distances, cost[u][i])) {
        q.push(std::make_pair(v, distances[v]));
      }
    }
  }

  return distances[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
