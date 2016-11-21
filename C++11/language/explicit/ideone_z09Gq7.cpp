#include <iostream>
using namespace std;

class String {
public:

	// A constructor that is not declared with the specifier explicit 
	// and which can be called with a single parameter (until C++11) is called 
	// a converting constructor.
	
	// without explicit, int can be implicitly converted to a temporary object 
	// of type "String". Marking constructor as explicit disables such implicit
	// conversions
    explicit String(int n){ 
    	std::cout << "Integer argument non-converting constructor with value "
    			  << n << std::endl;
	}; // allocate n bytes to the String object
    
    // without explicit, char* or char[] can be implicitly converted to a
    // temporary object of type "String".
	// Marking constructor as explicit disables such implicit conversions
    explicit String(const char *p){ 
    	std::cout << "Array of const char argument non-converting constructor"
    			  << std::endl;
  	}; // initializes object with char *p

	// Here constructor is single argument and is without explicit keyword,
	// and so it is a converting constructor. It will implicitly convert a 
	// double literal to type String in following cases:
	// 1. either passing double to function with argument of type String or
	// 2. returning a double from function of return type String or 
	// 3. Using copy-initilization syntax to construct String from double
	String( double d ){ 
		std::cout << "Double argument converting constructor with value: " << d 
				  << std::endl;
	}
};


String checkFunc( String dblStr)
{
	std::cout << "Function which passes object of type String and returns a "
				 "object of type String" << std::endl;
	std::cout << "Value returned from this function is of type double which is "
				 "converted to String implicitly by converting constructor" 
			  << std::endl;
	
	// Here double value returned is implicitly converted to type String
	// because there exists a converting consructor String(double)
	return 7.8;
}

int main() {
	
	// ok as copy-initilization syntax works when constructor is not explicit. 
	// here double literal is implicitly converted to type String first before 
	// it is used 
	String mydbl = 35.7;
	
	// error as copy-initilization syntax is prohibhited when constructor is 
	// explicit
	//String mystring = "x";
	
	// ok syntax as explicit keyword supports only direct initialization syntax 
	String mystring("x");

	String ret = checkFunc( 10.5);
	return 0;
}