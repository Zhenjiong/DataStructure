#include <iostream>
#include <string>
#include <climits>



int main() {
  std::string s("asda");
  s.erase(1);
  std::cout << s.find('a');
  std::cout << '\n' << s;
  return 0;
}