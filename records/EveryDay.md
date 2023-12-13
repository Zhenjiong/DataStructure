# Problem Sets

## TODO List

并查集
Leetcode 1631 最小体力消耗路径

岛屿问题 图的遍历
Leetcode 695 岛屿的最大面积
Leetcode 200 岛屿数量

## DataSturcture and Algorithm 

## LeetCode

### Sliding Window(滑动窗口)

#### Leetcode 438 找到字符串中所有字母的异位词

给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。

示例 1:
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词

思路:
初始思路: 使用unordered_map<char, int>记录p的字符，频繁使用find来查找、增删

滑动窗口思路: 
记录p与s的差别int diff, 优化重复比较

[Answer](#leetcode-438)

### Disjoint Set(并查集)

典型问题是有n个人，按族谱归类，最终有几个家族，判断两个人之间是否是亲戚

核心为并与查:

并, unite方法，将孤立的两个节点连通，使这两个节点组成一个连通分量，成为一个集合.

查, find方法，该方法可以查询某个节点属于哪个连通分量(集合).

将集合用一棵树来表示, 树的根节点就是这个集合的标签. 每个节点有一个指针指向其父节点, 初始时指针指向自己. 实际C++实现中可以利用下标访问，采用数组parent保存父节点情况.

unite的优化: 按秩合并——按树的高度或者树的重量

find的优化: 路径紧缩(path compaction)、路径分隔(path splitting)、路径对折(path halving). 优化的find会改变树的高度，需注意

复杂度分析:

定义爆炸增长的Ackermann函数$A(i,j)$和其倒数$\alpha(p,q)$: 

$A(i,j)=\left\{\begin{matrix}
2^j     \quad  \quad \quad \quad  i=2 \ and \ j\geqslant 1\\
A(i-1,2) \quad \quad i\geqslant 2 \ and \ j=1 \\
A(i-1,A(i,j-1)) \quad i,j\geqslant 2\\
\end{matrix}\right.$

$\alpha(p,q)=min\{z\geqslant1|A(z,\left \lfloor p/q \right \rfloor)>log_2q\},p\geqslant q \geqslant 1$

$\alpha(p,q)$增长缓慢，一般的应用中可以假设$\alpha(p,q) \leqslant 4$

并查集的时间复杂度为$\alpha(p,q)$, q是集合的元素个数, p是查找次数和元素个数的和.


例子: 

```c++
struct DisjointSet {
  vector<int> parent;
  // 采用重量作为秩
  vector<int> rank;

  DisjointSet(int n)
    : parent(n), rank(n, 1) {
    for (int i = 0; i < n; ++i)
      this->parent[i] = i;
  }

  // path compaction 路径紧缩
  int find(int ele) {
    if (parent[ele] == ele)
      return ele;
    else {
      parent[ele] = find(parent[ele]);
      return parent[ele];
    }
  }

  void unite(int a, int b) {
    int classA = find(a);
    int classB = find(b);
    if (classA == classB) return;
    if (rank[classA] <= rank[classB]) {
      parent[classA] = classB;
      rank[classB] = rank[classA] + rank[classB];
      rank[classA] = 1;
    }
    else {
      parent[classB] = classA;
      rank[classA] = rank[classA] + rank[classB];
      rank[classB] = 1;
    }
  }
};
```

#### LeetCode 547 省份数量(LCR 116)

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。

求省份数量.

该题可以采用深度遍历或者广度遍历解决，在复杂度上更有优势. 并查集方法亦可解决, 以此为例使用并查集.

[Answer](#leetcode-547)

#### LeetCode 1631 最小体力消耗路径

你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子 (row, col) 的高度。一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。

一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。

请你返回从左上角走到右下角的最小 体力消耗值 。

输入：heights = [ [1,2,2], [3,8,2], [5,3,5] ]
输出：2
解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。

解法: 

我们可以将本题抽象成如下的一个图论模型：

我们将地图中的每一个格子看成图中的一个节点；

我么将两个相邻（左右相邻或者上下相邻）的两个格子对应的节点之间连接一条无向边，边的权值为这两个格子的高度差的绝对值；

我们需要找到一条从左上角到右下角的最短路径，其中一条路径的长度定义为其经过的所有边权的最大值。

作者：力扣官方题解
链接：https://leetcode.cn/problems/path-with-minimum-effort/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

此处暂时介绍并查集方法
TODO

[Answer](#leetcode-1631)

### Graph DFS BFS

#### Island Problem

网格形状图的遍历

## Answers

### LeetCode

#### LeetCode 438

```c++
  vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    if (s.size() < p.size())
      return res;
    vector<int> counter(26);
    for (int i = 0; i < p.size(); ++i) {
      ++counter[s[i] - 'a'];
      --counter[p[i] - 'a'];
    }
    int diff = 0;
    for (auto k : counter) {
      // 非0说明不同, 该字母不对应;
      // 因此后续与0相关的变动才会影响diff
      if (k != 0)
        ++diff;
    }
    if (diff == 0)
      res.push_back(0);
    
    for (int i = 0; i < s.size() - p.size(); ++i) {
      if (counter[s[i] - 'a'] == 1)
        --diff;
      if (counter[s[i] - 'a'] == 0)
        ++diff;
      --counter[s[i] - 'a'];
      if (counter[s[i + p.size()] - 'a'] == -1)
        --diff;
      if (counter[s[i + p.size()] - 'a'] == 0)
        ++diff;
      ++counter[s[i + p.size()] - 'a'];

      if (diff == 0)
        res.push_back(i+1);
    }
    return res;
  }
```

#### LeetCode 547

并查集: 

```c++
struct DisjointSet {
  vector<int> parent;
  // 采用重量作为秩
  vector<int> rank;

  DisjointSet(int n)
    : parent(n), rank(n, 1) {
    for (int i = 0; i < n; ++i)
      this->parent[i] = i;
  }

  // path compaction 路径紧缩
  int find(int ele) {
    if (parent[ele] == ele)
      return ele;
    else {
      parent[ele] = find(parent[ele]);
      return parent[ele];
    }
  }

  void unite(int a, int b) {
    int classA = find(a);
    int classB = find(b);
    if (classA == classB) return;
    if (rank[classA] <= rank[classB]) {
      parent[classA] = classB;
      rank[classB] = rank[classA] + rank[classB];
      rank[classA] = 1;
    }
    else {
      parent[classB] = classA;
      rank[classA] = rank[classA] + rank[classB];
      rank[classB] = 1;
    }
  }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
      int n = isConnected.size();
      DisjointSet s(n);
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (isConnected[i][j] == 1) {
            s.unite(i, j);
          }
        }
      }
      
      int sum = 0;
      int counter = 0;
      for (auto p : s.rank) {
        if (p != 1) {
          sum += p;
          ++counter;
        }
      }
      counter = counter + n - sum;
      return counter;
    }
};
```

深度遍历:

```c++
  void dfs(vector<vector<int> >& isConnected, vector<int>& visited, int i) {
    for (int j = 0; j < isConnected.size(); ++j) {
      if (isConnected[i][j] == 1 && visited[j] == 0) {
        visited[j] = 1;
        dfs(isConnected, visited, j);
      }
    }
  }

  int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<int> visited(n);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (visited[i] == 0) {
        ++res;
        visited[i] = 1;
        dfs(isConnected, visited, i);
      }
    }
    return res;
  }
```

广度遍历:

```c++
  int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<int> visited(n);
    int res = 0;
    queue<int> q;
    for (int i = 0; i < n; ++i) {
      if (visited[i] == 0) {
        q.push(i);
        while (!q.empty()) {
          int f = q.front();
          q.pop();
          visited[f] = 1;
          for (int k = 0; k < n; ++k) {
            if (isConnected[f][k] == 1 && visited[k] == 0)
              q.push(k);
          }
        }
        ++res;
      }
    }
    return res;
  }
```

#### LeetCode 1631

并查集方法解决:

```c++
struct Edge {
  int l;
  int r;
};

struct DisjointSet {
  vector<int> parent;
  vector<int> rank;
  int setCount;

  DisjointSet(int n)
    : parent(n), rank(n, 1), setCount(n) {
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int findSet(int x) {
    return parent[x] == x ? x : (parent[x] = findSet(parent[x]));
  }

  void unite(int a, int b) {
    int x = findSet(a);
    int y = findSet(b);
    if (x == y) return;
    if (rank[x] <= rank[y]) {
      parent[x] = y;
      rank[y] += rank[x];
    }
    else {
      parent[y] = x;
      rank[x] += rank[y];
    }
    --setCount;
  }

  bool isSameSet(int x, int y) {
    return findSet(x) == findSet(y);
  }

};

class Solution {
public:
  int minimumEffortPath(vector<vector<int>>& heights) {
    int m = heights.size();
    int n = heights[0].size();
    if (m == 1 && n == 1) return 0;

    multimap<int, Edge> edges;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int id = i * n + j;
        if (i < m-1) {
          int value = abs(heights[i][j] - heights[i+1][j]);
          edges.insert(pair<int, Edge>(value, Edge{id, id + n}));
        }
        if (j < n-1) {
          int value = abs(heights[i][j] - heights[i][j+1]);
          edges.insert(pair<int, Edge>(value, Edge{id, id + 1}));
        }
      }
    }
    
    DisjointSet s(m*n);
    for (auto e : edges) {
      s.unite(e.second.l, e.second.r);
      if (s.isSameSet(0, m*n-1))
        return e.first;
    }
    return edges.rbegin()->first;
  }

};
```