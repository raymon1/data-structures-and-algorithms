#include <iostream>

int get_change(int m) {
  //write your code here
  int tens = m / 10;
  int fives = (m - 10 * tens) / 5;
  int ones = (m - 10* tens - 5 * fives); 
  return tens + fives + ones;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
