#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

bool compareSegments(Segment s1, Segment s2) 
{ 
    return (s1.start < s2.start); 
} 

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here

  std::sort(segments.begin(), segments.end(), compareSegments);
  int min = segments[0].start;
  int max = segments[1].end;
  for (size_t i = 0; i < segments.size(); ++i)
  {
    if(segments[i].start > max) {
      points.push_back(max);
      min = segments[i].start;
      max = segments[i].end;
      continue;
    }
    
    if(segments[i].end < max) {
      max = segments[i].end;
    }
    if(segments[i].start > min) {
      min = segments[i].start;
    }
  }

  points.push_back(max);
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
