#include <memory>
#include <vector>

template < template < class, class > class Container, class Type >
//template < template < typename, typename > class Container, typename Type >
//template < template < typename, typename > typename Container, typename Type >
class Example
{
     Container< Type, std::allocator < Type > > baz;
};

template < class T1, typename T2> 
class X
{
  private:
  T1 d;
  T2 q;
};

class Y
{
};

void P()
{
 Example<X,float> f; 
 X<Y, float> l;
};

template <class T>
class MyClass {
   int i;
   std::vector<int> vi;
   std::vector<int>::iterator vitr;
   
// !error: need 'typename' before 'std::vector<T>::iterator' because 'std::vector<T>' is a dependent scope
// T t;
// std::vector<T> vt;
// std::vector<T>::iterator viter;
  
   T t;
   std::vector<T> vt;
   typename std::vector<T>::iterator viter;  
};


int main()
{
	P();
	return 0;
}