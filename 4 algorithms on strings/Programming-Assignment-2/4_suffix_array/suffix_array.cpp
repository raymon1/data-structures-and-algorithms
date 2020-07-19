#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
// vector<int> BuildSuffixArray(const string &text)
// {
//   vector<int> result(text.size());
//   std::iota(result.begin(), result.end(), 0);

//   sort(result.begin(), result.end(), [text](int a, int b) {
//     while (1)
//     {
//       if (text[a++] == text[b++])
//         continue;
//       return text[--a] < text[--b];
//     }
//     return true;
//   });

//   return result;
// }

struct suffix
{
  int index;
  int rank[2];
};

vector<int> BuildSuffixArray(const string &text)
{
  vector<int> result(text.size());
  auto cmp = [](suffix a, suffix b) {
    return a.rank[0] == b.rank[0] ? a.rank[1] < b.rank[1] : a.rank[0] <= b.rank[0];
  };

  vector<suffix> suffixes(text.size());
  for (int i = 0; i < text.size(); ++i)
  {
    suffixes[i].index = i;
    suffixes[i].rank[0] = text[i] - '$';
    suffixes[i].rank[1] = (i + 1) < text.size() ? text[i + 1] - '$' : -1;
  }

  sort(suffixes.begin(), suffixes.end(), cmp);

  vector<int> ind(text.size());

  for (int k = 4; k < 2 * text.size(); k *= 2)
  {
    int rank = 0;
    int prev_rank = suffixes[0].rank[0];
    suffixes[0].rank[0] = 0;
    ind[suffixes[0].index] = 0;

    for (int i = 1; i < text.size(); ++i)
    {
      if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
      {
        suffixes[i].rank[0] = rank;
      }
      else
      {
        prev_rank = suffixes[i].rank[0];
        suffixes[i].rank[0] = ++rank;
      }
      ind[suffixes[i].index] = i;
    }

    for (int i = 0; i < text.size(); ++i)
    {
      int nextIndex = suffixes[i].index + k / 2;
      suffixes[i].rank[1] = nextIndex < text.size() ? suffixes[ind[nextIndex]].rank[0] : -1;
    }

    sort(suffixes.begin(), suffixes.end(), cmp);
  }

  for (int i = 0; i < text.size(); ++i)
  {
    result[i] = suffixes[i].index;
  }

  return result;
}

int main()
{
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i)
  {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
