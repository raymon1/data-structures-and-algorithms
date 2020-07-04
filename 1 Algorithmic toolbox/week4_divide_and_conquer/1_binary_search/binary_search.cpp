#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using std::vector;

int binary_search(const vector<long long> &a, long long x) {
  int left = 0, right = (int)a.size(); 

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (x == a[mid]) return mid;
    else if (x < a[mid]) right = mid - 1;
    else left = mid + 1;
  }

  return -1;
}

int linear_search(const vector<long long> &a, long long x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void test_solution() {
    for(int k = 0; k < 10; k++) {
        int n = 3000;
        vector<long long> a(n);
        a[0] = rand() % 100000001;
        for (int i = 1; i < n; i++){
            a[i] = a[i-1] + rand() % 1000 + 1;
        }

        for (int i = 0; i < n; i++) {
            if(a[i] != a[binary_search(a, a[i])]) {
                std::cout << i << ' ' <<a[i] << ' ' << binary_search(a, a[i]) << ' ' << n << '\n' << '\n';

                for(int i = 0; i<n;i++){
                    std::cout << a[i] << ' ';
                }
            }
            
            assert(a[binary_search(a, a[i])] == a[i]);
        
            long long x = rand() % 1000000001;
            assert(binary_search(a, x) == linear_search(a, x));
        }

        assert(binary_search(a, 1000000002) == -1);
        assert(binary_search(a, a[n - 1] + 1) == -1);
        assert(binary_search(a, a[n - 1] + 10) == -1);
        assert(binary_search(a, a[0] - 1) == -1);
        assert(binary_search(a, a[0] - 10) == -1);
    }
}

int main() {
  int n;
  std::cin >> n;
  vector<long long> a(n);
  for (size_t  i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<long long> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  // test_solution();
  for (int i = 0; i < m; ++i)
  {
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
