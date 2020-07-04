#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  if(s == t)
    return 0;

  vector<int> distance(adj.size(), -1);

  queue<int> q;
  q.push(s);
  distance[s] = 0;

  while(!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = 0; i < adj[u].size(); ++i) {
      if(distance[adj[u][i]] == -1){
        if(adj[u][i] == t) {
          return distance[u] + 1;
        }
        
        distance[adj[u][i]] = distance[u] + 1;
        q.push(adj[u][i]);
      }
    }
  }

  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
