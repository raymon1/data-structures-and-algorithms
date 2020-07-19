#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

string InverseBWT(const string& bwt) {
  if(bwt.size() == 1)
    return bwt;

  string text = "";

  // write your code here
  string first_col = bwt;
  sort(first_col.begin(), first_col.end());

  unordered_map<char, vector<int>> first_col_map(bwt.size());
  vector<int> last_col_char_counter(bwt.size());

  unordered_map<char, int> counter;
  for (int i = 0; i < bwt.size(); ++i) {
    last_col_char_counter[i] = counter[bwt[i]];
    counter[bwt[i]]++;
  }

  for (int i = 0; i < first_col.size(); ++i) {
    first_col_map[first_col[i]].push_back(i);
  }

  text = "$";
  int ind = 0;
  for (int i = 1; i < bwt.size(); ++i) {
    int last_col_index = first_col_map[text[text.size() - 1]][ind];
    text += bwt[last_col_index];
    ind = last_col_char_counter[last_col_index];
  }

  reverse(text.begin(), text.end());
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
