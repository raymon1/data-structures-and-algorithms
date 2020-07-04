#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

vector<vector<long long>> mins;
vector<vector<long long>> maxs;
vector<int> values;
vector<char> ops;

vector<long long> min_Max(int i, int j) {
  long long mini = LLONG_MAX;
  long long maxi = LLONG_MIN;

  for (size_t k = i; k < j; k++) {
    long long a = eval(maxs[i][k], maxs[k + 1][j], ops[k - 1]);
    long long b = eval(maxs[i][k], mins[k + 1][j], ops[k - 1]);
    long long c = eval(mins[i][k], maxs[k + 1][j], ops[k - 1]);
    long long d = eval(mins[i][k], mins[k + 1][j], ops[k - 1]);

    mini = min(min(min(min(mini, a), b), c), d);
    maxi = max(max(max(max(maxi, a), b), c), d);
  }

  vector<long long> result(2);
  result[0] = mini;
  result[1] = maxi;

  return result;
}

long long get_maximum_value(const string &exp) {
  for (size_t i = 0; i < exp.length(); ++i){
    if(exp[i] >= '0' && exp[i] <= '9'){
      values.push_back(exp[i] - '0');
    }
    else {
      ops.push_back(exp[i]);
    }
  }

  int n = values.size();
  int m = ops.size();

  mins = vector<vector<long long>> (n + 1);
  maxs = vector<vector<long long>> (n + 1);
  mins[0] = vector<long long>(m);
  maxs[0] = vector<long long>(m);
  for (size_t i = 1; i <= n; ++i)
  {
    mins[i] = vector<long long>(n + 1);
    maxs[i] = vector<long long>(n + 1);
    mins[i][i] = values[i - 1];
    maxs[i][i] = values[i - 1];
  }

  for (size_t s = 1; s < n; ++s) {
    for (size_t i = 1; i <= n - s; ++i) {
      int j = i + s;
      vector<long long> minMax = min_Max(i, j);
      mins[i][j] = minMax[0];
      maxs[i][j] = minMax[1];
    }
  }

  return maxs[1][n];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
