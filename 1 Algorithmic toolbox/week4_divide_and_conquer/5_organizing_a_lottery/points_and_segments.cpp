#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <exception>

using std::vector;

struct Point {
  long long place;
  short type; //s = 0, p = 1, e = 2
};

bool comparePoints(Point p1, Point p2)
{
  if(p1.place != p2.place)
    return p1.place < p2.place;

  return p1.type < p2.type;
}

vector<long long>
fast_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points)
{  
  vector<Point> p(points.size() + ends.size() + starts.size());

  for (int i = 0; i < points.size(); ++i)
  {
    p[i] = {points[i], 1};
  }

  for (int i = 0; i < starts.size(); ++i){
    p[i + points.size()] = {starts[i], 0};
  } 
  
  for (int i = 0; i < ends.size(); ++i){
    p[i + points.size() + starts.size()] = {ends[i], 2};
  }

  std::sort(p.begin(), p.end(), comparePoints);

  int segments = 0;
  std::unordered_map<long long, long long> counts;
  for (int i = 0; i < p.size(); ++i)
  {
    if (p[i].type == 1 && counts.find(p[i].place) == counts.end())
    {
      counts.insert({p[i].place, segments});
    }
    else if(p[i].type == 0) {
      segments++;
    }
    else if(p[i].type == 2) {
      segments--;
    }
  }

  vector<long long> cnt(points.size(), 0);
  for (int i = 0; i < cnt.size(); ++i) {
    std::unordered_map<long long, long long>::iterator it = counts.find(points[i]);
    if(it != counts.end()) {
      cnt[i] = it->second;
    }
  }

  return cnt;
}

vector<int> naive_count_segments(vector<long long> starts, vector<long long> ends, vector<long long> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

void test_solution() {
  for (int k = 0; k < 100; k++) {
    int n = rand() % 50000 + 2;
    vector<long long> starts(n);
    vector<long long> ends(n);
    vector<long long> points(n);

    for (int i = 0; i < n;++i){
      starts[i] = rand() % 200000001 - 100000000;
      ends[i] = starts[i] + rand() % 200000000 + 1;

      points[i] = rand() % 200000000 - 100000000;
    }

    vector<long long> cnt = fast_count_segments(starts, ends, points);
    vector<int> cnt1 = naive_count_segments(starts, ends, points);
    assert(cnt1.size() == cnt.size());
    assert(n == cnt.size());
    for (int i = 0; i < cnt1.size(); i++)
    {
      assert(cnt[i] == cnt1[i]);
    }

    std::cout << "Done Test" << '\n';
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<long long> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<long long> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  // test_solution();
  vector<long long> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
