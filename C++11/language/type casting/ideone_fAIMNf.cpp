#include <iostream>
using namespace std;

class A
{
    public:
    A();
    ~A();
    void XF();
};

void A::XF()
{}

class B: private A 
{
public:
    B();
    ~B();
};



int main() 
{
	B* beePointer = new B();
	
	// ERROR! compiler complains that the 
	// method is not accessible
	beePointer->XF();
	
	// ERROR! compiler complains that the 
	// conversion from B* to A* exists but
	// is not accessible
	A* aPointer = new B();
	
	// ! for the following two the standard
	// stipulates the behavior as undefined;
	// the compiler should generate an error at least
	// for the first one saying that B is not a
	// polymorphic type
	A* aPointer2 = dynamic_cast<A*>(beePointer);
	A* aPointer3 = reinterpret_cast<A*>(beePointer);
	return 0;
}