#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// s ← array of integers of length |P|
// s[0] ← 0, border ← 0
// for i from 1 to |P| − 1:
//  while (border > 0) and (P[i] ̸= P[border]):
//    border ← s[border − 1]
//  if P[i] == P[border]:
//    border ← border + 1
//  else:
//    border ← 0
// s[i] ← border
// return s
vector<int> prefix_function(const string &t)
{
  vector<int> s(t.size());
  int border = s[0] = 0;
  for (int i = 1; i < s.size(); ++i)
  {
    while (border > 0 && t[i] != t[border])
    {
      border = s[border - 1];
    }
    if (t[i] == t[border])
    {
      border++;
    }
    else
    {
      border = 0;
    }

    s[i] = border;
  }

  return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string &pattern, const string &text)
{
  vector<int> result;
  // Implement this function yourself

  vector<int> pff = prefix_function(pattern + '$' + text);

  for (int i = pattern.size() + 1; i < pff.size(); i++)
  {
    //  std::cout << pff[i] << " ";
    if (pff[i] == pattern.size())
    {
      result.push_back(i - (pattern.size() << 1));
    }
  }

  return result;
}

int main()
{
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i)
  {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
