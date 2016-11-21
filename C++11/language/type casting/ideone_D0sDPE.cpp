// User defined conversion function or type-cast operator 
#include <iostream>
#include <ios>
#include <string>

class B;
class A
{
	private:
		int m_;
		char n_;
		
	public:
	
		// http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean
		// A constructor that is not declared with the specifier explicit 
		// and which can be called with a single parameter (until C++11) 
		// is called a converting constructor.


		A():m_(0),n_('\0'){ std::cout << "Constructed A" << std::endl;}
		
		void setM( int m ){ m_ = m;}
		void setN( int n ){ n_ = n;}
		int getM() const { return m_;}
		char getN() const { return n_;}
		
		// Type-cast operator or user defined conversion functions
		explicit operator int() { std::cout << "Converting A to int " << m_ << std::endl;  return m_;}
		explicit operator char() { std::cout << "Converting A to char " << n_ << std::endl; return n_;}
		explicit operator bool() { bool result = ( m_ != 0 );  std::cout << "Converting A to bool " << std::boolalpha << result << std::endl; return result;}
};

class B
{
	private:
		int k_;
		double l_;
		
	public:
	
		// http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean
		// A constructor that is not declared with the specifier explicit 
		// and which can be called with a single parameter (until C++11) is called a converting constructor.
	
		B():k_(0),l_(0.0){ std::cout << "Constructed B" << std::endl;}
		explicit B( A const &a )
		{
			std::cout << "Converting constructor: A to B" << std::endl;
			k_ = a.getM();
		}
		
		int getK() const { return k_;}
		double getL() const { return l_;}
		void setK( int k ){ k_ = k;}
		void setL( double l){ l_ = l;}
		
		// Type-cast operator or user defined conversion functions
		explicit operator int() { std::cout << "Converting B to int " << k_ << std::endl; return k_;}
		explicit operator double() { std::cout << "Converting B to double " << l_ << std::endl; return l_;}
		explicit operator bool() { bool result = ( k_ != 0 ); std::cout << "Converting B to bool " << std::boolalpha << result << std::endl; return result;}		
};

bool FuncExplTypeCastCheck( bool check )
{
	std::cout << "Function for checking explicit type-cast of object to bool: " << std::boolalpha << check << std::endl;
	//return A();// compiler error and will not work as operator bool() for A is marked as explicit
	return static_cast<bool>(A());// Ok
}

int main() {
	A a;
	
	// Testing conversion constructor
	//B b=a; // syntax compiler error because constructors marked as explicit cannot be called with the assignment-like syntax(copy initialization)
	B b(a);// ok syntax when conversion constructor marked as explicit(direct initialization)
	
	// Testing user-defined conversion function or type-cast operator
	a.setM( 102);
	a.setN( 'N');
	// int m = a;// compiler error as type-cast operator marked as explicit doesnt allow copy-initilization syntax
	int m(a);// ok, explicit keyowrd allows only direct initialization
	//char n= (a);// compiler error as type-cast operator marked as explicit doesnt allow copy-initilization syntax
	char n(a);// ok, explicit keyowrd allows only direct initialization
	//bool checkA = a;// compiler error as type-cast operator marked as explicit doesnt allow copy-initilization syntax
	bool checkA = static_cast<bool>(a);// ok, explicit keyowrd allows only direct initialization and only explicit casts to be valid
	
	// Implicitly convert object of type A to bool when passing to function fails
	// bool chk = FuncExplTypeCastCheck( a );// compiler error and // will not work as operator bool() is marked as explicit

	// Explictly convert object of type A to bool when passing to function is OK
	bool chk = FuncExplTypeCastCheck( static_cast<bool>(a));
	
	if( a ){std::cout << "Tested bool true" << std::endl;}
	else	{std::cout << "Tested bool false" << std::endl; }
	
	return 0;
}