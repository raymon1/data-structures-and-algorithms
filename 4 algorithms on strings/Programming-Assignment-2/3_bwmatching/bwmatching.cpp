#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string &bwt,
                   map<char, int> &starts,
                   map<char, vector<int>> &occ_count_before)
{
  // Implement this function yourself
  int count = 0;
  for (char c : bwt)
  {
    starts[c]++;
  }

  vector<char> available_chars;
  for (auto it : starts)
  {
    available_chars.push_back(it.first);
    occ_count_before[it.first] = vector<int>(bwt.size() + 1, 0);
  }

  //  occ_count_before[bwt[0]][0]++;
  for (int i = 1; i <= bwt.size(); ++i)
  {
    for (auto it = occ_count_before.begin(); it != occ_count_before.end(); it++)
    {
      it->second[i] = it->second[i - 1];
    }
    occ_count_before[bwt[i - 1]][i]++;
  }

  sort(available_chars.begin(), available_chars.end());

  int prev_count = 0;
  for (auto c : available_chars)
  {
    prev_count += starts[c];
    starts[c] = prev_count - starts[c];
  }
}

int countSymbol(int ind, const vector<int> &occ)
{
  for (int i = 0; i < occ.size(); ++i)
  {
    if (occ[i] > ind)
      return i;
  }

  return 0;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string &pattern,
                     const string &bwt,
                     const map<char, int> &starts,
                     const map<char, vector<int>> &occ_count_before)
{
  int top = 0;
  int bottom = bwt.size() - 1;

  int patternBack = pattern.size() - 1;
  while (top <= bottom)
  {
    if (patternBack > -1)
    {
      char symbol = pattern[patternBack];
      patternBack--;
      auto it = occ_count_before.find(symbol);
      int symbol_top_occ = it != occ_count_before.end() ? it->second[top] : -1;
      int symbol_bot_occ = it != occ_count_before.end() ? it->second[bottom + 1] : -1;
      if (symbol_top_occ != -1 && (symbol_bot_occ > symbol_top_occ))
      {
        //top ← FirstOccurrence(symbol) + Countsymbol(top, LastColumn)
        //bottom ← FirstOccurrence(symbol) + Countsymbol(bottom + 1, LastColumn) − 1
        top = starts.find(symbol)->second + it->second[top];
        bottom = starts.find(symbol)->second + it->second[bottom + 1] - 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return bottom - top + 1;
    }
  }

  return 0;
}

int main()
{
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int>> occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi)
  {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
