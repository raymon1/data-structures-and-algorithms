#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::min;

int edit_distance(const string &str1, const string &str2) {
  int n = str1.length();
  int m = str2.length();
  int dp[n + 1][m + 1];

  dp[0][0] = 0;
  for (int j = 1; j <= m; ++j)
  {
    dp[0][j] = dp[0][j - 1] + 1;
  }
  for (size_t i = 1; i <= n; ++i) {
    dp[i][0] = dp[i - 1][0] + 1;
  }
  
  for (int i = 1; i <= n; ++i){
    for (int j = 1; j <= m; ++j) {
      if (str1[i - 1] == str2[j - 1])
      {
        dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1]);
      }
      else {
        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
      }
    }
  }
  
  // for (int j = 0; j <= m; j++)
  // {
  //   std::cout << "\t" << str2[j];
  // }
  //   std::cout << '\n';

  // for (int i = 0; i <= n; i++){
  //   std::cout << str1[i] << "\t";
  //   for (int j = 0; j <= m; j++)
  //   {
  //     std::cout << dp[i][j] << "\t";
  //   }
  //   std::cout << '\n';
  // }

  return dp[n][m];
}

void test_solution(){
  string str1 = "";
  string str2 = "";

  for (int i = 0; i < 25; ++i) {
    str1 += ('a' + rand() % 26);
    str2 += ('a' + rand() % 26);
  }
  std::cout << str1 << std::endl;
  std::cout << str2 << std::endl;
  std::cout << edit_distance(str1, str2) << std::endl;
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
 // test_solution();
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
