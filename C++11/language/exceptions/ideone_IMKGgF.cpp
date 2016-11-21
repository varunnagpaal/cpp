#include <iostream>
using namespace std;
void test(int x)
{
try
{
if (x > 0)
throw x;
else
throw 'x';
}
catch(char)
{
cout << "Catch a integer and that integer is:" << x;
}
}
int main()
{
cout << "Testing multiple catches\n:";
test(10);
test(0);
}