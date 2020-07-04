#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  std::vector<int> dp(std::max(n + 1, 4));
  std::vector<int> previous(std::max(n + 1, 4));
  dp[0] = 0;
  dp[1] = 0;
  dp[2] = 1;
  dp[3] = 1;
  previous[0] = 0;
  previous[1] = 0;
  previous[2] = 1;
  previous[3] = 1;

  for (int i = 4; i <= n; i++) {
    dp[i] = dp[i - 1];
    previous[i] = i - 1;
    if (i % 2 == 0 && dp[i / 2] < dp[i])
    {
      dp[i] = dp[i / 2];
      previous[i] = i / 2;
    }
    if (i % 3 == 0 && dp[i / 3] < dp[i]) {
      dp[i] = dp[i / 3];
      previous[i] = i / 3;
    }

    dp[i]++;
  }

  while (n >= 1) {
   sequence.push_back(n);
   n = previous[n];
  }

  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (int i = sequence.size() - 1; i >= 0; --i) {
    std::cout << sequence[i] << " ";
  }
}
