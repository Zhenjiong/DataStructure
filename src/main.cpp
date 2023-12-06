#include <iostream>

void getMemory(int *p) {
  // p = new int();
  *p = 30;
  return;
}

int main() {
  int a = 20;
  int* p = &a;
  getMemory(p);
  // *p = 10;
  std::cout << "p: " << *p << std::endl;
  return 0;
}