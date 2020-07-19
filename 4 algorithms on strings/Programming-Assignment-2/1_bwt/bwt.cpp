#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";
  
  // write your code here
  vector<int> order(text.size());
  for (int i = 0; i < text.size();++i){
    order[i] = i;
  }

  sort(order.begin(), order.end(), [text](int a, int b) {
    for (int i = 0; i < text.size(); i++) {
      int ai = (a + i) % text.size();
      int bi = (b + i) % text.size();
      if(text[ai] == text[bi]) continue;
      return text[ai] < text[bi];
    }
    return true;
  });

  for (int i = 0; i < text.size();++i){
    result += text[(order[i] + text.size() - 1) % text.size()];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}