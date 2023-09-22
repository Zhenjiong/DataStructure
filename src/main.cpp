#include <iostream>

class A {
 public:
  virtual void out() const{
    std::cout << "A" << std::endl;
  }

  int aa;

};

class B {
 public:
  // virtual void out() const override {
  //   std::cout << "B" << std::endl;
  // }
  void out() const;
  void out();
  int bb;
};

void B::out() const {
  std::cout << "const B" << std::endl;
}

void B::out() {
  std::cout << "no-const B" << std::endl;
}

void test(A &a) {
  a.out();
}

void test_b(const B &b) {
  b.out();
}

void test_c(const B b) {
  b.out();
}

int main() {
  A a;
  B b;
  b.out();
  const B* cb = &b;
  cb->out();
  test_b(b);
  test_c(b);
  // test(b);

  int cc = 4;
  int &const c = cc;
  c = 5;
  std::cout << cc;
  
  return 0;
}