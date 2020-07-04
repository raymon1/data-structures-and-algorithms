#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

bool relax(int u, int v, vector<long long> &distances, int cost){
  if(distances[u] == std::numeric_limits<long long>::max()) {
    return false;
  }
  if(distances[u] + cost < distances[v]) {
    // if (cost > 0 && distances[u] + cost < distances[u]
    //  || cost < 0 && distances[u] + cost > distances[u]) {
    //   return false;
    // }

    distances[v] = distances[u] + cost;
    return true;
  }
  return false;
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  distance[s] = 0;
  reachable[s] = 1;
  vector<bool> visited(adj.size(), false);
  queue<int> q;

  for (int x = 0; x <= adj.size(); ++x) {
    for (int u = 0; u < adj.size(); ++u) {
      for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        
        if(reachable[u])
            reachable[v] = 1;
        
       // std::cout << x << " " << u << " " << v << " " << distance[u] << " " << cost[u][i] << " " << distance[v] << "\n";
        if (relax(u, v, distance, cost[u][i]) && x >= adj.size() - 1) {
          shortest[v] = 0;
          if(!visited[v])
            q.push(v);
          visited[v] = 1;
        }
      }
    }
  }
  
  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    for (int v : adj[u])
    {     
      shortest[v] = 0;
 
      if(!visited[v]) {
        visited[v] = 1;
        q.push(v);
      }
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
