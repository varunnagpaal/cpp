#include <iostream>
#include <exception>
using namespace std;
class base { virtual void dummy() {} };
class derived: public base { int a; };
int main ()
{
try
{
base * pba = new derived;
base * pbb = new base;
derived * pd;
pd = dynamic_cast<derived*>(pba);
if (pd == 0)
cout << "Null pointer on first type-cast" << endl;
pd = dynamic_cast<derived*>(pbb);
if (pd == 0)
cout << "Null pointer on second type-cast" << endl;
}
catch (exception& e)
{
cout << "Exception: " << e.what();
}
return 0;
}