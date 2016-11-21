#include <iostream>

class Base{
  public:
    void foo(){std::cout<<"base\n";}
};

class Derived : public Base
{
  public:
    void foo(){std::cout<<"derived\n";}
};

int main()
{
  Derived bar;
  bar.foo();
  
  Base* basePtrToDerived = &bar;
  basePtrToDerived->foo();
  //call Base::foo() from bar here?
  bar.Base::foo(); // using a qualified-id
  return 0;
}