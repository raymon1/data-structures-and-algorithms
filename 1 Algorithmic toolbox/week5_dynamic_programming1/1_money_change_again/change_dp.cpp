#include <iostream>
#include <algorithm>

int get_change(int m) {
  //write your code here
  int coins[3] = {1, 3, 4};
  int dp[m + 1];
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 1;
  dp[4] = 1;

  for (int i = 5; i <= m; i++)
  {
    dp[i] = dp[i - coins[0]] + 1;
    for (int j = 1; j < 3; j++)
    {
      dp[i] = std::min(dp[i - coins[j]] + 1, dp[i]);
    }
  }

  return dp[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
