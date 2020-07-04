#include <iostream>
#include <cassert>


long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd(int a, int b) {
  if (b == 0) return a;

  return gcd(b, a % b);
}

long long lcm(int a, int b){
  return (long long) a / gcd(a, b) * b;
}

void test_solution() {
    for (int i = 1; i < 1500; ++i) {
        int n = rand() % 100 + 1;
        int m = rand() % 100 + 1;
        
        assert(lcm(n, m) == lcm_naive(n, m));
    }        
}


int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << lcm_naive(a, b) << std::endl;
  //test_solution();
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
