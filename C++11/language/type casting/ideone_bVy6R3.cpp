// Conversion constructor
#include <iostream>

class B;
class A
{
	private:
		int m_;
		char n_;
		
	public:
		A():m_(0),n_('\0'){ std::cout << "Constructed A" << std::endl;}
		
		void setM( int m ){ m_ = m;}
		void setN( int n ){ n_ = n;}
		int getM() const { return m_;}
		char getN() const { return n_;}
};

class B
{
	private:
		int k_;
		double l_;
		
	public:
		B():k_(0),l_(0.0){ std::cout << "Constructed B" << std::endl;}
		B( A const &a )
		{
			std::cout << "Converting constructor: A to B" << std::endl;
			k_ = a.getM();
		}
		
		int getK() const { return k_;}
		double getL() const { return l_;}
		void setK( int k ){ k_ = k;}
		void setL( double l){ l_ = l;}
};

int main() {
	A a;
	B b(a);
	return 0;
}