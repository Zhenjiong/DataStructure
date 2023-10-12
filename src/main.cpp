#include <iostream>

char quan[] = "jkl;";

int main () {
  char s[] = "asdf";
  int i = 4;
  std::cout << &"kkkk" << " " << &quan << " " << &s << " " << &i << std::endl;
  return 0;
}