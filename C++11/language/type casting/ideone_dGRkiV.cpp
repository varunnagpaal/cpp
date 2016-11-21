#include <iostream>
using namespace std;

class sq
{
	double s_;

public:
	sq(double x): s_(x*x)
	{}
	
	// conversion operator
	// implicitly or explicitly cast object of class sq to a double
	// http://e...content-available-to-author-only...s.org/wiki/C%2B%2B_Programming/Operators/Operator_Overloading#Conversion_operators
	operator double() const
	{
		std::cout<<"Called conversion operator" << std::endl;
		return s_;
	}
};


class sq_t
{
public:
	typedef double value_type;
	
	value_type operator()(double x) const
	{
		std::cout<<"Called Function call operator" << std::endl; 
		return x*x;
	}
};


int main() {
	double a = sq(3.14);
	
	std::cout << "Square 3.14=" << a <<std::endl;
	
	const sq_t sq2;
	std::cout<< "Yet another square  of 3.14=" << sq2(3.14);
	return 0;
}