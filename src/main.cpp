#include <iostream>

union U1 {
  int x;
  float y;
  char *ch;
};

union U2 {
  int x;
  float y;
};

int main() {

  std::cout << sizeof(U1) << std::endl;
  std::cout << sizeof(U2) << std::endl;
  
  return 0;
}