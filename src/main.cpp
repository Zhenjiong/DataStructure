#include <iostream>
#include <string>
#include <list>

int main() {
  std::string s = "Hello";
  s.erase(s.begin(), s.begin()+1);
  
  std::cout << s;
  return 0;
}