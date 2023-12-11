# Problem Sets

## TODO List

并查集
Leetcode 1631 最小体力消耗路径

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