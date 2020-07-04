#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

vector<int> partition3(vector<int> &a, int l, int r) {
  int pivot = a[l];
  int end = r; // end
  int begin = l + 1; // begin
  for (int i = l + 1; i <= end; i++)
  {
    if (a[i] < pivot) {
      swap(a[i], a[begin]);
      begin++;
    }
    else if (a[i] > pivot) {
      swap(a[i], a[end]);
      end--;
      i--;
    }
  }

  // std::cout <<l << '-' << r << '-' << pivot << ": " << begin << '-' << end << ": ";

  // for (int i = 0; i < a.size(); ++i){
  //   std::cout << a[i] << ',';
  // }
  // std::cout <<'\n';
  vector<int> m(2);
  m[0] = begin;
  m[1] = end;
  return m;
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
  // std::cout <<l << '-' << r << ' ' << std::endl;
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  vector<int> m = partition3(a, l, r);
  
  randomized_quick_sort(a, l, m[0] - 1);
  randomized_quick_sort(a, m[1] + 1, r);
}


void test_solution() {
    int n = 100000;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
       a[i] = 1000000000; 
    }
    
    randomized_quick_sort(a, 0, a.size() - 1);

    for (int k = 0; k < 1000; k++)
    {
      vector<int> b(n);
      for(int j = 0; j < n; j++) {
          a[j] = rand() % 1000000000;
          b[j] = a[j];
      }
      
      randomized_quick_sort(a, 0, a.size() - 1);
      std::sort(b.begin(), b.end());
      
      for(int j = 0; j < n; j++) {
          assert(a[j] == b[j]);
      }
    }
}



int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  
 // test_solution();
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
