#include <typeinfo>
#include <iostream>
using namespace std;
class A
{
public:
virtual ~A();
};
int main()
{
A* a = NULL;
try
{
cout << typeid(*a).name() << endl;
}
catch (bad_typeid)
{
cout << "Object is NULL" << endl;
}
}