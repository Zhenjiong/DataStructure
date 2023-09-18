#include <iostream>
#include <set>
#include <vector>

struct Point {
  int x;
  int y;
  Point(int _x, int _y) : x(_x), y(_y) {};
};


class Solution {
 public:
  std::vector<std::vector<int> > grid;
  std::vector<int> dead_monsters;
  int n;

  Solution(std::vector<std::vector<int> > &input, int _n)
    : n(_n), grid(input), dead_monsters() {
    if (!dfs(0,0))
      std::cout << 0 << std::endl;
    else {
      std::set<int> d(dead_monsters.cbegin(), dead_monsters.cend());
      std::cout << d.size() << std::endl;
    }
  }

  bool dfs(int x, int y);

};

int main() {
  int n = 5;
  std::vector<std::vector<int> > grid(n);
  grid[0] = std::vector<int>({0,0,0,1,0});
  grid[1] = std::vector<int>({0,0,-1,-1,0});
  grid[2] = std::vector<int>({0,-1,0,0,0});
  grid[3] = std::vector<int>({0,0,1,0,-1});
  grid[4] = std::vector<int>({0,0,1,1,0});
  
  Solution(grid, n);
  std::cout << "Hello World!" << std::endl;
  return 0;
}

bool Solution::dfs(int x, int y) {
  if (x < 0 || x > n-1 || y < 0 || y > n-1 || this->grid[x][y] == -1)
    return false;
  if (x == n-1 && y == n-1) return true;
  if (dfs(x+1,y) || dfs(x,y+1)) {
    if (this->grid[x][y] == 1)
      this->dead_monsters.push_back(x*n+y);
    return true;
  }
  else {
    return false;
  }
}