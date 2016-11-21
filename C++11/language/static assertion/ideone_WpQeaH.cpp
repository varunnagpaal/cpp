// Static Assert
#include <iostream>
using namespace std;

int main()
{
	// Compile time checking of a property
	static_assert( sizeof(int) >= 4, "sizeof(int) is less than 4");
	static_assert( sizeof(int) >= 8, "sizeof(int) is less than 8");
	
	// Static assertion can be used anywhere that can be expressed in terms of
	// constant expressions
	
	
	return 0;
}