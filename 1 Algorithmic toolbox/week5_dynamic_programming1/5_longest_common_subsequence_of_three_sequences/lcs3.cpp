#include <iostream>
#include <vector>
#include <algorithm> 

using std::vector;
using std::max_element;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here  
  int n = a.size();
  int m = b.size();
  int l = c.size();
  int dp[n + 1][m + 1][l + 1] = {};

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = 1; k <= l; ++k) {
        int x[] = { dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1],
            dp[i - 1][j - 1][k], dp[i - 1][j][k - 1], dp[i][j - 1][k - 1],
            dp[i - 1][j - 1][k - 1]
        };
        if (a[i - 1] == b[j - 1] && a[i-1] == c[k-1])
        {
          x[6]++;
        }

        dp[i][j][k] = *std::max_element(x, x + 7);
      }
    }
  }

  return dp[n][m][l];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
