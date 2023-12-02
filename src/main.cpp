#include <iostream>

struct A {

  A() = default;

  A(int *input) {
    a = input;
    if (*a == 1)
      throw std::runtime_error("aaaa");
    std::cout << "construct A! " << std::endl;
  }

  ~A() {
    std::cout << "destroy A! " << std::endl;
  }

  int *a = nullptr;  
};

int main() {

  int in[5] = {1, 2, 3, 4, 5};
  int* p = in;
  std::cout << *p << std::endl;
  A((int*)p);  
  return 0;
}