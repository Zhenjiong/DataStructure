#include <iostream>
#include <string>

using namespace std;

void PrintV(int &t) {
  cout << "lvalue" << endl;
}

void PrintV(int &&t) {
  cout << "rvalue" << endl;
}

template<typename T>
void Test(T &&t) {
  PrintV(t);
  PrintV(std::forward<T>(t));

  PrintV(std::move(t));
}

struct A {
  int b;
  int &a;

  A (int _a, int _b)
    : b(_b), a(_a) {}

};

int main() {
  Test(1); // lvalue rvalue rvalue
  int a = 1;
  Test(a); // lvalue lvalue rvalue
  Test(std::forward<int>(a)); // lvalue rvalue rvalue
  Test(std::forward<int&>(a)); // lvalue lvalue rvalue
  Test(std::forward<int&&>(a)); // lvalue rvalue rvalue

  int x = 20;
  int y = x & (-x);
  std::cout << y << std::endl;

  A(21, 12);
  int k = 10;
  int &&pp = 20;
  std::cout << std::is_rvalue_reference_v<decltype(pp)> << std::endl;
  return 0;
}