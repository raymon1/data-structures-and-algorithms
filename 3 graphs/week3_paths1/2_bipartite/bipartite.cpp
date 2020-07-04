#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  vector<int> colors(adj.size(), -1);

  for (int i = 0; i < adj.size(); ++i){
    if(colors[i] != -1)
      continue;
    colors[i] = 0;
    queue<int> q;
    q.push(i);

    while(!q.empty()) {
      int u = q.front();
      q.pop();

      for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if(colors[v] == -1) {
          colors[v] = colors[u] ^ 1;
          q.push(v);
        }
        else if (colors[adj[u][i]] == colors[u]) {
          return 0;
        }
      }
    }
  }

  return 1;
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
  std::cout << bipartite(adj);
}
