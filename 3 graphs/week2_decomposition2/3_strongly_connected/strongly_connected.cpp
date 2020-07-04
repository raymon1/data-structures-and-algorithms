#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(int vertex, int* clock, vector<bool> &visited, vector<pair<int,int>> &vertexPostOrder, vector<vector<int> > &adj) {
  visited[vertex] = true;
  (*clock)++;

  for (int i = 0; i < adj[vertex].size(); ++i) {
      if(!visited[adj[vertex][i]])
        dfs(adj[vertex][i], clock, visited, vertexPostOrder, adj);
  }
  (*clock)++;

  pair<int, int> temp(vertex, *clock);
  vertexPostOrder.push_back(temp);
}

void dfs(int vertex, vector<bool> &visited, vector<vector<int> > &adj) {
  visited[vertex] = true;
  
  for (int i = 0; i < adj[vertex].size(); ++i) {
      if(!visited[adj[vertex][i]])
        dfs(adj[vertex][i], visited, adj);
  }
}

vector<vector<int>> reverse(vector<vector<int> > &adj) {
  vector<vector<int>> adjR(adj.size());
  for (int i = 0; i < adj.size(); ++i) {
    for (int j = 0; j < adj[i].size(); ++j) {
      adjR[adj[i][j]].push_back(i);
    }
  }

  return adjR;
}



int number_of_strongly_connected_components(vector<vector<int> > adj) {
  vector<vector<int>> adjR = reverse(adj);

  vector<bool> rVisited(adj.size(), false);
  vector<pair<int, int>> vertexPostOrder;
  int clock = 0;

  for (int i = 0; i < adjR.size(); ++i) {
    if(!rVisited[i]) {
      dfs(i, &clock, rVisited, vertexPostOrder, adjR);
    }
  }

  int scc = 0;
  vector<bool> visited(adj.size(), false);

  for (int i = vertexPostOrder.size() - 1; i >= 0; --i) {
    int v = vertexPostOrder[i].first;
    
    if(!visited[v]) {
      scc++;
      dfs(v, visited, adj);
    }
  }

  return scc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << number_of_strongly_connected_components(adj);
}
