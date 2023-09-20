
## TODO List

位运算

二叉树的操作

## 荣耀20230909 笔试


第三题 走格子。

[Answer](#20230909-exam-3rd)

N*N的矩阵格子，-1表示障碍物，1表示怪兽格子，0表示空

从(0,0)走到(N-1,N-1),只能向下或向右走格子

从(N-1,N-1)走到(0,0)，只能向上或向左走格子

无法从(0,0)走到(N-1,N-1)则无法消灭任何怪兽

走过怪兽格子，1将变为0

问最多消灭多少怪兽

第二题 展开字符串

[Answer](#20230909-exam-2nd)

输入 abas3(adf)

输出 fdafdafdasaba

有（{[ 三种括号

## 腾讯20230910 笔试 一面

反转链表2

二叉树，节点为1或者0

求从根节点到叶子节点的所有路径中，1的个数比0多一个的路径有几条


## 百度20230912 笔试 A卷

第三题

n个整数表示愤怒值

操作m次，每次操作会给一个区间的整数们分别-1

求几次操作后存在人愤怒值归0了?(没人归零就输出m)

## 腾讯20230915 笔试

第四题

几个旋转字符串，寻找匹配的。

存在两个匹配，yes，否则no

第五题

0 红色 1 蓝色

给出位置 {x_n} 该位置的颜色 {c_n}

可以最多使用k次操作2：将蓝色变成红色

问需要几次操作1：将红色左移或者右移1格，才能让任意两个红色之间没有蓝色


## OPPO20230916 笔试

第三题 已知平面三角形和半径r

对于三角形内的点，以该点做圆心，画半径为r的圆

求圆能在三角形内的圆心的概率






## Practice

### 归并排序

148 leetcode 排序链表

对一个链表进行排序，时间复杂度为Nlog(N)

### 二分查找

### 反转链表

### 正则匹配




## Answers

### 20230909 exam 2nd

```c++
#include <iostream>
#include <string>
#include <stack>
#include <vector>

// // right < left
// struct Range{
//   char commr;
//   int left;
//   int right;
//   int new_pos;
//   Range(char _commr, int _left, int _right, int _newpos)
//     : commr(_commr), left(_left), right(_right), new_pos(_newpos) {};
// };

int main () {

  std::string input = "adsd10(ab3(ji)a)";

  int n = input.size();
  int cur = n-1;
  std::stack<int> ranges;
  std::string res;
  while (cur >= 0) {
    if (input[cur] == ')') {
      ranges.push(res.size());
    }
    else if (input[cur] == '(') {
      // int left_comm = cur;
      auto temp = ranges.top();
      ranges.pop();

      std::vector<int> nums;
      do {
        --cur;
        nums.push_back(input[cur] - '0');
      } while (cur > 0 && input[cur-1] <= '9' && input[cur-1] >= '0');
      int counter = 0;
      for (auto it = nums.rbegin(); it != nums.rend(); ++it)
        counter = 10 * counter + *it;
      
      std::string tt(res.begin()+temp, res.end());
      for (int i = 1; i < counter; ++i)
        res += tt;
    }
    else {
      res.push_back(input[cur]);
    }
    
    --cur;
  }

  std::cout << res << std::endl;
  return 0;
}
```

### 20230909 exam 3rd

```c++
#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int> > grid;
  std::unordered_set<int> dead_monsters;
  int n;

  Solution(std::vector<std::vector<int> > &input, int _n)
    : n(_n), grid(input), dead_monsters() {
    dfs(0,0);
    std::cout << dead_monsters.size() << std::endl;
  }

  bool dfs(int x, int y);

};

int main() {
  int n = 5;
  std::vector<std::vector<int> > grid(n);
  grid[0] = std::vector<int>({0,0,0,1,1});
  grid[1] = std::vector<int>({0,0,-1,-1,0});
  grid[2] = std::vector<int>({0,-1,0,1,0});
  grid[3] = std::vector<int>({0,1,1,0,-1});
  grid[4] = std::vector<int>({0,0,1,1,0});
  
  Solution(grid, n);
  std::cout << "Hello World!" << std::endl;
  return 0;
}

bool Solution::dfs(int x, int y) {
  if (x < 0 || x > n-1 || y < 0 || y > n-1 || this->grid[x][y] == -1)
    return false;
  if (x == n-1 && y == n-1) return true;
  bool next_row = dfs(x+1,y);
  bool next_col = dfs(x,y+1);
  if (next_row || next_col) {
    if (this->grid[x][y] == 1)
      this->dead_monsters.insert(x*n+y);
    return true;
  }
  else {
    return false;
  }
}
```