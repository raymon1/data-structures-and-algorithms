#include <iostream>
#include <vector>
// #include <iomanip>
using std::vector;

int partition3(vector<int> &A) {
  int sum = 0;
  for (size_t i = 0; i < A.size(); ++i) {
    sum += A[i];
  }

  if(sum % 3 != 0)
    return 0;

  int W = sum / 3;

  int n = A.size();
  vector<vector<int>> dp(n + 1);

  for (size_t i = 0; i <= n; ++i){
    dp[i] = vector<int>(W + 1);
  //  dp[i][0] = 0;
  }

  for (size_t i = 0; i < n; ++i) {
  //  std::cout << A[i] << " " << W << " ";
   if (A[i] <= W)
     dp[i + 1][A[i]] = 1;
  }

  // for (size_t i = 0; i <= n; ++i) {
  //   for (size_t j = 0; j <= W; ++j)
  //   {
  //     std::cout << std::setfill('0') << std::setw(2) << dp[i][j] << " "; 
  //   }
  //   std::cout << std::endl;
  // }

  for (size_t i = 1; i <= n; ++i) {
    int wi = A[i - 1];
    for (size_t j = 1; j <= W; ++j)
    {
      if(wi <= j)
      {
        for (size_t k = 1; k < i; ++k)
          dp[i][j] += dp[i - k][j - wi];        
      }
    }
  }

  // for (size_t i = 0; i <= n; ++i) {
  //   for (size_t j = 0; j <= W; ++j)
  //   {
  //     std::cout << std::setfill('0') << std::setw(2) << dp[i][j] << " "; 
  //   }
  //   std::cout << std::endl;
  // }

  int count = 0;
  for (size_t i = 1; i <= n; ++i)
  {
    count += dp[i][W];
  }

    return count >= 3 ? 1 : 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
