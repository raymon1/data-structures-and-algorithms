#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using std::vector;
using std::pair;
using std::priority_queue;

bool relax(int u, int v, vector<int> &distances, int cost){
  if(distances[u] + cost < distances[v]) {    
    distances[v] = distances[u] + cost;
    return true;
  }
  return false;
}


int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  vector<int> distances(adj.size(), 0); 

  bool relaxed = false;

  for (int x = 0; x < adj.size(); ++x) {
    relaxed = false;

    for (int u = 0; u < adj.size(); ++u) {
      for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (relax(u, v, distances, cost[u][i])) {
          relaxed = true;
        }
      }
    }
  }

  return relaxed;
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
  std::cout << negative_cycle(adj, cost);
}
