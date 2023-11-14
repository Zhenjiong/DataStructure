#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  
  vector<vector<int> > grid;
  int m;
  int n;

  Solution(vector<vector<int> > _grid, int _m, int _n)
    : grid(_grid), m(_m), n(_n) {
    
  }

  bool bfs(int x, int y);
  bool dfs(int x, int y);
};

int main () {
  vector<vector<int> > grid1 = {{1,0,0},
                                {0,1,1},
                                {0,1,1}};
  


  return 0;
}

bool Solution::bfs(int x, int y) {
  if (x < 0 || x >= m || y < 0 || y >= n)
    return false;
  
  return true;
  
}

bool Solution::dfs(int x, int y) {
  if (x < 0 || x >= m || y < 0 || y >= n)
    return false;
  
  return true;
}