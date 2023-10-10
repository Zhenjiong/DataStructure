#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct A {
  int a;

  A(const A &) = delete;

	A(A &&) = default;

	A &operator=(const A &other) noexcept = delete;

	A &operator=(A &&other) noexcept = delete;
};

int main () {
  
  vector<A> data;
  data.push_back(A{10});
  data.push_back(A{30});

  auto data2(std::move(data));

  vector<unique_ptr<int> > x;
  x.push_back(make_unique<int>(10));
  x.push_back(make_unique<int>(50));

  auto y(std::move(x));

  return 0;
}