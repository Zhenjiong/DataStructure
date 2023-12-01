#include <iostream>

struct A {

  A() = default;

  A(char *input) : ch(input) {
    if (*ch == 'a')
      throw std::runtime_error("aaaa");
    std::cout << "construct A! " << std::endl;
  }

  ~A() {
    std::cout << "destroy A! " << std::endl;
  }

  char *ch = nullptr;  
};

int main() {

  char *in = "asdf";
  A(in);  
  return 0;
}