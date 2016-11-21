#include <iostream>
using namespace std;

class X
{
};

// lvalue reference overload
void foo(X& x)
{
	std::cout<< "lvalue" <<std::endl;
}
// rvalue reference overload
void foo(X&& x)
{
		std::cout<< "rvalue" <<std::endl;
}

// lvalue or rvalue
void bar( const X &x)
{
	std::cout<<"lvalue or rvalue " <<std::endl;	
}

// rvlaue only
void nobar( X&& x)
{
	std::cout<< "rvalue" <<std::endl;
}

// lvalue only
void nobar( const X &x)
{
	std::cout<< "lvalue" <<std::endl;
}

X foobar()
{
	return X();
}

int main() 
{
	X x;
	foo(x); // argument is lvalue: calls foo(X&)
	foo(foobar()); // argument is rvalue: calls foo(X&&)
	bar(x);
	bar(foobar());
	nobar( x );
	nobar( foobar() );
	return 0;
}