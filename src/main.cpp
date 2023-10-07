#include <iostream>

struct C {
  int c;
  int c2;
};
struct A {

  virtual void print() {
    std::cout << "A" << std::endl;
  }

  virtual void get() {
    std::cout << a << std::endl;
  }

  int a;
  int a3;
};

struct B : A {
  int b;
};

int main () {
  B bb;
  bb.b = 10;
  A *pA = &bb;
  B *pB = dynamic_cast<B*>(pA);
  std::cout << pB->b << std::endl;
  std::cout << sizeof(B) << std::endl;
  C sc{1};
  std::cout << sc.c2 << " " << sc.c << std::endl;
  return 0;
}