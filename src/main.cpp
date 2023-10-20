#include <iostream>
#include <utility>
#include <memory>
#include <string>

using namespace std;

struct A {
  int a;
  char b;
  string s;
  // int c;
  // int d;
  // double e = 0.0;
};


int main() {
  int a[3] = {1,2,3};
  cout << sizeof(A) << endl;
  cout << sizeof(a) << endl;
  cout << &a << endl;
  cout << &(a + 1) << endl;

  // A aa{10, 's', 20, 8};
  // A *p = &aa;
  // A &r = aa;
  // shared_ptr<A> sp(new A {10, 's', 20, 8});
  // weak_ptr<A> wp(sp);
  // cout << sizeof(wp) << " " << sizeof(sp) << " " << sizeof(p) << " " << sizeof(r) << endl;
  return 0;
}