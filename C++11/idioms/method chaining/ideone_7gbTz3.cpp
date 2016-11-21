#include <iostream>
using namespace std;
struct X
{
	int _a;
	char _b;
	double _c;

	X& setA( int a )
	{
		_a = a;
	}
	
	X& setB( char b )
	{
		_b = b;
	}
	
	X& setC( double c )
	{
		_c = c;
	}
};



int main()
{
	X x;
	x.setA(10).setB('b').setC(-1.5);
	return 0;
}