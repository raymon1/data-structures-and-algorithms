#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>

using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

typedef pair<double, int> pdi;

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0;
  vector<int> parent(x.size(), -1);
  vector<bool> done(x.size(), 0);
  vector<double> cost(x.size(), std::numeric_limits<double>::infinity());
  cost[0] = 0;

  priority_queue<pdi, vector<pdi>, std::greater<pdi> > q;
  for (int i = 0; i < x.size(); ++i)
  {
    q.push(std::make_pair(cost[i], i));
  }

  while (!q.empty())
  {
    int u = q.top().second;
    q.pop();
    if(done[u])
      continue;

    done[u] = 1;

    for (int i = 1; i < x.size(); ++i) {
      double ui = sqrt(pow(x[u] - x[i], 2) + pow(y[u] - y[i], 2));
      // std::cout << u << " " << i << " " << ui << " " << cost[i] << "\n";
      if (!done[i] && ui < cost[i])
      {
        cost[i] = ui;
        parent[i] = u;
        q.push(std::make_pair(cost[i], i));
      }
    }
  }

  for (int i = 0; i < cost.size(); ++i) {
    // std::cout << cost[i] << " ";
    result += cost[i];
  }

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
