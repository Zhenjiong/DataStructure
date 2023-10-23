#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main() {
  shared_ptr<int> sp = make_shared<int>(100);
  weak_ptr<int> wp(sp);

  if (!wp.expired()) {
    auto temp = wp.lock();
    cout << *temp << endl;
    cout << sp.use_count() << endl;
  }
  cout << sp.use_count() << endl;
  
  return 0;
}