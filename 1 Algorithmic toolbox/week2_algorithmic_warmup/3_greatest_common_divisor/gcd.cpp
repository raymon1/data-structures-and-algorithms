#include <iostream>
#include <cassert>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd(int a, int b) {
  if (b == 0) return a;

  return gcd(b, a % b);
}

void test_solution() {
    for (int i = 1; i < 1500; ++i) {
        int n = rand() % 1000000 + 1;
        int m = rand() % 1000000 + 1;
        
        assert(gcd(n, m) == gcd_naive(n, m));
    }        
}


int main() {
  int a, b;
  std::cin >> a >> b;
  //test_solution();
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
