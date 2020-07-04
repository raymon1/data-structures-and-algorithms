#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    vector<int> stack;
    int current = 0;
    while (!stack.empty() || current != -1) {
      while(current != -1){
        stack.push_back(current);
        current = left[current];
      }

      current = stack.back();
      stack.pop_back();

      result.push_back(key[current]);
      current = right[current];
    }
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    vector<int> stack;
    stack.push_back(0);
    int current = 0;
    while (!stack.empty())
    {
      current = stack.back();
      stack.pop_back();

      result.push_back(key[current]);

      if(right[current] != -1) {
        stack.push_back(right[current]);
      }
      
      if(left[current] != -1) {
        stack.push_back(left[current]);
      }
    }
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    vector<int> stack;
    int current = 0;
    do {
      while(current != -1){
        if(right[current] != -1) {
          stack.push_back(right[current]);
        }
        stack.push_back(current);
        current = left[current];
      }

      current = stack.back();
      stack.pop_back();

      if(right[current] != -1 && right[current] == stack.back()){
        stack.pop_back();
        stack.push_back(current);
        current = right[current];
      }
      else {        
        result.push_back(key[current]);
        current = -1;
      }
    } while (!stack.empty());

    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

