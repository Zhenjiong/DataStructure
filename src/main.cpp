#include <iostream>
#include <string>

char itoc(int x) {
  if (x == 0)
    return '0';
  if (x == 1)
    return '1';
  if (x == 2)
    return '2';
  if (x == 3)
    return '3';
  if (x == 4)
    return '4';
  if (x == 5)
    return '5';
  if (x == 6)
    return '6';
  if (x == 7)
    return '7';
  if (x == 8)
    return '8';
  if (x == 9)
    return '9';
}

int main() {
  std::string s1, s2;
  // std::cin >> s1;
  // std::cin >> s2;
  s1 = "234"; s2 = "123";

  auto it = s1.rbegin();
  auto it2 = s2.rbegin();
  std::string result = s1;
  // int res = 0;
  int pos = 0;
  bool bring = false;
  while (it != s1.rend() && it2 != s2.rend()) {
    int m = *it - *it2;
    if (bring) {
      --m;
      bring = false;
    }
    if (m >= 0) {
      result[pos] = itoc(m);
      // res = res + m * pos;
      ++pos;
    }
    else {
      if (it+1 != s1.rend()) {
        result[pos] = itoc(10+m);
        // res = res + (10+m) * pos;
        ++pos;
        bring = true;
      }
      // minus result
      else {
        result = '-' + result;
      }
    }
    ++it2;
    ++it;
  }

  int k = 0;
  
  while (result[k] == '0') {
    ++k;
  }
  auto res = result.substr(k, result.size()-k);
  std::cout << res;
  return 0;
}