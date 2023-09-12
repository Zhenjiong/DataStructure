#include <iostream>
#include <set>
#include <vector>

struct Point {
  int x;
  int y;
  Point(int _x, int _y) : x(_x), y(_y) {};
};

int main() {
  int n = 5;
  std::vector<std::vector<int> > grid(n);
  grid[0] = std::vector<int>({0,0,0,0,0});
  grid[1] = std::vector<int>({0,0,-1,-1,0});
  grid[2] = std::vector<int>({0,-1,0,0,0});
  grid[3] = std::vector<int>({0,0,0,0,-1});
  grid[4] = std::vector<int>({0,0,0,0,0});
  
  std::vector<std::vector<Point> > ob_points;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == -1) {
        // p2 p3 p4
        // p1 -1 p8
        // p5 p6 p7
        bool p1 = j > 0 && grid[i][j-1] == -1;
        bool p2 = j > 0 && i > 0 && grid[i-1][j-1] == -1;
        bool p3 = i > 0 && grid[i-1][j] == -1;
        bool p4 = i > 0 && j < n-1 && grid[i-1][j+1] == -1;
        bool p5 = i < n-1 && j > 0 && grid[i+1][j-1] == -1;
        // bool p6 = i < n-1 && grid[i+1][j] == -1;
        bool p7 = i < n-1 && j < n-1 && grid[i+1][j+1] == -1;
        // bool p8 = j < n-1 && grid[i][j+1] == -1;
        // stronger the future point, p6 and p8
        // if (p5) grid[i+1][j] = -1;
        // if (p7) {
        //   grid[i+1][j] = -1;
        //   grid[i][j+1] = -1;
        // }
        // need to be connetcted
        if (p1 || p2 || p3 || p4) {
          if (p1) {
            for (auto l = ob_points.rbegin(); l != ob_points.rend(); ++l) {
              if (l->back().x == i && l->back().y == j-1) {
                l->push_back(Point(i,j));
                break;
              }
            }
          }
          else {
            bool b = false;
            for (auto l = ob_points.rbegin(); l != ob_points.rend(); ++l) {
              for (auto p = l->rbegin(); p != l->rend(); ++p) {
                if (p->x == i-1 && p->y == j+1) {
                  l->push_back(Point(i,j));
                  b = true;
                  break;
                }
                else if (p->x == i-1 && p->y == j) {
                  l->push_back(Point(i,j));
                  b = true;
                  break;
                }
                else if (p->x == i-1 && p->y == j-1) {
                  l->push_back(Point(i,j));
                  b = true;
                  break;
                }
              }
              if (b) break;
            }
          }
        }
        else if (p5) {
          //TODO
        }
        // begin a new point line
        else {
          std::vector<Point> temp_point;
          temp_point.push_back(Point(i,j));
          ob_points.push_back(temp_point);
        }
      }
    }
  }


  int xx = 1;
  xx >>= 1;
  bool gg;
  if (!xx)
    std::cout << (xx >> 1);
  std::cout << "Hello World!" << std::endl;
  return 0;
}