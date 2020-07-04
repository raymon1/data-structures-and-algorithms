#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class Node
{
public:
	map<char, int> next;
  int startIndex;
  int length;

  Node (int startIndex, int length) : startIndex(startIndex), length(length)
	{
	}

  void SplitNode(vector<Node> &t, const string &text, int i)
  {
    Node newChild = Node(i, length - i + startIndex);
    length = i - startIndex;

    for (auto it = next.begin(); it != next.end(); it++) {
      newChild.next[it->first] = it->second;
    }
    next = map<char, int>();
    next[text[i]] = t.size(); 
    t.push_back(newChild);     
  }
};


void InsertPattern(vector<Node> &t, const string& text, int i) {
  int currentNode = 0;
  while(i < text.size())
  {
    if (t[currentNode].next.find(text[i]) == t[currentNode].next.end()) // not found
    {
      t[currentNode].next[text[i]] = t.size();
      currentNode = t.size();
      t.push_back(Node(i, text.size() - i));
      return;
    }
    else
    {      
      currentNode = t[currentNode].next[text[i]];
      for (int j = t[currentNode].startIndex; j < t[currentNode].startIndex + t[currentNode].length; j++) {
        if(text[j] != text[i]) {
          t[currentNode].SplitNode(t, text, j);
          break;
        }
        i++;
      }
    }
  }

  return;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  // Implement this function yourself
  vector <Node> t;
	t.push_back(Node(-1, -1));

  for (int i = 0; i < text.size(); ++i) {
    InsertPattern(t, text, i);
  }

  vector<string> result(t.size() - 1);
  for (int i = 1; i < t.size(); ++i) {
    result[i - 1] = text.substr(t[i].startIndex, t[i].length);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
