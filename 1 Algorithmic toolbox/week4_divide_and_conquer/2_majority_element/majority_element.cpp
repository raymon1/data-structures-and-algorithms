#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_count_in_range(vector<int> &a, int x, int left, int right) {
  int count = 0;
  for (int i = left; i <= right; i++) {
    if(a[i] == x)
      count++;
  }

  return count;
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return a[left];
  if (left + 1 == right) return a[left];
  //write your code here

  int mid = (left + right) / 2;

  int left_major = get_majority_element(a, left, mid);
  int right_major = get_majority_element(a, mid + 1, right);

  if(left_major == right_major) {
    return left_major;
  }

  int leftCount = get_count_in_range(a, left_major, left, right);
  int rightCount = get_count_in_range(a, right_major, left, right);

  return leftCount >= rightCount ? left_major : right_major;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_count_in_range(a, get_majority_element(a, 0, a.size()), 0 , a.size()) > (n / 2)) << '\n';
}
