#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void DFS(vector<vector<int> > &adj, vector<bool> &visited, int i) {
  if(visited[i])
    return;

  visited[i] = true;

  for (size_t j = 0; j < adj[i].size(); ++j){
    DFS(adj, visited, adj[i][j]);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;

  vector<bool> visited(adj.size(), false);
  for (size_t i = 0; i < adj.size(); ++i) {
    if(visited[i])
      continue;
    res++;
    DFS(adj, visited, i);
  }

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
