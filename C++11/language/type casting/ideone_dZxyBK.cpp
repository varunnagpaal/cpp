// http://webcourse.cs.technion.ac.il/236703/Summer2015/ho/WCFiles/11%20-%20C++%20Casts.pdf
#include <iostream>
using namespace std;



int main()
{
	{
		struct A
		{ 
			//virtual void f()=0;
		};
		
		struct B : A
		{
			virtual void f(){}
		};
		
		struct C : B
		{
			
		};
		
		A* a = new B();
		B* b1 = static_cast<B*>(a);
		B* b2 = reinterpret_cast<B*>(a);
		//B* b3 = dynamic_cast<B*>(a);// dynamic downcast only valid for polymorphic base class
		
		std::cout << a <<", " << b1 <<", " << b2 <<std::endl;
		delete a;
	
		//----------------------------------------------------------------
		B* b = new C();
		C* c1 = static_cast<C*>(b);
		C* c2 = reinterpret_cast<C*>(b);
		C* c3 = dynamic_cast<C*>(b);// here base class is polymorphic, so it works
		
		std::cout << b <<", " << c1 <<", " << c2 <<", " << c3 <<std::endl;
		delete b;
	}
	
	{
		// virtual inheritance
		struct A { virtual void f(){} };
		struct B : virtual A { };
		A* a = new B();
		B* b1 = static_cast<B*>(a); // Compiler error
		B* b2 = reinterpret_cast<B*>(a); // Runs, but a wrong result
		B* b3 = dynamic_cast<B*>(a);
		
		std::cout << a <<", " << b1 <<", " << b2 <<", " << b3 <<std::endl;
		delete a;
	}

	return 0;
}