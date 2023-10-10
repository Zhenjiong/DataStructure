#include <iostream>

using namespace std;

class CBase {
public:
  CBase() {
    Init();
  }

  virtual ~CBase() {
    Uninit();
  };

  virtual void Init() {
    Fun();
  }

  virtual void Uninit() {
    cout << "CBase::Uninit" << endl;
  }

  virtual void Fun() {
    cout << "CBase::Fun" << endl;
  }

  int base_value = 0x1234;
};

class CDerived : public CBase {
public:
  CDerived() {
    Init();
  }

  virtual ~CDerived() {
    Uninit();
  }

  virtual void Init() {
    cout << "CDerived::Init" << endl;
  }

  virtual void Uninit() {
    cout << "CDerived::Uninit" << endl;
  }

  virtual void Fun() {
    cout << "CDerived::Fun" << endl;
  }

  int derived_value = 0x5678;
};

int main() {
  CDerived* derived = new CDerived();
  delete derived;
  derived = nullptr;
  return 0;
}