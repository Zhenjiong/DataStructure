# Problem Sets

## TODO List

并查集
Leetcode 1631 最小体力消耗路径
Leetcode 547  LCR 116 省份数量

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