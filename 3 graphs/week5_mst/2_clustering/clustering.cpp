#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using std::vector;
using std::pair;
using std::max;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
  int max_table_size;
  vector<DisjointSetsElement> sets;

  DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		if(sets[table].parent != table){
			sets[table].parent = getParent(sets[table].parent);
		}

		return sets[table].parent;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		// merge two components
		// use union by rank heuristic
		// update max_table_size
		if (realDestination != realSource) {
			if(sets[realDestination].rank > sets[realSource].rank){
				sets[realSource].parent = realDestination;
				sets[realDestination].size += sets[realSource].size;
			}
			else {
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
				if(sets[realDestination].rank == sets[realSource].rank) {
					sets[realSource].rank++;
				}
			}

			max_table_size = max(max(sets[realDestination].size, sets[realSource].size),
				 max_table_size);
      size--;
    }
  }
};

struct Edge {
  int u, v;
  double length;

  Edge(vector<int>& x, vector<int>& y, int u, int v):u(u), v(v) {
    length = sqrt(pow(x[u] - x[v], 2) + pow(y[u] - y[v], 2));
  }
};

bool compareEdges(Edge a, Edge b) {
  return a.length < b.length;
}

double clustering(vector<int> x, vector<int> y, int k) {
  vector<Edge> edges;
  for (int i = 0; i < x.size(); ++i)
  {
    for (int j = i + 1; j < x.size(); ++j) {
      edges.push_back(Edge(x, y, i, j));
    }
  }

  std::sort(edges.begin(), edges.end(), compareEdges);
  auto forest = DisjointSets(x.size());

  for (int i = 0; i < edges.size(); ++i) {
    if(forest.getParent(edges[i].u) != forest.getParent(edges[i].v)) {
      forest.merge(edges[i].u, edges[i].v);      
      if(forest.size == k - 1)
        return edges[i].length;
    }
  }

  return edges[edges.size() - 1].length;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
