#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int main() {
  string s;
  cin >> s;
  
  auto it = s.begin();
  vector<int> numbers;
  while (it != s.end()) {
    string num;
    while (*it <= '9' && *it >= '0') {
      num.push_back(*it);
      it = s.erase(it);
    }
    numbers.push_back(stoi(num));
    ++it;
  }

  vector<char> comrs;
  vector<int> pos;
  it = s.begin();
  
  



  return 0;
}