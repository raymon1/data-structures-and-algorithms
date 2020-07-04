#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;

typedef unordered_map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  // edges root;
  t.push_back(edges());

  for (int i = 0; i < patterns.size(); ++i)
  {
    string pattern = patterns[i];
    int currentNode = 0;
    for (int j = 0; j < pattern.size(); ++j)
    {
      char currentSymbol = pattern[j];
      if(t[currentNode].find(currentSymbol) != t[currentNode].end()){
        currentNode = t[currentNode][currentSymbol];
      } else {
        t[currentNode][currentSymbol] = t.size();
        currentNode = t.size();
        edges newNode;
        t.push_back(newNode);
      }
    }
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}