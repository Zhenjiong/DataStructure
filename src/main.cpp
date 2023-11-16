#include <cstring>

#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <functional>  // basic hash template, such as hash<int>

class String {
 public:

  String(const char*);  

  void test();
 private:
  
  char* mData;
};

#define TT int[5]

int main() {

  std::string s = "H!";
  String ms(s.c_str());
  const char* kk = s.c_str();
  kk = kk + 2;
  int* x = new TT;
  *x = 1;
  *(x+1) = 2;
  int *pp = x+1;
  delete x;
  x = nullptr;
  // std::cout << *(x+1);
}

String::String(const char* in) {
  if (in == nullptr) {
    mData = new char [1];
    mData[0] = '\0';
  }
  else {
    auto size = std::strlen(in);
    mData = new char [std::strlen(in)+1];
    std::strcpy(mData, in);
    std::cout << *mData << std::endl;
  }
}

void String::test() {

}
