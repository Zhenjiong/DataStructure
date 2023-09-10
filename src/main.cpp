#include <iostream>
#include <vector>
#include <memory>
#include <string>

int main() {
  std::string s = "Hello";
  std::shared_ptr<std::string> p = std::make_shared<std::string>();
  int i = 9;
  if (p)
    std::cout << "true ";
  if (p && p->empty())
    *p = "Hi";
  std::cout << &p << "\n"
            << *p << "\n";
  return 0;
}