#include <iostream>
#include <set>
#include <vector>

struct Point {
  int x;
  int y;
  Point(int _x, int _y) : x(_x), y(_y) {};
};

struct Wall {
  int left, right, top, bot;
  Wall(int _left, int _right, int _top, int _bot)
    : left(_left), right(_right), top(_top), bot(_bot) {};
  Wall(){};
};

class Solution {
 public:
  std::vector<std::vector<int> > grid;
  std::vector<std::vector<Point> > ob_points;
  std::vector<Point> monsters;
  std::vector<Wall> walls;
  int n;

  Solution(std::vector<std::vector<int> > &input, int _n)
    : n(_n), ob_points(), walls(), monsters(), grid(input) {
    
    construct_ob();

    // grid[row][col]
    std::set<int> straight_row;  // row number
    std::set<int> straight_col;  // col number

    for (auto &ob : ob_points) {
      int right = 0;
      int left = n-1;
      int bot = 0;
      int top = n-1;
      for (auto p : ob) {
        if (left > p.x) left = p.x;
        if (right < p.x) right = p.x;
        if (top > p.y) top = p.y;
        if (bot < p.y) bot = p.y;
        straight_col.insert(p.y);
        straight_row.insert(p.x);
      }
      walls.push_back(Wall(left, right, top, bot));
    }

    if (straight_col.size() == n || straight_row.size() == n)
      std::cout << 0;
    else {
      // TODO
      int counter = 0;
      for (auto m : monsters) {

      }
    }

  }

  void dfs(bool oried, int x, int y);

  void construct_ob() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == -1)
          dfs(true, i, j);
        else if (grid[i][j] == 2)
          continue;
        else if (grid[i][j] == 1) {
          monsters.push_back(Point(i,j));
          grid[i][j] = 2;
        }
        else
          grid[i][j] = 2;
      }
    }
  }

};

int main() {
  int n = 5;
  std::vector<std::vector<int> > grid(n);
  grid[0] = std::vector<int>({0,0,0,0,0});
  grid[1] = std::vector<int>({0,0,-1,-1,0});
  grid[2] = std::vector<int>({0,-1,0,0,0});
  grid[3] = std::vector<int>({0,0,0,0,-1});
  grid[4] = std::vector<int>({0,0,0,0,0});
  
  Solution(grid, n);
  std::cout << "Hello World!" << std::endl;
  return 0;
}


void Solution::dfs(bool oried, int x, int y) {
  if (x < 0 || x > n-1 || y < 0 || y > n-1 || grid[x][y] == 2)
    return;
  if (grid[x][y] == -1) {
    grid[x][y] = 2;
    // true, this is the start point
    if (oried) {
      std::vector<Point> temp_point;
      temp_point.push_back(Point(x,y));
      ob_points.push_back(temp_point);
    }
    // false, this is not the start point
    else {
      ob_points.rbegin()->push_back(Point(x,y));
    }
    dfs(false, x,y+1);
    dfs(false, x,y-1);
    dfs(false, x+1,y);
    dfs(false, x+1,y+1);
    dfs(false, x+1,y-1);
    dfs(false, x-1,y);
    dfs(false, x-1,y+1);
    dfs(false, x-1,y-1);
  }
  else if (grid[x][y] == 1) {
    monsters.push_back(Point(x,y));
    grid[x][y] = 2;
  }
  else
    grid[x][y] = 2;
}