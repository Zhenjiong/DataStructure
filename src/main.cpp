#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  
  vector<vector<int> > grid;
  int m;
  int n;
  int island_num;
  unordered_set<int> finished;

  Solution(vector<vector<int> > _grid, int _m, int _n)
    : grid(_grid), m(_m), n(_n),
      finished(), island_num(0) {
    
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1 && finished.find(i*n+j) == finished.end())
          ++island_num;
        dfs(i,j);
      }
    }
  }

  void dfs(int x, int y);
};

int main () {
  vector<vector<int> > grid1 = {{1,0,0,1},
                                {0,1,1,1},
                                {0,0,1,1}};
  Solution s1(grid1, grid1.size(), grid1[0].size());
  cout << s1.island_num << endl;

  return 0;
}

void Solution::dfs(int x, int y) {
  if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0)
    return;
  
  int index = x*n + y;
  if (grid[x][y] == 1) {
    if (finished.find(index) != finished.end())
      return;
    finished.insert(index);
    dfs(x-1,y);
    dfs(x+1,y);
    dfs(x,y+1);
    dfs(x,y-1);
  }
  return;
}