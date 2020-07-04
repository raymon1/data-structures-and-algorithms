#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  int n = w.size();
  vector<vector<int>> dp(n + 1);

  for (size_t i = 0; i <= n; ++i)
  {
    dp[i] = vector<int>(W + 1);
    dp[i][0] = 0;
  }
  for (size_t i = 0; i <= W; ++i) {
    dp[0][i] = 0;
  }

  for (size_t i = 1; i <= n; ++i)
  {
    for (size_t j = 1; j <= W; ++j)
    {
      int wi = w[i - 1];
      dp[i][j] = dp[i - 1][j];

      if (wi <= j)
      {
        int val = dp[i - 1][j - wi] + wi;
        if (val > dp[i][j])
          dp[i][j] = val;
      }
    }
  }

  return dp[n][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
