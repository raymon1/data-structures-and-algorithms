#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct Item { 
    int weight, value;
    double wv;
}; 

bool compareItems(Item i1, Item i2) 
{ 
    return (i1.wv > i2.wv); 
} 


double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  vector<Item> items(weights.size()); 
  for(int i = 0; i < weights.size(); ++i) {
      items[i] = {weights[i], values[i], values[i] * 1.0 / weights[i]};
  }
  
  std::sort(items.begin(), items.end(), compareItems); 


  for (int i = 0; i < items.size() && capacity > 0; ++i) {
    int w = capacity > items[i].weight ? items[i].weight : capacity;
    value += (w * 1.0 / items[i].weight) * items[i].value;
    capacity -= w;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
