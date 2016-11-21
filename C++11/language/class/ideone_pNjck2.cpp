#include <iostream>

using namespace std;

class NormalClass
{
     public:  const int &getI() const;
              const char &getC() const;
     private: int i;
              char b;
              char c;
};

class EmptyClass
{    

};

class DerivedEmptyClass: public EmptyClass
{
	
};

class AbstractClass
{
  public: 
          virtual void funcOne() = 0;
          virtual void funcTwo() = 0; // Virtual pointer
};

class DerivedAbstractClass: public AbstractClass
{
public: 
          virtual void funcOne() = 0;
          virtual void funcTwo() = 0; // Virtual pointer	
};

class NotAbstrClass
{
  public: int Func( int );
          long Func( char );
          //virtual int funcMe();
};

class MixClass
{
  public:
          virtual void clFunc( int ); // Virtual pointer
          static int i; // Not part of object of class so no contribution
          int j;
          char k;
};

int main()
{
    // Print size of class or class objects
    cout<<"Size of Normal class: "<< sizeof(NormalClass)<<endl;
    cout<<"Size of empty class: "<< sizeof(EmptyClass)<<endl;
    cout<<"Size of Abstract class :"<< sizeof(AbstractClass)<<endl;
    cout<<"Size of Non Abstract class: "<< sizeof(NotAbstrClass)<<endl;
    cout<<"Size of Mix class: "<< sizeof(MixClass)<<endl;
    
    cout<<"Size of Empty Derived class: "<< sizeof(DerivedEmptyClass)<<endl;
    cout<<"Size of Derived Abstract class :"<< sizeof(DerivedAbstractClass)<<endl;

    return 0;
    
}