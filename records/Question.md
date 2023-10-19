
## TODO List

位运算

二叉树的操作

git

new delete 与 c中的 malloc

友元

大端小端

## 八股文

### 1.语言基础

#### 指针与引用

引用和指针都是复合类型，实现对其他对象的间接访问

引用相当于是一个别名，必须初始化：在定义引用的时候，程序会把引用和它的初始值绑定在一起

这节省了拷贝，但同时也代表了无法令引用绑定到另一个对象

指针则是一种指向，存放对象的地址

主要区别：

1. 指针本身是对象，而引用不是对象
   因此——
   (a)不能定义引用的引用，而指针则有指针的指针这样的类型
   (b)不能定义指向引用的指针，但相反存在对指针的引用
```c++
  int *p;
  int *&r = p;  // r是一个对指针p的引用
```
   (c)有常量指针而没有常量引用。常量指针不变的是指针本身，指向不变，顶层const。
      引用就没有顶层const,只有底层const，指向常量的引用。
  
2. 指针不必须在定义时赋初值

#### 数组与指针

数组的大小是固定不变的，在连续的内存中存放了这组元素

可以通过指针来操作数组

#### 左值与右值

C++中将表达式分为左值和右值。一个左值表达式表示对象的身份(在内存中的位置)，一个右值表达式表示对象的值(内容)

左值表达式是不可移动的，而右值表达式是可以移动的

左值: 
变量、函数、模板形参对象或数据成员的名字(std::cin);
返回类型为左值引用的函数调用;
++a/--a;
*ptr、取下标;

右值: 
取地址表达式 &a ;
this指针;
lambda表达式;
字面量;
各种数值运算表达式;
a++/a--;

<div align=center>
<img src="../media/lvalue_rvalue.jpg"  />
</div>

prvalue没有内存实体，取不到地址

xvalue 和 lvalue都有内存实体，但是生命周期不同。左值持久，右值短暂

#### 左值引用和右值引用

为了实现移动语义而引入了右值引用。

顾名思义，左值引用是绑定到左值的引用，右值引用是绑定到右值的引用。

左值引用无法绑定到一个右值上，不过const的引用可以

右值引用只能绑定到右值上，不过右值引用的表达式既可以是右值，也可以是左值

```c++
void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

int main() {
  int &&rref = 1;
  foo(rref);    // output: lvalue
}

// https://www.zhihu.com/question/363686723/answer/1976488046
```

此外还可以使用转发引用实现std::forward()

```c++
#include <iostream>
#include <string>

using namespace std;

void PrintV(int &t) {
  cout << "lvalue" << endl;
}

void PrintV(int &&t) {
  cout << "rvalue" << endl;
}

template<typename T>
void Test(T &&t) {
  PrintV(t);
  PrintV(std::forward<T>(t));

  PrintV(std::move(t));
}

int main() {
  Test(1); // lvalue rvalue rvalue
  int a = 1;
  Test(a); // lvalue lvalue rvalue
  Test(std::forward<int>(a)); // lvalue rvalue rvalue
  Test(std::forward<int&>(a)); // lvalue lvalue rvalue
  Test(std::forward<int&&>(a)); // lvalue rvalue rvalue
  return 0;
}
```

#### struct 与 class

他们只有两个区别：

1 默认的访问权限不同。struct默认都是public成员，class默认是private成员

2 默认的继承派生访问符不同。struct默认public继承，class默认private继承

```c++
class Base {};
struct D1 : Base {};  // 默认public继承
class D2 : Base {};   // 默认private继承
```

#### OOP:多态和继承

继承，通过已有类定义新类，实现软件复用

polymorphism多态，可以使得在执行同一条语句时，能够根据运行情况执行不同的操作，易于系统的扩展

多态性的实现：引用或指针的静态类型和动态类型不同，通过动态绑定，在运行时解析该调用，实现多态；
因此，只有使用基类的引用或指针调用一个虚函数时才会发生动态绑定

虚函数(virtual function) 允许了派生类定义其各自版本的该函数

TODO

#### 访问控制: public private protected




### 操作系统

#### 大端存储和小端存储

大端和小端是两种不同的字节序

大端：数据低位保存在内存高地址中，数据高位则保存在内存低地址中

小端：数据

#### 进程，信号量，锁，多线程

### CUDA

#### 硬件架构与相应的软件对象

#### Debug, Nsight

#### ruduce

bank confilct

#### GEMM

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

## 华为20230921 笔试

第二题 快速传球

[Answer](#20230920-exam-2nd)

m行n列 矩阵为0或1 从第一列的任意一个1，通过上下左右沿着1走到最后一列的任意一个1

求最短路径的长度

第三题 词法分析器

## 小米20230923 笔试

第一题 基站信号强度

第二题 拓扑排序

2
1:0,0:1

错误的解答

TODO

```c++
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main () {
  // int n;
  // cin >> n;
  // string s;
  // cin >> s;

  int n = 2;
  string s = "1:0,0:1";
  int counter = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == ':') {
      int left = i;
      int right = i;
      do
      {
        --left;
      } while (left >=0 && s[left] >= '0' && s[left] <= '9');
      do
      {
        ++right;
      } while (right < n && s[right] >= '0' && s[right] <= '9');
      string ll = s.substr(left+1, i - left - 1);
      string rr = s.substr(i+1, right - i);
      int l = stoi(ll);
      int r = stoi(rr);
      if (l < r) {
        cout << 0;
        break;
      }
    }

    ++counter;
  }
  if (counter == n)
    cout << 1;
  

  return 0;
}
```


## Practice

### 归并排序

148 leetcode 排序链表

对一个链表进行排序，时间复杂度为Nlog(N)

空间logN的自顶向下递归归并：

```c++
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) return nullptr;
        if (head->next == nullptr) return head;
        return sort(head, nullptr);
    }

    ListNode* sort(ListNode* begin, ListNode* end) {
        // if (begin == nullptr) return begin;
        if (begin == end) return begin;
        if (begin->next == end) {
            begin->next = nullptr;
            return begin;
        }

        ListNode* mid = begin;
        ListNode* right = begin->next;
        while (right != end) {
            right = right->next;
            mid = mid->next;
            if (right != end)
                right = right->next;
        }

        return merge(sort(begin, mid), sort(mid, end));
    }

    ListNode* merge(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode* dum = new ListNode(-1);
        ListNode* tail = dum;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        if (list1 == nullptr && list2 != nullptr)
            tail->next = list2;
        if (list2 == nullptr && list1 != nullptr)
            tail->next = list1;
        return dum->next;
    }
```

空间为常数的：



```c++
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) return nullptr;
        if (head->next == nullptr) return head;
        int length = 0;
        ListNode* temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            ++length;
        }

        ListNode* dum = new ListNode(-1);
        dum->next = head;
        for (int subLength = 1; subLength < length; subLength <<= 1) {
            ListNode* pre = dum;
            ListNode* cur = dum->next;
            while (cur != nullptr) {
                ListNode* head1 = cur;
                for (int i=1; i<subLength && cur->next != nullptr; ++i) {
                    cur = cur->next;
                }
                ListNode* head2 = cur->next;
                cur->next = nullptr;
                cur = head2;
                for (int j = 1; j < subLength && cur != nullptr; ++j) {
                    cur = cur->next;
                }
                ListNode* temp = nullptr;
                if (cur != nullptr) {
                    temp = cur->next;
                    cur->next = nullptr;
                }
                cur = temp;

                ListNode* m = merge(head1, head2);
                pre->next = m;
                while (pre->next != nullptr)
                    pre = pre->next;
                pre->next = cur;
            }
        }
        return dum->next;
    }

    ListNode* merge(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode* dum = new ListNode(-1);
        ListNode* tail = dum;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        if (list1 == nullptr && list2 != nullptr)
            tail->next = list2;
        if (list2 == nullptr && list1 != nullptr)
            tail->next = list1;
        return dum->next;
    }
```


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

### 20230920 exam 2nd

可能有超时或递归爆栈的风险，有待考量

广度优先遍历在这题更合适

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

struct Ans {
  int x;
  int y;
  std::vector<int> path;
  Ans(int _x, int _y, std::vector<int> _p)
    : x(_x), y(_y), path(_p) {};
};

class Solution {
 public:
  std::vector<std::vector<int> > grid;
  std::vector<int> res;
  int m;
  int n;

  Solution(std::vector<std::vector<int> > &input, int _m, int _n)
    : m(_m), n(_n), grid(input), res() {
    if (n == 1) {
      bool kk = false;
      for (int i = 0; i < m; ++i) {
        if (grid[i][0] == 1) {
          std::cout << 0;
          kk = true;
          break;
        }
      }
      if (!kk) std::cout << -1;
    }
    // // Plan one: DFS, recursion
    // // ----------------------------------------------------------------
    // else {
    //   for (int i = 0; i < m; ++i)
    //     dfs(i,0,std::vector<int>());
    //   if (res.empty())
    //     std::cout << -1;
    //   else {
    //     std::cout << *std::min_element(res.begin(), res.end());
    //   }
    // }
    // ===================================================================
    // Plan two: BFS, non-recursion
    // -------------------------------------------------------------------
    else {
      for (int i = 0; i < m; ++i) {

        std::deque<Ans> ans;
        std::vector<int> p;
        ans.push_back(Ans(i, 0, p));
        while (!ans.empty()) {
          auto temp = ans.front();
          ans.pop_front();

          if (bfs(temp.x, temp.y, temp.path)) {
            if (*temp.path.rbegin() % n == n-1) {
              res.push_back(temp.path.size() - 1);
              // Find the shortest path from this start point grid[i][0],
              // so break the while
              break;
            }
            ans.push_back(Ans(temp.x - 1, temp.y, temp.path));
            ans.push_back(Ans(temp.x + 1, temp.y, temp.path));
            ans.push_back(Ans(temp.x, temp.y - 1, temp.path));
            ans.push_back(Ans(temp.x, temp.y + 1, temp.path));
          }
        }
      }
      if (res.empty())
        std::cout << -1;
      else
        std::cout << *std::min_element(res.begin(), res.end());
    }
    
  }

  // Each test grid[x][y] save a path,
  // this will copy the new path to the next dfs node
  bool dfs(int x, int y, std::vector<int> path);

  // Save the path change to the outsider of this function
  bool bfs(int x, int y, std::vector<int> &path);

};

int main() {
  int n = 5;
  std::vector<std::vector<int> > grid(n);
  grid[0] = std::vector<int>({1,1,0,0,0});
  grid[1] = std::vector<int>({0,1,0,1,0});
  grid[2] = std::vector<int>({1,1,0,0,0});
  grid[3] = std::vector<int>({1,0,1,1,1});
  grid[4] = std::vector<int>({1,1,1,1,0});
  
  Solution(grid, n, n);
  std::cout << "Hello World!" << std::endl;
  return 0;
}

bool Solution::dfs(int x, int y, std::vector<int> path) {
  if (x < 0 || x > m-1 || y < 0 || y > n-1 || this->grid[x][y] == 0)
    return false;
  if (y == n-1 && grid[x][y] == 1) {
    res.push_back(path.size());
    return true;
  }
  if (std::find(path.crbegin(), path.crend(), x*n+y) != path.crend())
    return false;
  else
    path.push_back(x*n+y);

  bool up = dfs(x-1, y, path);
  bool down = dfs(x+1, y, path);
  bool left = dfs(x, y-1, path);
  bool right = dfs(x, y+1, path);

  if (!up && !down && !left && !right) return false;
  else return true;
  
}

bool Solution::bfs(int x, int y, std::vector<int> &path) {
  if (x < 0 || x > m-1 || y < 0 || y > n-1 || this->grid[x][y] == 0)
    return false;
  if (y == n-1 && grid[x][y] == 1) {
    path.push_back(x*n+y);
    return true;
  }
  if (std::find(path.crbegin(), path.crend(), x*n+y) != path.crend())
    return false;
  else {
    path.push_back(x*n+y);
    return true;
  }
}
```

### 继承中调用构造和析构的顺序

```c++
// 作者：程序员bingo
// 链接：https://zhuanlan.zhihu.com/p/104014640
// 来源：知乎
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#include <iostream>

using namespace std;

class CBase {
public:
  CBase() {
    Init();
  }

  virtual ~CBase() {
    Uninit();
  };

  virtual void Init() {
    Fun();
  }

  virtual void Uninit() {
    cout << "CBase::Uninit" << endl;
  }

  virtual void Fun() {
    cout << "CBase::Fun" << endl;
  }

  int base_value = 0x1234;
};

class CDerived : public CBase {
public:
  CDerived() {
    Init();
  }

  virtual ~CDerived() {
    Uninit();
  }

  virtual void Init() {
    cout << "CDerived::Init" << endl;
  }

  virtual void Uninit() {
    cout << "CDerived::Uninit" << endl;
  }

  virtual void Fun() {
    cout << "CDerived::Fun" << endl;
  }

  int derived_value = 0x5678;
};

int main() {
  CDerived* derived = new CDerived();
  delete derived;
  derived = nullptr;
  return 0;
}
```