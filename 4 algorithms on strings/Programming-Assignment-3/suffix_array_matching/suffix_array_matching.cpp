#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <assert.h>

using std::cin;
using std::string;
using std::unordered_map;
using std::vector;

vector<int> sort_characters(const string &s)
{
  char alphabet[] = {'$', 'A', 'C', 'G', 'T'};
  vector<int> order(s.size());
  unordered_map<char, int> counts;
  for (int i = 0; i < s.size(); ++i)
    counts[s[i]]++;

  for (int i = 1; i < 5; ++i)
    counts[alphabet[i]] += counts[alphabet[i - 1]];

  for (int i = s.size() - 1; i >= 0; --i)
  {
    counts[s[i]]--;
    order[counts[s[i]]] = i;
  }

  return order;
}

vector<int> compute_char_classes(const string &s, const vector<int> &order)
{
  vector<int> classes(s.size());
  classes[order[0]] = 0;

  for (int i = 1; i < s.size(); ++i)
  {
    if (s[order[i]] != s[order[i - 1]])
      classes[order[i]] = classes[order[i - 1]] + 1;
    else
      classes[order[i]] = classes[order[i - 1]];
  }

  return classes;
}

vector<int> sort_doubled(const string &s, int l, const vector<int> &order, const vector<int> &cl)
{
  vector<int> count(s.size(), 0);
  vector<int> new_order(s.size());

  for (int i = 0; i < s.size(); ++i)
  {
    count[cl[i]]++;
  }

  for (int i = 1; i < s.size(); ++i)
  {
    count[i] += count[i - 1];
  }

  for (int i = s.size() - 1; i >= 0; --i)
  {
    int start = order[i] - l;
    start = start < 0 ? (start + s.size()) % s.size() : start;

    count[cl[start]]--;
    new_order[count[cl[start]]] = start;
  }

  return new_order;
}

vector<int> update_classes(const vector<int> &new_order, const vector<int> &cl, int l)
{
  vector<int> new_cl(new_order.size());
  new_cl[new_order[0]] = 0;
  for (int i = 1; i < new_order.size(); ++i)
  {
    int cur = new_order[i];
    int prev = new_order[i - 1];
    int mid = (cur + l) % new_order.size();
    int midPrev = (prev + l) % new_order.size();

    if (cl[cur] != cl[prev] || cl[mid] != cl[midPrev])
    {
      new_cl[cur] = new_cl[prev] + 1;
    }
    else
    {
      new_cl[cur] = new_cl[prev];
    }
  }

  return new_cl;
}

vector<int> BuildSuffixArray(const string &text)
{
  vector<int> order = sort_characters(text);
  vector<int> cl = compute_char_classes(text, order);

  int l = 1;
  while (l < text.size())
  {
    order = sort_doubled(text, l, order, cl);
    cl = update_classes(order, cl, l);
    l *= 2;
  }

  return order;
}

int str_cmp(const string &pattern, const string &text, int textStart)
{
  int i = 0;
  int j = textStart;
  while (i < pattern.size() && j < text.size() && pattern[i] == text[j])
  {
    i++;
    j++;
  }

  if (i == pattern.size())
  {
    return 0;
  }

  if (pattern[i] < text[j])
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

int find_upper_bound(const string &pattern, const string &text, const vector<int> &suffix_array, int lo, int hi)
{
  while (lo < hi)
  {
    int mid = lo + (hi - lo) / 2;
    int res = str_cmp(pattern, text, suffix_array[mid]);

    if (res == 0)
    {
      if (lo == mid)
      {
        if (str_cmp(pattern, text, suffix_array[hi]) == 0)
        {
          lo++;
        }
        else
        {
          hi--;
        }
      }
      else
      {
        lo = mid;
      }
    }
    else
    {
      hi = mid - 1;
    }
  }

  return hi;
}

int find_lower_bound(const string &pattern, const string &text, const vector<int> &suffix_array, int lo, int hi)
{
  while (lo < hi)
  {
    int mid = lo + (hi - lo) / 2;
    int res = str_cmp(pattern, text, suffix_array[mid]);

    if (res == 0)
    {
      hi = mid;
    }
    else
    {
      lo = mid + 1;
    }
  }

  return lo;
}

vector<int> FindOccurrences(const string &pattern, const string &text, const vector<int> &suffix_array)
{
  vector<int> result;
  int lo = 0;
  int hi = suffix_array.size() - 1;

  while (lo <= hi)
  {
    int mid = lo + (hi - lo) / 2;
    int res = str_cmp(pattern, text, suffix_array[mid]);

    if (res == 0)
    {
      int upper_bound = find_upper_bound(pattern, text, suffix_array, mid, hi);
      int lower_bound = find_lower_bound(pattern, text, suffix_array, lo, mid);

      // assert(str_cmp(pattern, text, suffix_array[lower_bound]) == 0);
      // assert(str_cmp(pattern, text, suffix_array[upper_bound]) == 0);
      // assert(upper_bound >= mid);
      // assert(lower_bound <= upper_bound);
      for (int i = lower_bound; i <= upper_bound; i++)
        result.push_back(suffix_array[i]);

      break;
    }
    else if (res < 0)
      hi = mid - 1;
    else
      lo = mid + 1;
  }

  return result;
}

int main()
{
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index)
  {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j)
    {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i)
  {
    if (occurs[i])
    {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
