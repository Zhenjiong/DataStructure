#include <iostream>
#include <vector>
#include <map>

enum State {TOP, BOTTOM, PREEXTEND};

struct Horizonal {
  int y;
  int start;
  int stop;
  State state;
};

struct Point {
  int x;
  int y;
};

class Solution {
 public:
  
  Solution(std::vector<std::vector<int> >& inputs)
    : data(), hlines(), res() {

    
  }

  std::vector<Point> data;
  std::multimap<int, Horizonal> hlines;
  std::vector<std::vector<Point> > res;
};

int main() {
  
  return 0;
}