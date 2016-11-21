#include <iostream>
#include <vector>
#include <initializer_list>

// initList is passed by value and is immutable
void func( std::initializer_list<unsigned> initList )
{
	// *v.begin() = 2; //error
	
	for( auto i: initList )
	{
		std::cout << i << "\n";
	}
}

class C
{
public:

C(){ std::cout <<"Default constructor" <<std::endl;}

C( std::initializer_list<unsigned> initList ){ std::cout <<"initializer list constrcutor" <<std::endl;}

C( unsigned ){ std::cout <<"Unsigned int constrcutor" <<std::endl;}
private:
};

int main() 
{
	// 1. using {} and {} vs ()
	std::vector<unsigned> v1{2,3}; // Vector initialized with values 2 and 3 using an initializer list 
	std::vector<unsigned> v2(2,3); // vector of 2 elements each initialized to value 3
	
	// 2. passing an initializer list to a function
	func( {1, 2, 3} );
	
	// 3. Constructor ambiguity and precedence
	C c1{};	// default constructor passed with empty initialization list
	C c2{1};// initializer list constructor
	C c3(1);// single int constructor
	C c4; // default constructor
	return 0;
}